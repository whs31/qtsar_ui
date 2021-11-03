#include "uisar.h"
#include "ui_uisar.h"
#include "qmlmarkerdialog.h"

void uiSAR::ReadTelemetry(QByteArray data){

    // Тут приходят данные телеметрии
    TelemetryData = reinterpret_cast<TelemetryData_t*>(data.data());
    qDebug() << data;
    updateTelemetry();

}


uiSAR * uiSAR::pMainWindow;
uiSAR::uiSAR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::uiSAR)
{
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    qInfo() << "Logging data...";
    qInfo() << "------------Session time: " << local << "--------------------------";
    qWarning() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    pMainWindow = this;
    initUI();

    /* Интерфейс для получения телеметрии */
    Telemery = RemoteAuto("UDP");
    connect(Telemery, SIGNAL(received(QByteArray)), this, SLOT(ReadTelemetry(QByteArray)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

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
    QFile jpg;
    QString _fileCounter = QString::number(fileCounter);
    jpg.setFileName(path + "/" + _fileCounter + ".jpg");

    if(jpg.open(QIODevice::ReadOnly)){
        QByteArray rawData = jpg.readAll();
        char *data = rawData.data();
        uint16_t *metaMarker = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE);

        if(*metaMarker == 0xE1FF){

            uint16_t *metaSize = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE + 2);
            *metaSize = qToBigEndian(*metaSize) - 2;

            memcpy(&_field, (data + JPEG_HEADER_SIZE + 4), *metaSize);
        }

        QFileInfo fi(jpg.fileName());
        _field.filename = fi.fileName();

        statusBar()->showMessage(tr("Декодирование метаданных успешно произведено"), 15000);
        update_jpgblocklabels_from_field(_field);
    }

    return _field;

}

void uiSAR::on_DecodeJPG_clicked()
{
    decode_jpgs(jpg_path);
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
        QString _fileCounter = QString::number(fileCounter);
        QString filename = jpg_path + "/" + _fileCounter + ".jpg";
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

        Telemery->Connect(commandUDP);

        ui->udpDisp->setTextColor(Qt::darkGreen);
        ui->udpDisp->insertPlainText("Successfully binded!\r\n");
        ui->udpDisp->setTextColor(Qt::white);
        qDebug()<< "Try to connect to" << commandUDP;
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
    bool ok;
    QString strPort = ui->UDPPortxml->text();
    quint16 xmlPort = strPort.toUShort(&ok, 10);
}

void uiSAR::onTimer()
{
    int t = Telemery->Send("update");
}

void uiSAR::on_pushButton_2_clicked()
{

    timer->start(500);
}

void uiSAR::on_udpStopButton_clicked()
{
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
    if(fileCounter==1)
    {
        ui->jpg_gleft->setEnabled(true);
    }
    fileCounter++;
    if(fileCounter==totalJPGDetected)
    {
        ui->jpg_gright->setEnabled(false);
    }
    on_DecodeJPG_clicked();
}

void uiSAR::on_jpg_gleft_clicked()
{
    if(fileCounter==totalJPGDetected)
    {
        ui->jpg_gright->setEnabled(true);
    }
    fileCounter--;
    if(fileCounter==1)
    {
        ui->jpg_gleft->setEnabled(false);
    }
    on_DecodeJPG_clicked();
}

void uiSAR::on_detect_refresh_clicked()
{
    if(allowRefresh)
    {
        on_selectFolderButton_clicked();
    }
}

void uiSAR::on_selectFolderButton_clicked()
{
    jpg_path = QFileDialog::getExistingDirectory(this, "Выберите папку с выходными изображениями РЛС", QStandardPaths::displayName(QStandardPaths::PicturesLocation), QFileDialog::ShowDirsOnly);
    //
    QFile jpg;
    //
    fileCounter = 1;
    QString _fileCounter = QString::number(fileCounter);
    jpg.setFileName(jpg_path + "/" + _fileCounter + ".jpg");
    if(jpg.exists())
    {
        statusBar()->showMessage(tr("Каталог с изображениями распознан"), 15000);
        for(fileCounter = 1; fileCounter<100; fileCounter++)
        {
            QFile trackJPGs;
            _fileCounter = QString::number(fileCounter);
            trackJPGs.setFileName(jpg_path + "/" + _fileCounter + ".jpg");
            if(trackJPGs.exists())
            {
                totalJPGDetected = fileCounter;
                QFont bold7pxfont = ui->nav_latdisp->font();
                ui->detect_detecteddisp->setText(_fileCounter);
                ui->jpg_gright->setEnabled(true);
                ui->jpg_gleft->setEnabled(false);
                allowRefresh = true;
            } else {
                fileCounter = 1;
                on_DecodeJPG_clicked();
                break;
            }
        }
    }
    else
    {
        statusBar()->showMessage(tr("Каталог с изображениями не распознан, повторите ввод через панель инструментов"), 15000);
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Неверный каталог!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("Укажите верный каталог поиска изображений!");
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
}


void uiSAR::updateTelemetry(){

    char* infoHtml = "<font color=\"DarkGray\">";
    char* markupHtml = "<font color=\"Cyan\">";
    char* markup2Html = "<font color=\"DarkCyan\">";
    char* endHtml = "</font><br>";

    QString tmp;
    //double t = TelemetryData->lat;
    //tmp = QString::number(t);
    tmp.sprintf("%0.1f", TelemetryData->lat);
    ui->nav_latdisp->setText(markupHtml+tmp+endHtml);
    //t = TelemetryData->lon;
    //tmp = QString::number(t);
    tmp.sprintf("%0.1f", TelemetryData->lon);
    ui->nav_londisp->setText(markupHtml+tmp+endHtml);
    //t = TelemetryData->speed;
    //tmp = QString::number(t);

    tmp.sprintf("%0.1f", TelemetryData->speed);
    ui->nav_accdisp->setText(markup2Html+tmp+endHtml+infoHtml+" км/ч"+endHtml);
    //t = TelemetryData->ele;
    //tmp = QString::number(t);
    tmp.sprintf("%0.1f", TelemetryData->ele);
    ui->nav_altdisp->setText(markup2Html+tmp+endHtml+infoHtml+" м"+endHtml);

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
