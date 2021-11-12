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

    QDir childDirectory(path);
    childDirectory.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    childDirectory.setNameFilters(QStringList("*.jpg"));

    QStringList fileList = childDirectory.entryList();

    if(!fileList.empty()){
        imageList.clear();
        for ( QString f : fileList  ){
            imageList.append(f.prepend(path+"/"));
        }

        mainWindow->ui->jpg_gright->setEnabled(true);
        mainWindow->ui->jpg_gleft->setEnabled(true);

        decode_metadata(imageList);
        mainWindow->ui->transformJPGbox->setEnabled(1);
        mainWindow->ui->groupBox->setEnabled(1);

        showAllImages();
    }else{
        mainWindow->statusBar()->showMessage(tr("Каталог с изображениями не распознан, повторите ввод через панель инструментов"), 15000);
        QMessageBox warningDialogue;
        warningDialogue.setWindowTitle("Неверный каталог!");
        warningDialogue.setIcon(QMessageBox::Warning);
        warningDialogue.setText("Изображения не найдены!");
        warningDialogue.exec();
    }
}

ImageProcessing::image_metadata ImageProcessing::decode_metadata(QStringList fileList)
{

}

void ImageProcessing::showAllImages()
{

}

void ImageProcessing::updateLabels(image_metadata _meta)
{

}

