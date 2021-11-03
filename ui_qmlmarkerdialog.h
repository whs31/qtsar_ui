/********************************************************************************
** Form generated from reading UI file 'qmlmarkerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMLMARKERDIALOG_H
#define UI_QMLMARKERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_qmlMarkerDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *markerNameEditor;

    void setupUi(QDialog *qmlMarkerDialog)
    {
        if (qmlMarkerDialog->objectName().isEmpty())
            qmlMarkerDialog->setObjectName(QString::fromUtf8("qmlMarkerDialog"));
        qmlMarkerDialog->setWindowModality(Qt::WindowModal);
        qmlMarkerDialog->resize(308, 110);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/add_marker.png"), QSize(), QIcon::Normal, QIcon::Off);
        qmlMarkerDialog->setWindowIcon(icon);
        qmlMarkerDialog->setModal(true);
        gridLayout = new QGridLayout(qmlMarkerDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(20, 14, 20, 22);
        pushButton = new QPushButton(qmlMarkerDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        pushButton->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/take_coords.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(qmlMarkerDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

        label = new QLabel(qmlMarkerDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        markerNameEditor = new QLineEdit(qmlMarkerDialog);
        markerNameEditor->setObjectName(QString::fromUtf8("markerNameEditor"));
        markerNameEditor->setMaxLength(26);
        markerNameEditor->setClearButtonEnabled(true);

        gridLayout->addWidget(markerNameEditor, 1, 1, 1, 1);


        retranslateUi(qmlMarkerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), qmlMarkerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), qmlMarkerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(qmlMarkerDialog);
    } // setupUi

    void retranslateUi(QDialog *qmlMarkerDialog)
    {
        qmlMarkerDialog->setWindowTitle(QCoreApplication::translate("qmlMarkerDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\274\320\260\321\200\320\272\320\265\321\200", nullptr));
        pushButton->setText(QString());
        label->setText(QCoreApplication::translate("qmlMarkerDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\270 \321\206\320\262\320\265\321\202 \320\274\320\260\321\200\320\272\320\265\321\200\320\260:", nullptr));
        markerNameEditor->setText(QCoreApplication::translate("qmlMarkerDialog", "\320\235\320\276\320\262\321\213\320\271 \320\274\320\260\321\200\320\272\320\265\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qmlMarkerDialog: public Ui_qmlMarkerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMLMARKERDIALOG_H
