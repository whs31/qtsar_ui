#include "remoteUDP.h"
#include <QDebug>

RemoteUDP::RemoteUDP()
{
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

RemoteUDP::~RemoteUDP()
{
    socket->close();
    delete socket;
}

int RemoteUDP::Connect(QString addr){
    QStringList l = addr.split(":");
    host.setAddress(l[0]);
    port = l[1].toInt();
    qDebug() << "Binding:" << host << port;

    if(socket->bind(host,port)){
        Status = CONNECTED;
        return 0;
    }else{
        Status = DISCONNECTED;
        return -1;
    }
}

int RemoteUDP::Disconnect(){
    Status = DISCONNECTED;
    socket->close();
    host.clear();
    return 0;
}

int RemoteUDP::Send(QByteArray data){
    if(!host.isNull()){
        return socket->writeDatagram(data, host, port);
    }
    return -1;
}

void RemoteUDP::readyRead(){

    //qDebug() << "Read";

    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(Buffer.data(), (qint64) Buffer.size(), &host, &port);

    emit this->received(Buffer);
}
