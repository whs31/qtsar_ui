#ifndef REMOTETCP_H
#define REMOTETCP_H
#include "remote.h"
#include <QTcpSocket>

class RemoteTCP : public Remote
{
    Q_OBJECT
public:
    RemoteTCP();
    int Connect(QString addr);
    int Disconnect();
    int Send(QByteArray data);

private:
    QTcpSocket *socket;

private slots:
    void readSlot();
    void disconnectSlot();
};

#endif // REMOTETCP_H
