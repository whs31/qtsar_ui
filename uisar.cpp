#include "uisar.h"
#include "ui_uisar.h"


template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

void uiSAR::ReadTelemetry(QByteArray data){

    // Тут приходят данные телеметрии
    TelemetryData = reinterpret_cast<TelemetryData_t*>(data.data());
    qDebug() << data;

    updateTelemetry();

}


uiSAR::uiSAR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::uiSAR)
{
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    qInfo() << "Logging data...";
    qInfo() << "------------Session time: " << local << "--------------------------";
    qWarning() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

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
    if(jpg.open(QIODevice::ReadOnly))
    {
        QByteArray rawData = jpg.readAll();
        statusBar()->showMessage(tr("Сформирован массив байтов из изображения"), 1000);
        if (rawData.at(20) == (char)0xFF && rawData.at(21) == (char)0xE1)
        {
            statusBar()->showMessage(tr("Совпадение заголовка JPEG"), 1000);
            unsigned char buf16[2];
            buf16[0] = rawData[22];
            buf16[1] = rawData[23];
            short meta_sizeLittleEndian;
            memcpy(&meta_sizeLittleEndian, &buf16, sizeof(buf16));
            short meta_size = swap_endian<uint16_t>(meta_sizeLittleEndian)-2;
            if(meta_size >= 36)
            {
                unsigned char buf64[8];
                for (int i = 0; i <= 7; i++)
                {
                    buf64[i] = rawData[24 + i];
                }
                double lat_LE;
                memcpy(&lat_LE, &buf64, sizeof(buf64));
                _field.latitude = lat_LE;
                for (int i = 0; i <= 7; i++)
                {
                    buf64[i] = rawData[24 + 8 + i];
                }
                double lon_LE;
                memcpy(&lon_LE, &buf64, sizeof(buf64));
                _field.longitude = lon_LE;
                unsigned char buf32[4];
                for (int i = 0; i <= 7-4; i++)
                {
                    buf32[i] = rawData[24 + 8 + 8 + i];
                }
                float dx;
                memcpy(&dx, &buf32, sizeof(buf32));
                _field.dx = dx;
                for (int i = 0; i <= 7 - 4; i++)
                {
                    buf32[i] = rawData[24 + 8 + 8 + 4 + i];
                }
                float dy;
                memcpy(&dy, &buf32, sizeof(buf32));
                _field.dy = dy;
                for (int i = 0; i <= 7 - 4; i++)
                {
                    buf32[i] = rawData[24 + 8 + 8 + 4 + 4 + i];
                }
                float x0;
                memcpy(&x0, &buf32, sizeof(buf32));
                _field.x0 = x0;
                for (int i = 0; i <= 7 - 4; i++)
                {
                    buf32[i] = rawData[24 + 8 + 8 + 4 + 4 + 4 + i];
                }
                float y0;
                memcpy(&y0, &buf32, sizeof(buf32));
                _field.y0 = y0;
                for (int i = 0; i <= 7 - 4; i++)
                {
                    buf32[i] = rawData[24 + 8 + 8 + 4 + 4 + 4 + 4 + i];
                }
                float angle;
                memcpy(&angle, &buf32, sizeof(buf32));
                qDebug() << _field.latitude << _field.longitude << _field.dx << _field.dy << _field.x0 << _field.y0 << _field.angle;
                statusBar()->showMessage(tr("Декодирование метаданных успешно произведено"), 15000);
                QFileInfo fi(jpg.fileName());
                _field.filename = fi.fileName();
                update_jpgblocklabels_from_field(_field);
            }
        }
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

    ui->osmMap->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
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
    tmp.sprintf("%s%0.1f</font><br>", markupHtml, TelemetryData->lat);
    ui->nav_latdisp->setText(tmp);

    tmp.sprintf("%s%0.1f</font><br>", markupHtml, TelemetryData->lon);
    ui->nav_londisp->setText(tmp);

    tmp.sprintf("%s%0.1f км/ч</font><br>", markupHtml, TelemetryData->speed);
    ui->nav_accdisp->setText(tmp);

    tmp.sprintf("%s%0.1f м</font><br>", markupHtml, TelemetryData->ele);
    ui->nav_altdisp->setText(tmp);

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
