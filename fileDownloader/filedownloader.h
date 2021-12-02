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
    float progress();

private:
    Remote *Imgd;
    Config *cfg;
    int size = 0;
    qint32 fileSize = 0;
    QString prefix;
    QFile file;
    QStringList queue;

public slots:
    void received(QByteArray data);



};

#endif // FILEDOWNLOADER_H
