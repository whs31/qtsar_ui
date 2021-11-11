#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>

#include "uisar.h"
#include "ui_uisar.h"
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

    image_metadata decode_metadata(QString path);
    void showAllImages();
    void updateLabels(image_metadata _meta);

signals:

private:
    uiSAR *mainWindow;
};

#endif // IMAGEPROCESSING_H
