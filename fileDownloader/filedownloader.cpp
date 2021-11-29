#include "filedownloader.h"

fileDownloader::fileDownloader(Config* _cfg) : cfg(_cfg)
{
    QString connectStatus;
    state = IDLE;

    /* Интерфейс для получения РЛИ */
    Imgd = RemoteAuto(cfg->value("imgd/type").toString());
    QString imgdIP = cfg->value("imgd/address").toString();
    QString imgdPort = cfg->value("imgd/port").toString();
    QString imgdAddr = imgdIP + ":" + imgdPort;

    connectStatus = "Connect to imgd ";
    if(Imgd->Connect(imgdAddr) != -1){
        connectStatus.append("OK");
    }else{
        connectStatus.append("Error");
    }
    qDebug() << connectStatus;

    QObject::connect( Imgd , SIGNAL(received(QByteArray)), this, SLOT(received(QByteArray)));
    file.setFileName(prefix+fn);

}


void fileDownloader::received(QByteArray data){

    if(fileSize < 1){

        state = BUSY;
        const char *d = data.data();
        fileSize = (d[3] << 24) | (d[2] << 16) | (d[1] << 8) | d[0];

        qDebug() << "filesize" << fileSize;

        if(fileSize == -1){
            qDebug() << "Have no file to download!";
            return;
        }


        if( file.open(QIODevice::WriteOnly) ){
            qDebug()  << "File" << fn << "opened";
        }

        if(data.length() > 4){
            received( QByteArray( data.data() + 4 ) );
        }

    }else{
        if(file.isOpen()){
            size += file.write(data);
        }

        if(size >= fileSize){
            fileSize = 0;
            size = 0;
            qDebug() << "Downloading done!";
            file.close();
            state = IDLE;
            if(!queue.isEmpty()){
                download(queue[0]);
                queue.pop_front();
            }

        }

    }

}

void fileDownloader::abort(){

    QString connectStatus;
    Imgd->Disconnect();

    fileSize = 0;
    size = 0;
    state = IDLE;


    QString imgdIP = cfg->value("imgd/address").toString();
    QString imgdPort = cfg->value("imgd/port").toString();
    QString imgdAddr = imgdIP + ":" + imgdPort;

    connectStatus = "Reconnect to imgd ";
    if(Imgd->Connect(imgdAddr) != -1){
        connectStatus.append("OK");
    }else{
        connectStatus.append("Error");
    }
    qDebug() << connectStatus;

    if(file.isOpen()){
        file.close();
    }


}


void fileDownloader::setName(QString name){
    fn = name;
    file.setFileName(prefix+fn);
}


void fileDownloader::setPrefix(QString _prefix){
    prefix = _prefix;
    qDebug() << "Download directory is: " << prefix;
}

void fileDownloader::download(QString path){

    if(state == IDLE){
        state = BUSY;
        QFileInfo fi(path);
        fn = fi.fileName();
        Imgd->Send(path.toUtf8());
    }else if(state == BUSY){
        // add to queue
        qDebug() << "add to queue" << path;
        queue.append(path);
    }
}
