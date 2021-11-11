#include "confighandler.h"

ConfigHandler::ConfigHandler()
{
    mainWindow = uiSAR::getMainWinPtr();
    config = new Config(QCoreApplication::applicationDirPath()+"/config.ini");
    qInfo()<<"ConfigHandler initialized.";
}

void ConfigHandler::loadSettings()
{
    QString t = config->value("telemetry/address").toString();
    double d;
    mainWindow->ui->UDPIPxml->setText(t);
    t = config->value("telemetry/port").toString();
    mainWindow->ui->UDPPortxml->setText(t);
    t = config->value("network/address").toString();
    mainWindow->ui->TCPIPxml->setText(t);
    t = config->value("network/port").toString();
    mainWindow->ui->TCPPortxml->setText(t);
    d = config->value("telemetry/updateTime").toDouble();
    mainWindow->ui->refreshtelemetryxml->setValue(d);
    d = config->value("map/predict_line_range").toDouble();
    mainWindow->ui->predictRangexml->setValue(d);
    d = config->value("map/capture_time").toDouble();
    mainWindow->ui->diaTimexml->setValue(d);
    d = config->value("map/diagram_length").toDouble();
    mainWindow->ui->diaRangexml->setValue(d);
    d = config->value("map/diagram_theta_azimuth").toDouble();
    mainWindow->ui->diaThetaAzimuth->setValue(d);
    d = config->value("map/diagram_drift_angle").toDouble();
    mainWindow->ui->diaDriftAngle->setValue(d);
    t = config->value("map/map_provider").toString();
    if(t=="google")
    {
        mainWindow->ui->providerGoogle->setChecked(1);
        mainWindow->ui->providerESRI->setChecked(0);
        mainWindow->ui->providerOSM->setChecked(0);
    } else if(t=="esri") {
        mainWindow->ui->providerESRI->setChecked(1);
        mainWindow->ui->providerOSM->setChecked(0);
        mainWindow->ui->providerGoogle->setChecked(0);
    } else if(t=="osm") {
        mainWindow->ui->providerOSM->setChecked(1);
        mainWindow->ui->providerESRI->setChecked(0);
        mainWindow->ui->providerGoogle->setChecked(0);
    }

    t = config->value("utility/version").toString();

    //to qml
    auto qml = mainWindow->ui->osmMap->rootObject();
    QMetaObject::invokeMethod(qml, "loadSettings",
            Q_ARG(QVariant, config->value("map/map_provider").toString()),
            Q_ARG(double, config->value("map/diagram_theta_azimuth").toDouble()),
            Q_ARG(double, config->value("map/diagram_length").toDouble()),
            Q_ARG(double, config->value("map/diagram_drift_angle").toDouble()),
            Q_ARG(double, config->value("map/capture_time").toDouble()),
            Q_ARG(double, config->value("map/predict_line_range").toDouble()));

    qInfo()<<"Config loaded. Version "<<t;

}

void ConfigHandler::saveSettings()
{
    config->setValue("telemetry/address", mainWindow->ui->UDPIPxml->text());
    config->setValue("telemetry/port", mainWindow->ui->UDPPortxml->text());
    config->setValue("network/address", mainWindow->ui->TCPIPxml->text());
    config->setValue("network/port", mainWindow->ui->TCPPortxml->text());
    config->setValue("telemetry/updateTime", mainWindow->ui->refreshtelemetryxml->value());
    config->setValue("map/predict_line_range", mainWindow->ui->predictRangexml->value());
    config->setValue("map/capture_time", mainWindow->ui->diaTimexml->value());
    config->setValue("map/diagram_length", mainWindow->ui->diaRangexml->value());
    config->setValue("map/diagram_theta_azimuth", mainWindow->ui->diaThetaAzimuth->value());
    config->setValue("map/diagram_drift_angle", mainWindow->ui->diaDriftAngle->value());
    //
    if(mainWindow->ui->providerGoogle->isChecked()) { config->setValue("map/map_provider", "google"); } else if (mainWindow->ui->providerESRI->isChecked()) { config->setValue("map/map_provider", "esri"); }
    else if (mainWindow->ui->providerOSM->isChecked()) { config->setValue("map/map_provider", "osm"); }

    //to qml
    auto qml = mainWindow->ui->osmMap->rootObject();
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

void ConfigHandler::discardSettings()
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
