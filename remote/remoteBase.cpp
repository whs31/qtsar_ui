#include "remoteBase.h"

Remote* RemoteAuto(QString type){
    QStringList types;
    types << "UDP" << "TCP" << "COM";

    Remote *r = NULL;
    switch (types.indexOf(type)) {
    case 0:
        r = new RemoteUDP();
        break;
    case 1:
        r = new RemoteTCP();
        break;
    default:
        qDebug() << "Не верный тип связи с удаленным хостом:" << type;
        break;
    }
    return r;

}
