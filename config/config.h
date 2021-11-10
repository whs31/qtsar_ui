#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <QMap>

class Config : public QSettings
{
    Q_OBJECT

#define group_t QMap<QString,QString>
#define checkValuesSimple(X) checkValues(#X, &X)

public:
    Config(QString fn = "default.cfg");

private:
    void checkValues(QString group, group_t *list);

};

#endif // CONFIG_H
