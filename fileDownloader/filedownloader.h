#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
#include "config/config.h"
#include "remote/remoteBase.h"
#include <QObject>
#include <QFile>


class fileDownloader : public QObject
{
    Q_OBJECT
public:
    fileDownloader(Config *_cfg);
    void setName(QString name);
    void setPrefix(QString _prefix);
    void abort();
    void download(QString path);

    Remote *Imgd;
    Config *cfg;
    int size = 0;
    int fileSize = 0;
    QString fn = "tmp";
    QString prefix = "./";
    QFile file;

public slots:
    void received(QByteArray data);



};

#endif // FILEDOWNLOADER_H
