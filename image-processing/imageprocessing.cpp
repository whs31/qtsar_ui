#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject(parent)
{
    mainWindow = uiSAR::getMainWinPtr();

    /*image_metadata img = {1,2,3,4,5,6,7,"filenameq"};
    image_metadata img2 = {1,32,32,43,54,56,7,"qwe"};
    metadataList.append(img);
    metadataList.prepend(img2);
    qDebug()<<metadataList[0].filename;
    qDebug()<<metadataList[1].filename;

    пример работы с вектором структур*/
}

void ImageProcessing::processPath(QString path)
{
    QStringList childDirectoryList;

    QDir parentDirectory(path);
    QDirIterator iterator(parentDirectory.path(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(iterator.hasNext()){
           iterator.next();
           childDirectoryList << iterator.filePath();
    }
    /*
     * 1. ☑ Нужно вместо qfilesystemmodel использовать класс, унаследованный от нее, с переопределенными методами data(), setData()
     * 2. Нужно реворкнуть кнопку <показать изображение>: она должна быть checkable, и менять свое состояние в зависимости от текущего выбранного изображения
     * 3. Изображения должны отображаться только однажды
     * 4. Кнопка показа изображения должна быть связанна с деревом
     * 5. При чеке\анчеке директории в дереве должны чекаться\анчекаться все изображения в этой директории
     */
    CheckableModel *model = new CheckableModel;
    model->setRootPath(parentDirectory.path());
    mainWindow->ui->treeView->setModel(model);
    mainWindow->ui->treeView->setRootIndex(model->index(parentDirectory.path()));

    QStringList fileList;
    if(!childDirectoryList.empty())
    {
        for (QString childDirectoryString : childDirectoryList)
        {
            QDir childDirectory(childDirectoryString);
            childDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
            childDirectory.setNameFilters(QStringList("*.jpg"));
            QStringList entry_list = childDirectory.entryList();
            for (QString entryString : entry_list)
            {
                fileList.append(entryString.prepend(childDirectoryString+"/"));
            }
            //fileList.append(childDirectory.entryList());
        }
       // qDebug()<<fileList;
        if(!fileList.empty())
        {
            qInfo()<<"Imagelist fulfilled";
            imageList.clear();
            metadataList.clear();
            //qml clear and remove images
            for ( QString f : fileList  ){
               // imageList.append(f.prepend(path+"/"));
                imageList.append(f);
            }
        } else {
            mainWindow->statusBar()->showMessage(tr("Каталог с изображениями не распознан, повторите ввод через панель настроек!"), 15000);
            QMessageBox warningDialogue;
            warningDialogue.setWindowTitle("Изображения не найдены!");
            warningDialogue.setIcon(QMessageBox::Warning);
            warningDialogue.setText("В выбранном каталоге не найдены изображения!");
            warningDialogue.exec();
        }
    } else {
        mainWindow->statusBar()->showMessage(tr("В выбранном каталоге неверная структура папок!"), 15000);
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Неверный каталог!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("Неверная структура каталога!");
        warningDialogue.exec();
    }
        mainWindow->ui->jpg_gright->setEnabled(true);
        mainWindow->ui->jpg_gleft->setEnabled(true);
        mainWindow->ui->transformJPGbox->setEnabled(1);
        mainWindow->ui->groupBox->setEnabled(1);

        decode_metadata(imageList);
        //showAllImages();
}

ImageProcessing::image_metadata ImageProcessing::decode_metadata(QStringList fileList)
{
    image_metadata metaStruct = {0,0,0,0,0,0,0,"err"};
    qDebug()<<"Called decoding function for list from "<< fileList[0];
    for (QString fileName : fileList)
    {
        QFile _qfile(fileName);
        if(_qfile.open(QIODevice::ReadOnly))
        {
            QByteArray rawData = _qfile.readAll();
            char *data = rawData.data();
            uint16_t *metaMarker = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE);

            if(*metaMarker == 0xE1FF)
            {
                uint16_t *metaSize = reinterpret_cast<uint16_t *>(data + JPEG_HEADER_SIZE + 2);
                *metaSize = qToBigEndian(*metaSize) - 2;
                memcpy(&metaStruct, (data+JPEG_HEADER_SIZE+4), *metaSize);
            }
            metaStruct.filename = fileName;
            qDebug()<<"Decoded file ("<<metaStruct.filename<<") successfully";
            metadataList.append(metaStruct);
        }
    }
    return {0,0,0,0,0,0,0,"successfull decoding!"};
}

void ImageProcessing::showAllImages()
{

}

void ImageProcessing::updateLabels(image_metadata _meta)
{

}

