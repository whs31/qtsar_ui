#include "config.h"
#include <QDebug>

Config::Config(QString fn) : QSettings(fn, QSettings::IniFormat)
{
    /*
     * Тут проверяется наличие параметров в конфиг файле.
     * Если параметр отсутствует, то класс восполнит файл стандартными настройками
     *
     * Заполнять стандартные параметры рекомендуется так:
     * group_t <Название группы>;
     * <Название группы>["<Название параметра>"] = "<Значение>";
     * checkValuesSimple(<Название группы>);
     */

    group_t telemetry;
    telemetry["type"] = "UDP";
    telemetry["address"] = "127.0.0.1:5599";
    telemetry["updateTime"] = "0.5";
    checkValuesSimple(telemetry);

    group_t map;
    map["predict_line_range"] = "0";
    map["capture_time"] = "0";
    map["diagram_length"] = "0";
    map["diagram_theta_azimuth"] = "0";
    map["diagram_drift_angle"] = "0";
    map["map_provider"] = "google";
    checkValuesSimple(map);

}


void Config::checkValues(QString group, group_t *list){

    QMapIterator<QString, QString> i(*list);

    beginGroup(group);
    while (i.hasNext()) {
        i.next();
        if(!value(i.key()).isValid()){
            setValue(i.key(), i.value());
        }
    }
    endGroup();
    list->clear();

}
