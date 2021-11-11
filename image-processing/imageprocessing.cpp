#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject(parent)
{
    mainWindow = uiSAR::getMainWinPtr();
}

ImageProcessing::image_metadata ImageProcessing::decode_metadata(QString path)
{

}

void ImageProcessing::showAllImages()
{

}

void ImageProcessing::updateLabels(image_metadata _meta)
{

}

