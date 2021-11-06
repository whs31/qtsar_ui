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
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/config.ini",
                             QSettings::IniFormat);
    settings->setValue("header/version", "1106");


    /* Интерфейс для получения телеметрии */
    Telemery = RemoteAuto("UDP");
    connect(Telemery, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    // Console test
    /*
    Remote *c = RemoteAuto("TCP");
    c->Connect("127.0.0.1:2222");
    c->Send("test");

    connect(c, SIGNAL(received(QByteArray)), this, SLOT(ReadExec(QByteArray)));
    */
    initUI();
    loadSettings();
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
                Q_ARG(QVariant, filename));
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
    QString path = QFileDialog::getExistingDirectory(this, "Выберите папку с выходными изображениями РЛС",
                                                     QStandardPaths::displayName(QStandardPaths::PicturesLocation),
                                                     QFileDialog::ShowDirsOnly);
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    dir.setNameFilters(QStringList("*.jpg"));

    QStringList fileList = dir.entryList();

    if(!fileList.empty()){
        imageList.clear();
        for ( QString f : fileList  ){
            imageList.append(f.prepend(path+"/"));
        }

        ui->jpg_gright->setEnabled(true);
        ui->jpg_gleft->setEnabled(true);

        decode_jpgs(imageList[0]);
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
    tmp.asprintf("%0.6f", TelemetryData->lat);
    ui->nav_latdisp->setText(markupHtml+tmp+endHtml);
    ui->udpDisp->insertPlainText("LAT: "+tmp+"  ");
    tmp.asprintf("%0.6f", TelemetryData->lon);
    ui->nav_londisp->setText(markupHtml+tmp+endHtml);
    ui->udpDisp->insertPlainText("LON: "+tmp+"  ");
    tmp.asprintf("%0.1f", TelemetryData->speed);
    ui->nav_accdisp->setText(markup2Html+tmp+infoHtml+" км/ч"+endHtml);
    ui->udpDisp->insertPlainText("SPD: "+tmp+"  ");
    tmp.asprintf("%0.1f", TelemetryData->ele);
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
    QString t = settings->value("telemetry/udp_ip_default").toString();
    double d;
    ui->UDPIPxml->setText(t);
    t = settings->value("telemetry/udp_port_default").toString();
    ui->UDPPortxml->setText(t);
    t = settings->value("telemetry/tcp_ip_default").toString();
    ui->TCPIPxml->setText(t);
    t = settings->value("telemetry/tcp_port_default").toString();
    ui->TCPPortxml->setText(t);
    d = settings->value("telemetry/refresh_telemetry_time").toDouble();
    ui->refreshtelemetryxml->setValue(d);
    d = settings->value("map/predict_line_range").toDouble();
    ui->predictRangexml->setValue(d);
    d = settings->value("map/capture_time").toDouble();
    ui->diaTimexml->setValue(d);
    d = settings->value("map/diagram_length").toDouble();
    ui->diaRangexml->setValue(d);
    d = settings->value("map/diagram_theta_azimuth").toDouble();
    ui->diaThetaAzimuth->setValue(d);
    d = settings->value("map/diagram_drift_angle").toDouble();
    ui->diaDriftAngle->setValue(d);
    t = settings->value("map/map_provider").toString();
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
    t = settings->value("header/version").toString();

    //to qml
    auto qml = ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "loadSettings",
            Q_ARG(QVariant, settings->value("map/map_provider").toString()),
            Q_ARG(double, settings->value("map/diagram_theta_azimuth").toDouble()),
            Q_ARG(double, settings->value("map/diagram_length").toDouble()),
            Q_ARG(double, settings->value("map/diagram_drift_angle").toDouble()),
            Q_ARG(double, settings->value("map/capture_time").toDouble()),
            Q_ARG(double, settings->value("map/predict_line_range").toDouble()));

    qInfo()<<"Config loaded. Version "<<t;

}

void uiSAR::on_UDPIPxml_textChanged(const QString &arg1)
{
    settings->setValue("telemetry/udp_ip_default", arg1);
}

void uiSAR::on_UDPPortxml_textChanged(const QString &arg1)
{
    settings->setValue("telemetry/udp_port_default", arg1);
}

void uiSAR::on_TCPIPxml_textChanged(const QString &arg1)
{
    settings->setValue("telemetry/tcp_ip_default", arg1);
}

void uiSAR::on_TCPPortxml_textChanged(const QString &arg1)
{
    settings->setValue("telemetry/tcp_port_default", arg1);
}

void uiSAR::on_refreshtelemetryxml_valueChanged(double arg1)
{
    settings->setValue("telemetry/refresh_telemetry_time", arg1);
}

void uiSAR::on_predictRangexml_valueChanged(double arg1)
{
    settings->setValue("map/predict_line_range", arg1);
}

void uiSAR::on_diaTimexml_valueChanged(double arg1)
{
    settings->setValue("map/capture_time", arg1);
}

void uiSAR::on_diaRangexml_valueChanged(double arg1)
{
    settings->setValue("map/diagram_length", arg1);
}

void uiSAR::on_diaThetaAzimuth_valueChanged(double arg1)
{
    settings->setValue("map/diagram_theta_azimuth", arg1);
}

void uiSAR::on_diaDriftAngle_valueChanged(double arg1)
{
    settings->setValue("map/diagram_drift_angle", arg1);
}

void uiSAR::on_providerGoogle_clicked()
{
    settings->setValue("map/map_provider", "google");
}

void uiSAR::on_providerESRI_clicked()
{
    settings->setValue("map/map_provider", "esri");
}

void uiSAR::on_providerOSM_clicked()
{
    settings->setValue("map/map_provider", "osm");
}
