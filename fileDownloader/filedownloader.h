#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
#include "config/config.h"
#include "remote/remoteBase.h"
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>


class fileDownloader : public QObject
{
    Q_OBJECT
public:

    enum State{IDLE, BUSY} state;

    fileDownloader(Config *_cfg);
    void setName(QString name);
    void setPrefix(QString _prefix);
    void abort();
    void abortAll();
    bool flush();
    void download(QString path);
    QString currentFile();

private:
    Remote *Imgd;
    Config *cfg;
    int size = 0;
    int fileSize = 0;
    QString fn = "tmp";
    QString prefix;
    QFile file;
    QStringList queue;

public slots:
    void received(QByteArray data);



};

#endif // FILEDOWNLOADER_H
