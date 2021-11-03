#include "qmlmarkerdialog.h"
#include "ui_qmlmarkerdialog.h"
#include <QColorDialog>
#include <QColor>

qmlMarkerDialog::qmlMarkerDialog(QWidget *parent) :
    QDialog(parent),
    dui(new Ui::qmlMarkerDialog)
{
    dui->setupUi(this);
    qInfo()<<"Dialog box init success";
    _color = "white";
}

qmlMarkerDialog::~qmlMarkerDialog()
{
    delete dui;
}

QString qmlMarkerDialog::lineEdit1Text() const
{
    return dui->markerNameEditor->text();
}

QColor qmlMarkerDialog::color() const
{
    return _color;
}

void qmlMarkerDialog::on_pushButton_clicked()
{
    _color = QColorDialog::getColor();
}
