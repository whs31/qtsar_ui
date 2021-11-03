#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>


class Remote : public QObject
{
    Q_OBJECT
public:

    Remote(){};
    virtual int Connect(QString addr) {return -1;};
    virtual int Disconnect() {return  -1;};
    virtual int Send(QByteArray data) {return -1;};

signals:
    void received(QByteArray data);
    void disconnected();
};

#endif // REMOTE_H
