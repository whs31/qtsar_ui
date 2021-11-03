#ifndef REMOTEUDP_H
#define REMOTEUDP_H
#include "remote.h"
#include <QUdpSocket>

class RemoteUDP : public Remote
{
    Q_OBJECT
public:
    RemoteUDP();
    ~RemoteUDP();
    int Connect(QString addr);
    int Disconnect();
    int Send(QByteArray data);

private:
    quint16 port;
    QHostAddress host;
    QUdpSocket *socket;

private slots:
    void readyRead();
};

#endif // REMOTEUDP_H
