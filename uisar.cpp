#include "uisar.h"
#include "ui_uisar.h"
#include "qmlmarkerdialog.h"

void uiSAR::ReadTelemetry(QByteArray data){

    // Тут приходят данные телеметрии
    TelemetryData = reinterpret_cast<TelemetryData_t*>(data.data());
    //qDebug() << data;
    updateTelemetry();

}

void uiSAR::ReadExec(QByteArray data){
    qDebug() << data;
    ui->consoleMain->write(data);
    ui->consoleMain->flush();
}

uiSAR * uiSAR::pMainWindow;
uiSAR::uiSAR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::uiSAR)
{
    pMainWindow = this;
    config = new Config(QCoreApplication::applicationDirPath()+"/config2.ini");
    //settings->setValue("header/version", "1106");


    /* Интерфейс для получения телеметрии */
    Telemery = RemoteAuto("UDP");
    connect(Telemery, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    initUI();
    loadSettings();

    // Console test

    QString execAddr = "127.0.0.1:2222";
    QString connectStatus = "connect to " + execAddr + " ";
    Remote *c = RemoteAuto("TCP");

    if(c->Connect(execAddr) != -1){
        c->Send("test"); // Запуск удаленной команды execd
        connectStatus.append("OK");
    }else{
        connectStatus.append("Error");
    }

    ui->consoleMain->write(connectStatus.toUtf8());
    ui->consoleMain->flush();

    connect(c, SIGNAL(received(QByteArray)), this, SLOT(ReadExec(QByteArray)));

}

uiSAR::~uiSAR()
{
    delete ui;
}

uiSAR *uiSAR::getMainWinPtr()
{
    return pMainWindow;
}

void uiSAR::update_jpgblocklabels_from_field(JPGFields _field)
{
    //bold+size for all future 7px bold labels
    QFont bold7pxfont = ui->jpgtls_latdisp->font();
    bold7pxfont.setPointSize(7);
    bold7pxfont.setBold(true);
    //just use ui->labelname->setFont(bold7pxfont);
    ui->jpgtls_latdisp->setText(QString::number(_field.latitude));
    ui->jpgtls_latdisp->setAlignment(Qt::AlignRight);
    ui->jpgtls_latdisp->setFont(bold7pxfont);
    ui->jpgtls_londisp->setText(QString::number(_field.longitude));
    ui->jpgtls_londisp->setAlignment(Qt::AlignRight);
    ui->jpgtls_londisp->setFont(bold7pxfont);
    ui->jpgtls_dxdisp->setText(QString::number(_field.dx));
    ui->jpgtls_dxdisp->setAlignment(Qt::AlignRight);
    ui->jpgtls_dxdisp->setFont(bold7pxfont);
    ui->jpgtls_dydisp->setText(QString::number(_field.dy));
    ui->jpgtls_dydisp->setAlignment(Qt::AlignRight);
    ui->jpgtls_dydisp->setFont(bold7pxfont);
    ui->jpgtls_x0disp->setText(QString::number(_field.x0));
    ui->jpgtls_x0disp->setAlignment(Qt::AlignRight);
    ui->jpgtls_x0disp->setFont(bold7pxfont);
    ui->jpgtls_y0disp->setText(QString::number(_field.y0));
    ui->jpgtls_y0disp->setAlignment(Qt::AlignRight);
    ui->jpgtls_y0disp->setFont(bold7pxfont);
    ui->jpgtls_angdisp->setText(QString::number(_field.angle));
    ui->jpgtls_angdisp->setAlignment(Qt::AlignRight);
    ui->jpgtls_angdisp->setFont(bold7pxfont);
    ui->jpgtls_filenamedisp->setText(_field.filename);
    ui->jpgtls_filenamedisp->setAlignment(Qt::AlignRight);
    ui->jpgtls_filenamedisp->setFont(bold7pxfont);
}

uiSAR::JPGFields uiSAR::readField()
{
    JPGFields _field;
    QString reader = ui->jpgtls_latdisp->text();
    _field.latitude = reader.toDouble();
    reader = ui->jpgtls_londisp->text();
    _field.longitude = reader.toDouble();
    reader = ui->jpgtls_dydisp->text();
    _field.dx = reader.toFloat();
    reader = ui->jpgtls_dxdisp->text();
    _field.dy = reader.toFloat();
    reader = ui->jpgtls_x0disp->text();
    _field.x0 = reader.toFloat();
    reader = ui->jpgtls_y0disp->text();
    _field.y0 = reader.toFloat();
    reader = ui->jpgtls_angdisp->text();
    _field.angle = reader.toFloat();
    reader = ui->jpgtls_filenamedisp->text();
    _field.filename = reader;
    return _field;
}

uiSAR::JPGFields uiSAR::decode_jpgs(QString path)
{
    JPGFields _field = { 0,0,0,0,0,0,0, "empty filename" };
    QFile f(path);


    if(f.open(QIODevice::ReadOnly)){
        QByteArray rawData = f.readAll();
        char *data = rawData.data();
        uint16_t *metaMarker = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE);

        if(*metaMarker == 0xE1FF){

            uint16_t *metaSize = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE + 2);
            *metaSize = qToBigEndian(*metaSize) - 2;

            memcpy(&_field, (data + JPEG_HEADER_SIZE + 4), *metaSize);
        }
        _field.filename = path;

        statusBar()->showMessage(tr("Декодирование метаданных успешно произведено"), 15000);
        update_jpgblocklabels_from_field(_field);
    }

    return _field;


}

void uiSAR::on_panButton_clicked()
{
    JPGFields _field = readField();
    if(_field.latitude != 0)
    {
        //QGeoCoordinate newcenter((float)_field.latitude, (float)_field.longitude);
        //emit toQMLpanButton(newcenter, _field.dx, _field.dy, _field.x0, _field.y0, _field.angle, _field.filename);
        statusBar()->showMessage(tr("Карта отцентрирована по широте и долготе радиолокационного изображения"), 15000);
        auto qml = ui->osmMap->rootObject();
        QMetaObject::invokeMethod(qml, "pan",
                Q_ARG(QVariant, (float)_field.latitude),
                Q_ARG(QVariant, (float)_field.longitude),
                Q_ARG(QVariant, _field.dx),
                Q_ARG(QVariant, _field.dy),
                Q_ARG(QVariant, _field.x0),
                Q_ARG(QVariant, _field.y0),
                Q_ARG(QVariant, _field.angle),
                Q_ARG(QVariant, _field.filename));
    }
    else {
        statusBar()->showMessage(tr("Широта и долгота изображения не распознаны"), 15000);
    }

}

void uiSAR::on_showButton_clicked()
{
    JPGFields _field = readField();
    if(_field.latitude != 0)
    {
        statusBar()->showMessage(tr("Изображение отображено на карте"), 15000);
        auto qml = ui->osmMap->rootObject();
        QString filename = imageList[fileCounter];
        QMetaObject::invokeMethod(qml, "addImage",
                Q_ARG(QVariant, (float)_field.latitude),
                Q_ARG(QVariant, (float)_field.longitude),
                Q_ARG(QVariant, _field.dx),
                Q_ARG(QVariant, _field.dy),
                Q_ARG(QVariant, _field.x0),
                Q_ARG(QVariant, _field.y0),
                Q_ARG(QVariant, _field.angle),
                Q_ARG(QVariant, filename)
                );
    }
    else {
        statusBar()->showMessage(tr("Широта и долгота изображения не распознаны"), 15000);
    }
}

void uiSAR::on_opacitySlider_sliderMoved(int position)
{
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "changeOpacityOfCurrentImage",
            Q_ARG(int, position));
}

void uiSAR::on_showCoordsBox_stateChanged(int arg1)
{
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "changeTooltipCheckBox",
            Q_ARG(QVariant, arg1));
}

bool uiSAR::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->udpIn)
    {
        if(event->type() == QKeyEvent::KeyPress)
        {
            QKeyEvent * ke = static_cast<QKeyEvent*>(event);
            if(ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
            {
                // [...]
                on_udpSendButton_clicked();
                return true; // do not process this event further
            }
        }
        return false; // process this event further
    }
    else
    {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(watched, event);
    }
}

void uiSAR::on_udpSendButton_clicked()
{
    QString commandUDP = ui->udpIn->toPlainText();
    ui->udpIn->clear();
    ui->udpDisp->setTextColor(Qt::cyan);
    ui->udpDisp->insertPlainText(">"+commandUDP+"\r\n");
    ui->udpDisp->setTextColor(Qt::white);
    qDebug()<<"UDP debug:: "<<commandUDP;
    if(commandUDP.startsWith("send"))
    {
        commandUDP.remove("send ");
        Telemery->Send(commandUDP.toUtf8());
    }
    if(commandUDP.startsWith("connect"))
    {
        commandUDP.remove("connect ");
        ui->udpDisp->setTextColor(Qt::blue);
        ui->udpDisp->insertPlainText("Address: "+commandUDP+"\r\n");
        ui->udpDisp->setTextColor(Qt::white);
        Telemery->Connect(commandUDP);

        ui->udpDisp->setTextColor(Qt::darkGreen);
        ui->udpDisp->insertPlainText("Successfully binded!\r\n");
        ui->udpDisp->setTextColor(Qt::white);
        qDebug()<< "Try to connect to" << commandUDP;
    }
    if(commandUDP=="start"||commandUDP=="begin")
    {
        on_pushButton_2_clicked();
    }
    if(commandUDP=="default"||commandUDP=="def")
    {
        on_pushButton_clicked();
    }
    if(commandUDP=="stop"||commandUDP=="st")
    {
        on_udpStopButton_clicked();
    }
    if(commandUDP=="clear"||commandUDP=="cc"||commandUDP=="clr"||commandUDP=="clearall")
    {
        ui->udpDisp->clear();
    }
    if(commandUDP==""||commandUDP=="rn")
    {
        ui->udpDisp->insertPlainText("\r\n");
    }
    if(commandUDP=="help"||commandUDP=="info"||commandUDP=="commandlist"||commandUDP=="commands")
    {
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("connect &ip:&port   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("binding connection to UDP server via server ip/port (e.g. connect 192.168.0.1:65535) \r\n");
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("clear   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("clearing console log, also works ");
        ui->udpDisp->setTextColor(Qt::darkMagenta);
        ui->udpDisp->insertPlainText("cc, clr, clearall \r\n");
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("send &string   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("sending string to connected UDP server (e.g. send hello world sends string *hello world* to server) \r\n");
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("rn   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("break line \r\n");
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("start ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("or ");
        ui->udpDisp->setTextColor(Qt::darkMagenta);
        ui->udpDisp->insertPlainText("begin   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("starts data reading from binded server \r\n");
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("default ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("or ");
        ui->udpDisp->setTextColor(Qt::darkMagenta);
        ui->udpDisp->insertPlainText("def   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("connects to default UDP server \r\n");
        ui->udpDisp->setTextColor(Qt::magenta);
        ui->udpDisp->insertPlainText("stop ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("or ");
        ui->udpDisp->setTextColor(Qt::darkMagenta);
        ui->udpDisp->insertPlainText("st   ");
        ui->udpDisp->setTextColor(Qt::darkGray);
        ui->udpDisp->insertPlainText("pauses data reading \r\n");

        ui->udpDisp->setTextColor(Qt::white);
    }
    QTextCursor c = ui->udpDisp->textCursor();
    c.movePosition(QTextCursor::End);
    ui->udpDisp->setTextCursor(c);
}

void uiSAR::on_placeMarkerButton_clicked()
{
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "prepareMarker"
            );
}

void uiSAR::on_pushButton_clicked()
{
    QString xmlAddress = ui->UDPIPxml->text();
    QString xmlPort = ui->UDPPortxml->text();
    ui->udpDisp->setTextColor(Qt::blue);
    ui->udpDisp->insertPlainText("Address: "+xmlAddress+":"+xmlPort+"\r\n");
    ui->udpDisp->setTextColor(Qt::darkGreen);
    ui->udpDisp->insertPlainText("Connecting to default server...\r\n");
    ui->udpDisp->setTextColor(Qt::white);
    Telemery->Connect(xmlAddress+":"+xmlPort);
}

void uiSAR::onTimer()
{
    Telemery->Send("update"); //int t =
}

void uiSAR::on_pushButton_2_clicked()
{
    ui->udpDisp->setTextColor(Qt::darkGreen);
    ui->udpDisp->insertPlainText("Beginning reading data...\r\n");
    ui->udpDisp->setTextColor(Qt::white);
    timer->start(500);
}

void uiSAR::on_udpStopButton_clicked()
{
    ui->udpDisp->setTextColor(Qt::darkRed);
    ui->udpDisp->insertPlainText("Reading paused\r\n");
    ui->udpDisp->setTextColor(Qt::white);
    timer->stop();
}

void uiSAR::on_panGPS_clicked()
{
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "panGPS");
}

void uiSAR::on_nav_follow_stateChanged(int arg1)
{
    if(arg1==2)
    {
        followPlane = true;
    }
    else { followPlane = false; }
}

void uiSAR::on_jpg_gright_clicked()
{
    if(fileCounter < imageList.size()-1){
        fileCounter++;
        decode_jpgs(imageList[fileCounter]);
    }
}

void uiSAR::on_jpg_gleft_clicked()
{
    if(fileCounter){
        fileCounter--;
        if(!imageList.empty()){
            decode_jpgs(imageList[fileCounter]);
        }
    }
}

void uiSAR::on_selectFolderButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Выберите папку с выходными изображениями РЛС"),
                                                     QStandardPaths::displayName(QStandardPaths::DesktopLocation));
    QStringList childDirectoryList;

    QDir parentDirectory(path);
    QDirIterator iterator(parentDirectory.path(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(iterator.hasNext()){
           iterator.next();
           childDirectoryList << iterator.filePath();
    }
    /*
     * 1. ☑ Нужно вместо qfilesystemmodel использовать класс, унаследованный от нее, с переопределенными методами data(), setData()
     * 2. Нужно реворкнуть кнопку <показать изображение>: она должна быть checkable, и менять свое состояние в зависимости от текущего выбранного изображения
     * 3. Изображения должны отображаться только однажды
     * 4. Кнопка показа изображения должна быть связанна с деревом
     * 5. При чеке\анчеке директории в дереве должны чекаться\анчекаться все изображения в этой директории
     */
    //QFileSystemModel *model = new QFileSystemModel;
    CheckableModel *model = new CheckableModel;
    model->setRootPath(parentDirectory.path());
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(parentDirectory.path()));

    QDir childDirectory(path);
    childDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    childDirectory.setNameFilters(QStringList("*.jpg"));

    QStringList fileList = childDirectory.entryList();

    if(!fileList.empty()){
        imageList.clear();
        for ( QString f : fileList  ){
            imageList.append(f.prepend(path+"/"));
        }

        ui->jpg_gright->setEnabled(true);
        ui->jpg_gleft->setEnabled(true);

        decode_jpgs(imageList[0]);
        ui->transformJPGbox->setEnabled(1);
        ui->groupBox->setEnabled(1);
    }else{
        statusBar()->showMessage(tr("Каталог с изображениями не распознан, повторите ввод через панель инструментов"), 15000);
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Неверный каталог!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("Изображения не найдены!");
        warningDialogue.exec();
    }
}

void uiSAR::on_nav_displayroute_stateChanged(int arg1)
{
    auto qml = ui->osmMap->rootObject();
        QMetaObject::invokeMethod(qml, "changeDrawRoute",
                Q_ARG(int, arg1));
}

void uiSAR::on_clearTrack_clicked()
{
    QMessageBox askForClearTrack;
    askForClearTrack.setWindowTitle("Очистка трека");
    askForClearTrack.setIcon(QMessageBox::Information);
    askForClearTrack.setText("Вы уверены, что хотите полностью очистить трек?");
    askForClearTrack.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForClearTrack.setDefaultButton(QMessageBox::Cancel);
    int ret = askForClearTrack.exec();
    auto qml = ui->osmMap->rootObject();
    switch (ret) {
      case QMessageBox::Yes: QMetaObject::invokeMethod(qml, "clearRoute");
          break;
      case QMessageBox::Cancel:
          break;
      default:
          // should never be reached
          break;
    }
}

void uiSAR::initUI(){

    ui->setupUi(this);
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    qInfo() << "                                        log start>>";
    qInfo() << "------------Session time: " << local << "--------------------------";
    if (QSslSocket::supportsSsl())
    {
        qInfo() << "OpenSSL detected: " << QSslSocket::supportsSsl() << ", OpenSSL build version: " << QSslSocket::sslLibraryBuildVersionString() << ", OpenSSL ver.: " << QSslSocket::sslLibraryVersionString();
    }
    else {
        qCritical() << "OpenSSL detected: " << QSslSocket::supportsSsl() << ", OpenSSL build version: " << QSslSocket::sslLibraryBuildVersionString() << ", OpenSSL ver.: " << QSslSocket::sslLibraryVersionString();
        QMessageBox openSSLDialogue;
        openSSLDialogue.setWindowTitle("Библиотека OpenSSL не обнаружена!");
        openSSLDialogue.setIcon(QMessageBox::Critical);
        openSSLDialogue.setText("Попробуйте переустановить программу.");
        openSSLDialogue.exec();
    }
    //ui->osmMap->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->osmMap->show();

    QFont bold8pxfont = ui->nav_latdisp->font();
    bold8pxfont.setPointSize(8);
    bold8pxfont.setBold(true);

    ui->nav_latdisp->setAlignment(Qt::AlignRight);
    ui->nav_latdisp->setFont(bold8pxfont);
    ui->nav_londisp->setAlignment(Qt::AlignRight);
    ui->nav_londisp->setFont(bold8pxfont);
    ui->nav_accdisp->setAlignment(Qt::AlignRight);
    ui->nav_accdisp->setFont(bold8pxfont);
    ui->nav_altdisp->setAlignment(Qt::AlignRight);
    ui->nav_altdisp->setFont(bold8pxfont);

    ui->udpIn->installEventFilter(this);

    /* Консоль для всех событий с поддержкой vt100 */

    //Console *con = new Console(ui->consoleMain, 10, 5);
    //con->write("Тест");
    //con->flush();
    //con->resize(ui->consoleMain->width(), ui->consoleMain->height());
    //con->hide(); // Закомментировать чтобы показать
}

void uiSAR::updateTelemetry(){

    QString infoHtml = "<font color=\"DarkGray\">";
    QString markupHtml = "<font color=\"Cyan\">";
    QString markup2Html = "<font color=\"DarkCyan\">";
    QString endHtml = "</font>";

    ui->udpDisp->setTextColor(Qt::darkGray);
    ui->udpDisp->insertPlainText("udp incoming telemetry: ");
    ui->udpDisp->setTextColor(Qt::darkYellow);

    QString tmp;
    tmp.sprintf("%0.6f", TelemetryData->lat);
    ui->nav_latdisp->setText(markupHtml+tmp+endHtml);
    ui->udpDisp->insertPlainText("LAT: "+tmp+"  ");
    tmp.sprintf("%0.6f", TelemetryData->lon);
    ui->nav_londisp->setText(markupHtml+tmp+endHtml);
    ui->udpDisp->insertPlainText("LON: "+tmp+"  ");
    tmp.sprintf("%0.1f", TelemetryData->speed);
    ui->nav_accdisp->setText(markup2Html+tmp+infoHtml+" км/ч"+endHtml);
    ui->udpDisp->insertPlainText("SPD: "+tmp+"  ");
    tmp.sprintf("%0.1f", TelemetryData->ele);
    ui->nav_altdisp->setText(markup2Html+tmp+infoHtml+" м"+endHtml);
    ui->udpDisp->insertPlainText("ELE: "+tmp+"\r\n");

    if(TelemetryData->lat != 0.0 && TelemetryData->lon != 0){
        auto qml = ui->osmMap->rootObject();
            QMetaObject::invokeMethod(qml, "drawRoute",
                    Q_ARG(QVariant, TelemetryData->lat),
                    Q_ARG(QVariant, TelemetryData->lon));
        if(followPlane)
        {
            on_panGPS_clicked();
        }
    }
}

void uiSAR::qmlDialogSlot(float markerLat, float markerLon)
{
    QString markerName = "Новый маркер";
    QColor markerColor = "white";
    qmlMarkerDialog md(this);
    if(md.exec() == QDialog::Accepted)
        {
            markerName = md.lineEdit1Text();
            markerColor = md.color();
            qDebug()<<"Marker placed at " << markerLat << ";  " << markerLon << ", NAME: " << markerName;
            auto qml = ui->osmMap->rootObject();
            QMetaObject::invokeMethod(qml, "addMarker",
                    Q_ARG(QVariant, markerLat),
                    Q_ARG(QVariant, markerLon),
                    Q_ARG(QVariant, markerName),
                    Q_ARG(QVariant, markerColor));
        }
}

void uiSAR::on_changeMapMode_toggled(bool checked)
{
    bool satellite = false;
    auto qml = ui->osmMap->rootObject();
    if(checked == true)
    {
       ui->changeMapMode->setText("Спутник");
       satellite = true;
       QMetaObject::invokeMethod(qml, "swapMapModes",
               Q_ARG(bool, satellite)
              );
    }
    else { ui->changeMapMode->setText("Схема");  satellite = false;
        QMetaObject::invokeMethod(qml, "swapMapModes",
                Q_ARG(bool, satellite)
               );}
}

void uiSAR::on_gpsPanClone_clicked()
{
    on_panGPS_clicked();
}

void uiSAR::on_t_up_clicked()
{
    double temp = ui->t_ySpin->value();
    ui->t_ySpin->setValue(temp+3);
}

void uiSAR::on_t_down_clicked()
{
    double temp = ui->t_ySpin->value();
    ui->t_ySpin->setValue(temp-3);
}

void uiSAR::on_t_left_clicked()
{
    double temp = ui->t_xSpin->value();
    ui->t_xSpin->setValue(temp-3);
}

void uiSAR::on_t_right_clicked()
{
    double temp = ui->t_xSpin->value();
    ui->t_xSpin->setValue(temp+3);
}

void uiSAR::on_t_xSpin_valueChanged(double arg1)
{
    auto qml = ui->osmMap->rootObject();
    if(arg1>=10000) {
        ui->t_right->setEnabled(false);
    }
    else if (arg1<10000)
    {
        ui->t_right->setEnabled(true);
    }
    if(arg1<=-10000) {
        ui->t_left->setEnabled(false);
    }
    else if (arg1>-10000)
    {
        ui->t_left->setEnabled(true);
    }
    double dx = arg1 - spinxArg0;
    //qDebug()<<arg1<<spinxArg0<<dx;
    spinxArg0 = arg1;
        QMetaObject::invokeMethod(qml, "transformX",
                Q_ARG(int, fileCounter),
                Q_ARG(double, dx)                  );
}

void uiSAR::on_t_ySpin_valueChanged(double arg1)
{
    auto qml = ui->osmMap->rootObject();
    if(arg1>=10000) {
        ui->t_up->setEnabled(false);
    }
    else if (arg1<10000)
    {
        ui->t_up->setEnabled(true);
    }
    if(arg1<=-10000) {
        ui->t_down->setEnabled(false);
    }
    else if (arg1>-10000)
    {
        ui->t_down->setEnabled(true);
    }
    double dy = arg1 - spinyArg0;
    spinyArg0 = arg1;
        QMetaObject::invokeMethod(qml, "transformY",
                Q_ARG(int, fileCounter),
                Q_ARG(double, dy)                  );
}

void uiSAR::on_t_sSpin_valueChanged(double arg1)
{
    auto qml = ui->osmMap->rootObject();
    double d = arg1-spinsArg0;
    spinsArg0 = arg1;
    QMetaObject::invokeMethod(qml, "transformScale",
            Q_ARG(int, fileCounter),
            Q_ARG(double, d));
}

void uiSAR::on_t_scale_valueChanged(int value)
{
    double temp = value;
    ui->t_sSpin->setValue(temp/100);
}

void uiSAR::loadSettings()
{
    QString t = config->value("telemetry/address").toString();
    double d;
    ui->UDPIPxml->setText(t);
    t = config->value("telemetry/port").toString();
    ui->UDPPortxml->setText(t);
    t = config->value("network/address").toString();
    ui->TCPIPxml->setText(t);
    t = config->value("network/port").toString();
    ui->TCPPortxml->setText(t);
    d = config->value("telemetry/updateTime").toDouble();
    ui->refreshtelemetryxml->setValue(d);
    d = config->value("map/predict_line_range").toDouble();
    ui->predictRangexml->setValue(d);
    d = config->value("map/capture_time").toDouble();
    ui->diaTimexml->setValue(d);
    d = config->value("map/diagram_length").toDouble();
    ui->diaRangexml->setValue(d);
    d = config->value("map/diagram_theta_azimuth").toDouble();
    ui->diaThetaAzimuth->setValue(d);
    d = config->value("map/diagram_drift_angle").toDouble();
    ui->diaDriftAngle->setValue(d);
    t = config->value("map/map_provider").toString();
    if(t=="google")
    {
        ui->providerGoogle->setChecked(1);
        ui->providerESRI->setChecked(0);
        ui->providerOSM->setChecked(0);
    } else if(t=="esri") {
        ui->providerESRI->setChecked(1);
        ui->providerOSM->setChecked(0);
        ui->providerGoogle->setChecked(0);
    } else if(t=="osm") {
        ui->providerOSM->setChecked(1);
        ui->providerESRI->setChecked(0);
        ui->providerGoogle->setChecked(0);
    }

    t = config->value("utility/version").toString();

    //to qml
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "loadSettings",
            Q_ARG(QVariant, config->value("map/map_provider").toString()),
            Q_ARG(double, config->value("map/diagram_theta_azimuth").toDouble()),
            Q_ARG(double, config->value("map/diagram_length").toDouble()),
            Q_ARG(double, config->value("map/diagram_drift_angle").toDouble()),
            Q_ARG(double, config->value("map/capture_time").toDouble()),
            Q_ARG(double, config->value("map/predict_line_range").toDouble()));

    qInfo()<<"Config loaded. Version "<<t;

}

void uiSAR::on_saveSettings_clicked()
{
    config->setValue("telemetry/address", ui->UDPIPxml->text());
    config->setValue("telemetry/port", ui->UDPPortxml->text());
    config->setValue("network/address", ui->TCPIPxml->text());
    config->setValue("network/port", ui->TCPPortxml->text());
    config->setValue("telemetry/updateTime", ui->refreshtelemetryxml->value());
    config->setValue("map/predict_line_range", ui->predictRangexml->value());
    config->setValue("map/capture_time", ui->diaTimexml->value());
    config->setValue("map/diagram_length", ui->diaRangexml->value());
    config->setValue("map/diagram_theta_azimuth", ui->diaThetaAzimuth->value());
    config->setValue("map/diagram_drift_angle", ui->diaDriftAngle->value());
    //
    if(ui->providerGoogle->isChecked()) { config->setValue("map/map_provider", "google"); } else if (ui->providerESRI->isChecked()) { config->setValue("map/map_provider", "esri"); }
    else if (ui->providerOSM->isChecked()) { config->setValue("map/map_provider", "osm"); }

    //to qml
    auto qml = ui->osmMap->rootObject();
    //провайдера карты можно менять только при перезапуске
    QMetaObject::invokeMethod(qml, "loadSettings",
            Q_ARG(QVariant, config->value("map/map_provider").toString()),
            Q_ARG(double, config->value("map/diagram_theta_azimuth").toDouble()),
            Q_ARG(double, config->value("map/diagram_length").toDouble()),
            Q_ARG(double, config->value("map/diagram_drift_angle").toDouble()),
            Q_ARG(double, config->value("map/capture_time").toDouble()),
            Q_ARG(double, config->value("map/predict_line_range").toDouble()));
    qInfo()<<"Config saved.";
    QMessageBox notifyAboutRestart;
    notifyAboutRestart.setWindowTitle("Сохранение настроек");
    notifyAboutRestart.setIcon(QMessageBox::Information);
    notifyAboutRestart.setText("Провайдер карт изменится при перезапуске программы.");
    notifyAboutRestart.setStandardButtons(QMessageBox::Yes);
    notifyAboutRestart.setDefaultButton(QMessageBox::Yes);
    notifyAboutRestart.exec();
}

void uiSAR::on_discardSettings_clicked()
{

    QMessageBox askForDiscardSettings;
    askForDiscardSettings.setWindowTitle("Отмена изменений");
    askForDiscardSettings.setIcon(QMessageBox::Question);
    askForDiscardSettings.setText("Вы уверены, что хотите отменить изменения настроек?");
    askForDiscardSettings.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    askForDiscardSettings.setDefaultButton(QMessageBox::Cancel);
    int ret = askForDiscardSettings.exec();
    switch (ret) {
      case QMessageBox::Yes: loadSettings();
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }
}

void uiSAR::on_t_rSpin_valueChanged(double arg1)
{
    auto qml = ui->osmMap->rootObject();
    double d = arg1-spinrArg0;
    spinrArg0 = arg1;
    QMetaObject::invokeMethod(qml, "transformRotate",
            Q_ARG(int, fileCounter),
            Q_ARG(double, d));
}

void uiSAR::on_t_rotation_valueChanged(int value)
{
    ui->t_rSpin->setValue(value);
}

void uiSAR::on_rulerButton_clicked()
{
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "rulerHandler");
}
