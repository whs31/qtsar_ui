#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QVector>

#include "uisar.h"
#include "ui_uisar.h"

#define JPEG_HEADER_SIZE 20
class uiSAR;

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QObject *parent = nullptr);
    struct image_metadata {
        double latitude;
        double longitude;
        float dx;
        float dy;
        float x0;
        float y0;
        float angle;
        QString filename;
    };
    int fileCounter = 0;
    int getFileCounter();
    int getVectorSize();
    image_metadata getMetaList();
    bool getReadyStatus();

    void processPath(QString path);
    image_metadata decode_metadata(QStringList fileList);
    void showAllImages();
    void updateLabels(int structureIndex);
    void goLeft();
    void goRight();

signals:

private:
    //image_metadata *meta_array;
    QStringList imageList;
    QVector<image_metadata> metadataList;
    uiSAR *mainWindow;
};

#endif // IMAGEPROCESSING_H
