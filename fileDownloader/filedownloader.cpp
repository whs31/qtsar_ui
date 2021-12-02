#include "filedownloader.h"

fileDownloader::fileDownloader(Config* _cfg) : cfg(_cfg)
{
    QString connectStatus;
    state = IDLE;

    setPrefix(cfg->value("imgd/downloadPath").toString());

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

}


void fileDownloader::received(QByteArray data){

    if(fileSize < 1){
        // Тут принимается размер файла
        state = BUSY;
        const quint8 *d = (const quint8*)data.data();
        fileSize = (d[3] << 24) | (d[2] << 16) | (d[1] << 8) | d[0];

        qDebug() << "filesize" << fileSize << QString::number(fileSize, 16);

        if(fileSize == -1){
            qDebug() << "Have no file to download!";
            return;
        }


        if( file.open(QIODevice::WriteOnly) ){
            qDebug()  << "File" << currentFile() << "opened";
        }

        if(data.length() > 4){
            received( QByteArray( data.data() + 4 ) );
        }

    }else{
        // Тут принимиается сам файл
        if(file.isOpen()){
            size += file.write(data);
        }

        if(size >= fileSize){
            fileSize = 0;
            size = 0;
            qDebug() << "Downloading done!";
            file.close();
            state = IDLE;
            // Отправка запроса на передачу следующего в очереди файла
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

void fileDownloader::abortAll(){
    queue.clear();
    abort();
}


bool fileDownloader::flush(){
    return file.flush();
}

QString fileDownloader::currentFile(){
    QFileInfo fi(file);
    return fi.absoluteFilePath();
}

void fileDownloader::setName(QString name){
    file.setFileName(prefix+name);
}


float fileDownloader::progress(){
    return (float)size/fileSize;
}

void fileDownloader::setPrefix(QString _prefix){
    prefix = _prefix;
    if(prefix[prefix.length()-1] != QChar('/')){
        prefix.append('/');
    }


    QDir dir;
    if( !dir.mkpath(prefix) ){
        qDebug() << "WARNING: Can not create" << prefix;
        prefix = "./";
    }
    qDebug() << "Download directory is: " << prefix;
}

void fileDownloader::download(QString path){

    if(state == IDLE){
        state = BUSY;
        QFileInfo fi(path);
        setName(fi.fileName());
        Imgd->Send(path.toUtf8());
    }else if(state == BUSY){
        // add to queue
        qDebug() << "add to queue" << path;
        queue.append(path);
    }
}
