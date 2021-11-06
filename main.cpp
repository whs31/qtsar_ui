#include "uisar.h"
#include <QApplication>
#include <QtGlobal>
#include <qqml.h>
#include <stdio.h>
#include <stdlib.h>
#include "qmlinvoker.h"

/*
CSS colors:

purple 			#BB86FC  #B2A4D4
blue 			#3700B3  #521AD5
green			#03DAC6  #93E5DD
red				#CF6679

back			#121212
darker back		#000000
text			#FFFFFF
dark text 		#AAAAAA

gray gradient:
01dp     		#1e1e1e
02dp      		#222222
03dp    		#242424
04dp     		#272727
06dp    		#2c2c2c
08dp    		#2e2e2e //border groupbox
12dp   			#333333
16dp    		#343434
24dp   			#383838

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
    QFile outFile(QCoreApplication::applicationDirPath()+"/debug_log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //раскомментировать для лога отладки в файл
    //qInstallMessageHandler(myMessageHandler); // Install the handler

    QFile LstyleSheetFile(":qdarkstyle/light/style.qss");
    QFile DstyleSheetFile(":qdarkstyle/dark/style.qss");
    if (!DstyleSheetFile.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        DstyleSheetFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&DstyleSheetFile);
        qApp->setStyleSheet(ts.readAll());
    }
    qmlRegisterType<qmlInvoker>("cpp.invoker", 1, 0, "Invoker");

    uiSAR w;
    w.show();
    return app.exec();
}
