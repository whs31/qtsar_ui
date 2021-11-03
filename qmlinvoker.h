#ifndef QMLINVOKER_H
#define QMLINVOKER_H

#include <QObject>

class qmlInvoker : public QObject
{
    Q_OBJECT
public:
    explicit qmlInvoker(QObject *parent = nullptr);

    Q_INVOKABLE void qmlDialogMarker(float markerLat, float markerLon);

signals:
    void sendToMainWindow(float markerLat, float markerLon);

};

#endif // QMLINVOKER_H
