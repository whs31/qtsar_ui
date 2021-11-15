/*-----Текущие проблемы/то, что нужно доделать-----
 *
 * Линейка не удаляет после использования метки
 * В линейке нужно добавить надпись, параллельную rulerLine, с отображением расстояния
 * ☑Все отображение РЛИ нужно переделать и перенести в отдельный класс
 * Чекбоксы в дереве изображений не работают
 * При изменении в конфиге провайдера карт нужно закрывать приложение, также нужно выводить предупреждение при попытке изменить конфиг при наличии коннекта с телеметрией (но не закрывать приложение)
 * При клике на изображение оно должно возвращать в мейн класс fileCounter
 *
 * */


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
    //config = new Config(QCoreApplication::applicationDirPath()+"/config.ini");
    configHandler = new ConfigHandler();
    imageProcessing = new ImageProcessing();
    /* Интерфейс для получения телеметрии */
    Telemery = RemoteAuto( configHandler->config->value("telemetry/type").toString() );
    connect(Telemery, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    /* Интерфейс для запуска/чтения вывода процессов на РМ */
    QString execdIP = configHandler->config->value("execd/address").toString();
    QString execdPort = configHandler->config->value("execd/port").toString();
    QString execAddr = execdIP + ":" + execdPort;
    QString connectStatus = "connect to " + execAddr + " ";
    Execd = RemoteAuto(configHandler->config->value("execd/type").toString());

    initUI();
    configHandler->loadSettings();
    qml = ui->osmMap->rootObject();


    if(Execd->Connect(execAddr) != -1){
        connectStatus.append("OK");
    }else{
        connectStatus.append("Error");
    }

    ui->consoleMain->write(connectStatus.toUtf8());
    ui->consoleMain->flush();

    connect(Execd, SIGNAL(received(QByteArray)), this, SLOT(ReadExec(QByteArray)));

}

uiSAR::~uiSAR()
{
    delete ui;
}

uiSAR *uiSAR::getMainWinPtr()
{
    return pMainWindow;
}

void uiSAR::on_panButton_clicked()
{
    if(imageProcessing->getReadyStatus())
    {
        ImageProcessing::image_metadata meta = imageProcessing->getMetaList();
        if(meta.latitude != 0)
        {
            statusBar()->showMessage(tr("Карта отцентрирована по широте и долготе радиолокационного изображения"), 15000);
            QMetaObject::invokeMethod(qml, "pan",
                Q_ARG(QVariant, (float)meta.latitude),
                Q_ARG(QVariant, (float)meta.longitude),
                Q_ARG(QVariant, meta.dx),
                Q_ARG(QVariant, meta.dy),
                Q_ARG(QVariant, meta.x0),
                Q_ARG(QVariant, meta.y0),
                Q_ARG(QVariant, meta.angle),
                Q_ARG(QVariant, meta.filename));
        } else {
            statusBar()->showMessage(tr("Широта и долгота изображения не распознаны"), 15000);
        }
    } else {
        statusBar()->showMessage(tr("Радиолокационное изображение не найдено"), 15000);
    }
}

void uiSAR::on_opacitySlider_sliderMoved(int position)
{
    QMetaObject::invokeMethod(qml, "changeOpacityOfCurrentImage",
            Q_ARG(int, position));
}

void uiSAR::on_showCoordsBox_stateChanged(int arg1)
{
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
    imageProcessing->goRight();
}

void uiSAR::on_jpg_gleft_clicked()
{
    imageProcessing->goLeft();
}

void uiSAR::on_selectFolderButton_clicked()
{
    imageProcessing->processPath(QFileDialog::getExistingDirectory(this, tr("Выберите папку с выходными изображениями РЛС"),
                                                                   QStandardPaths::displayName(QStandardPaths::DesktopLocation)));
}

void uiSAR::on_nav_displayroute_stateChanged(int arg1)
{
    QMetaObject::invokeMethod(qml, "changeDrawRoute", Q_ARG(int, arg1));
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
    ui->consoleMain->setExecd(Execd);

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
                Q_ARG(int, imageProcessing->getFileCounter()),
                Q_ARG(double, dy)                  );
}

void uiSAR::on_t_sSpin_valueChanged(double arg1)
{
    double d = arg1-spinsArg0;
    spinsArg0 = arg1;
    QMetaObject::invokeMethod(qml, "transformScale",
            Q_ARG(int, imageProcessing->getFileCounter()),
            Q_ARG(double, d));
}

void uiSAR::on_t_scale_valueChanged(int value)
{
    double temp = value;
    ui->t_sSpin->setValue(temp/100);
}

void uiSAR::on_saveSettings_clicked()
{
    configHandler->saveSettings();
}

void uiSAR::on_discardSettings_clicked()
{

    configHandler->discardSettings();
}

void uiSAR::on_t_rSpin_valueChanged(double arg1)
{
    double d = arg1-spinrArg0;
    spinrArg0 = arg1;
    QMetaObject::invokeMethod(qml, "transformRotate",
            Q_ARG(int, imageProcessing->getFileCounter()),
            Q_ARG(double, d));
}

void uiSAR::on_t_rotation_valueChanged(int value)
{
    ui->t_rSpin->setValue(value);
}

void uiSAR::on_rulerButton_clicked()
{
    QMetaObject::invokeMethod(qml, "rulerHandler");
}

void uiSAR::on_execd_in_returnPressed()
{
    Execd->Send(ui->execd_in->text().toUtf8()); // Запуск удаленной команды execd
}
