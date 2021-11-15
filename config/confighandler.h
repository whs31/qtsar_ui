#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QObject>

#include "uisar.h"
#include "ui_uisar.h"
#include "config/config.h"
class uiSAR;

class ConfigHandler
{
public:
    ConfigHandler();

    void loadSettings();
    void saveSettings();
    void discardSettings();

    Config *config;

private:
    uiSAR *mainWindow;

};

#endif // CONFIGHANDLER_H
