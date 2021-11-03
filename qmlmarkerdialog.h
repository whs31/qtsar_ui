#ifndef QMLMARKERDIALOG_H
#define QMLMARKERDIALOG_H

#include <QObject>
#include <QDebug>
#include <QInputDialog>
#include <QString>

namespace Ui {
class qmlMarkerDialog;
}

class qmlMarkerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit qmlMarkerDialog(QWidget *parent = 0);
    ~qmlMarkerDialog();
    QString lineEdit1Text() const;
    QColor color() const;

private slots:
    void on_pushButton_clicked();

private:
    QColor _color;
    Ui::qmlMarkerDialog *dui;
};

#endif // QMLMARKERDIALOG_H
