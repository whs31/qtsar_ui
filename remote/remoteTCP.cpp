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
        return 0;
    }
    qDebug() << "Connection timeout";
    return -1;
}

int RemoteTCP::Disconnect(){
    socket->close();
    emit this->disconnected();
    return 0;
}

int RemoteTCP::Send(QByteArray data){
    return socket->write(data);
}

void RemoteTCP::readSlot(){
    emit this->received(socket->readAll());
}

void RemoteTCP::disconnectSlot(){
    emit this->disconnected();
}
