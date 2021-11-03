#include "qmlinvoker.h"
#include "qmlmarkerdialog.h"
#include "uisar.h"
#include <QDebug>


qmlInvoker::qmlInvoker(QObject *parent) : QObject(parent)
{
    uiSAR * win = uiSAR::getMainWinPtr();
    connect(this, SIGNAL(sendToMainWindow(float, float)), win, SLOT(qmlDialogSlot(float, float)));
}

void qmlInvoker::qmlDialogMarker(float markerLat, float markerLon)
{
    emit sendToMainWindow(markerLat, markerLon);
    //qDebug()<<"invoker connected!";
    //qmlMarkerDialog d;
    /*int result = d.exec();
    if(result == QDialog::Accepted)
    {
        QString dialogOutput = ui->markerNameEditor->text();
        emit sendToMainWindow(markerLat, markerLon, dialogOutput);
    }*/
}
