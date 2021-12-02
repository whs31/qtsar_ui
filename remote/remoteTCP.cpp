#include "remoteTCP.h"
#include <QDebug>

RemoteTCP::RemoteTCP()
{
    socket = new QTcpSocket( this );
    connect(socket,SIGNAL(readyRead()), this, SLOT(readSlot()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnectSlot()));
}

int RemoteTCP::Connect(QString addr){

    QStringList l = addr.split(":");
    socket->connectToHost(l[0], l[1].toInt());

    if( socket->waitForConnected(3000) ) {
        Status = CONNECTED;
        return 0;
    }
    Status = DISCONNECTED;
    qDebug() << "Connection timeout";
    return -1;
}

int RemoteTCP::Disconnect(){
    Status = DISCONNECTED;
    socket->close();
    emit this->disconnected();
    return 0;
}

int RemoteTCP::Send(QByteArray data){
    int n = socket->write(data);
    socket->waitForBytesWritten();
    return n;
}

void RemoteTCP::readSlot(){
    emit this->received(socket->readAll());
}

void RemoteTCP::disconnectSlot(){
    Status = DISCONNECTED;
    emit this->disconnected();
}
