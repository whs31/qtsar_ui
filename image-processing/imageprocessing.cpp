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
     * 4. Кнопка показа изображения должна быть связанна с деревом
     * 5. При чеке\анчеке директории в дереве должны чекаться\анчекаться все изображения в этой директории
     */
    model = new CheckableModel;
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
        //mainWindow->ui->jpg_gleft->setEnabled(true);  //так как по дефолту filecounter уже в крайнем левом положении на старте
        mainWindow->ui->transformJPGbox->setEnabled(1);
        mainWindow->ui->groupBox->setEnabled(1);

        decode_metadata(imageList);
        updateLabels(0);
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
    for (image_metadata meta : metadataList)
    {
        if(meta.latitude!=0)
        {
            QQuickItem*  qml = mainWindow->ui->osmMap->rootObject();
            QMetaObject::invokeMethod(qml, "addImage",
                    Q_ARG(QVariant, (float)meta.latitude),
                    Q_ARG(QVariant, (float)meta.longitude),
                    Q_ARG(QVariant, meta.dx),
                    Q_ARG(QVariant, meta.dy),
                    Q_ARG(QVariant, meta.x0),
                    Q_ARG(QVariant, meta.y0),
                    Q_ARG(QVariant, meta.angle),
                    Q_ARG(QVariant, meta.filename)
                    );
        }
    }
    mainWindow->statusBar()->showMessage(tr("Изображения отображены на карте"), 15000);
}

void ImageProcessing::updateLabels(int structureIndex)
{
    //bold+size for all future 7px bold labels
    QFont labelFont = mainWindow->ui->jpgtls_latdisp->font();
    labelFont.setPointSize(7);
    labelFont.setBold(true);
    //just use ui->labelname->setFont(labelFont);
    mainWindow->ui->jpgtls_latdisp->setText(QString::number(metadataList[structureIndex].latitude));
    mainWindow->ui->jpgtls_latdisp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_latdisp->setFont(labelFont);
    mainWindow->ui->jpgtls_londisp->setText(QString::number(metadataList[structureIndex].longitude));
    mainWindow->ui->jpgtls_londisp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_londisp->setFont(labelFont);
    mainWindow->ui->jpgtls_dxdisp->setText(QString::number(metadataList[structureIndex].dx));
    mainWindow->ui->jpgtls_dxdisp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_dxdisp->setFont(labelFont);
    mainWindow->ui->jpgtls_dydisp->setText(QString::number(metadataList[structureIndex].dy));
    mainWindow->ui->jpgtls_dydisp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_dydisp->setFont(labelFont);
    mainWindow->ui->jpgtls_x0disp->setText(QString::number(metadataList[structureIndex].x0));
    mainWindow->ui->jpgtls_x0disp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_x0disp->setFont(labelFont);
    mainWindow->ui->jpgtls_y0disp->setText(QString::number(metadataList[structureIndex].y0));
    mainWindow->ui->jpgtls_y0disp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_y0disp->setFont(labelFont);
    mainWindow->ui->jpgtls_angdisp->setText(QString::number(metadataList[structureIndex].angle));
    mainWindow->ui->jpgtls_angdisp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_angdisp->setFont(labelFont);
    mainWindow->ui->jpgtls_filenamedisp->setText(metadataList[structureIndex].filename);
    mainWindow->ui->jpgtls_filenamedisp->setAlignment(Qt::AlignRight);
    mainWindow->ui->jpgtls_filenamedisp->setFont(labelFont);
}

int ImageProcessing::getFileCounter()
{
    return fileCounter;
}

int ImageProcessing::getVectorSize()
{
    return imageList.length();
}

ImageProcessing::image_metadata ImageProcessing::getMetaList()
{
    return metadataList[fileCounter];
}

bool ImageProcessing::getReadyStatus()
{
    if(!imageList.empty())
    {
        return 1;
    } else {
        return 0;
    }
}

void ImageProcessing::goLeft()
{
    int totalFiles = imageList.size()-1;

    if(fileCounter>0)
    {
        fileCounter--;
        updateLabels(fileCounter);
    }
    if (fileCounter == 0) {
        mainWindow->ui->jpg_gleft->setEnabled(false);
    }
    if(fileCounter < totalFiles)
    {
        mainWindow->ui->jpg_gright->setEnabled(true);
    }

    //qDebug()<<fileCounter<<totalFiles;
}

void ImageProcessing::goRight()
{
    int totalFiles = imageList.size()-1;
    if(fileCounter < totalFiles)
    {
        fileCounter++;
        updateLabels(fileCounter);
    }
    if(fileCounter > 0)
    {
        mainWindow->ui->jpg_gleft->setEnabled(true);
    }
    if (fileCounter == totalFiles) {
        mainWindow->ui->jpg_gright->setEnabled(false);
    }
    //qDebug()<<fileCounter<<totalFiles;
}

