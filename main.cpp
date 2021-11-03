#include "uisar.h"
#include <QApplication>
#include <QtGlobal>
#include <qqml.h>
#include <stdio.h>
#include <stdlib.h>
#include "qmlinvoker.h"

/*
CSS colors:

buttons background                      4d4d4d
buttons background disabled             424242
buttons checked                         3380cc
buttons checked disabled                295b8c
buttons hover                           5c5c5c

*/
void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg+"\r\n");
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg+"\r\n");
    break;
    case QtInfoMsg:
        txt = QString("Info: %1").arg(msg+"\r\n");
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg+"\r\n");
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg+"\r\n");
    break;
    }
    QFile outFile(QCoreApplication::applicationDirPath()+"/qtlog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
     //qInstallMessageHandler(myMessageHandler); // Install the handler


    QFile LstyleSheetFile(":qdarkstyle/light/style.qss");
    QFile DstyleSheetFile(":qdarkstyle/dark/style.qss");
    if (!DstyleSheetFile.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        DstyleSheetFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&DstyleSheetFile);
    //QString styleSheet = QLatin1String(styleSheetFile.readAll());
        qApp->setStyleSheet(ts.readAll());
    }
    qmlRegisterType<qmlInvoker>("cpp.invoker", 1, 0, "Invoker");
    uiSAR w;

    //w.setWindowState(Qt::WindowMaximized);
    w.show();
    return app.exec();
}
