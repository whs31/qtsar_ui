/********************************************************************************
** Form generated from reading UI file 'uisar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UISAR_H
#define UI_UISAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "console/console.h"

QT_BEGIN_NAMESPACE

class Ui_uiSAR
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QQuickWidget *osmMap;
    QTabWidget *tabWidget;
    QWidget *map_tab;
    QGridLayout *gridLayout_5;
    QFrame *line;
    QGroupBox *NAVSAR;
    QFormLayout *formLayout;
    QLabel *nav_latlabel;
    QLabel *nav_latdisp;
    QLabel *nav_lonlabel;
    QLabel *nav_londisp;
    QLabel *nav_acclabel;
    QLabel *nav_accdisp;
    QLabel *nav_altlabel;
    QLabel *nav_altdisp;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_5;
    QHBoxLayout *markerLayout;
    QLabel *label;
    QPushButton *placeMarkerButton;
    QPushButton *saveMarkerButton;
    QPushButton *loadMarkerButton;
    QGridLayout *gridLayout_2;
    QCheckBox *nav_follow;
    QCheckBox *nav_displaytriangle;
    QCheckBox *planeCheckbox;
    QCheckBox *showCoordsBox;
    QCheckBox *nav_displayroute;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_9;
    QPushButton *panGPS;
    QPushButton *clearTrack;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QWidget *tcp_tab;
    QGridLayout *gridLayout_11;
    QFrame *line_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_13;
    Console *consoleMain;
    QLabel *label_12;
    QSpacerItem *verticalSpacer_10;
    QWidget *img_tab;
    QGridLayout *gridLayout_7;
    QFrame *line_3;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *jpgtls_latlabel;
    QLabel *jpgtls_latdisp;
    QLabel *jpgtls_lonlabel;
    QLabel *jpgtls_londisp;
    QLabel *jpgtls_dxlabel;
    QLabel *jpgtls_dxdisp;
    QLabel *jpgtls_dylabel;
    QLabel *jpgtls_dydisp;
    QLabel *jpgtls_x0label;
    QLabel *jpgtls_x0disp;
    QLabel *jpgtls_y0label;
    QLabel *jpgtls_y0disp;
    QLabel *jpgtls_anglabel;
    QLabel *jpgtls_angdisp;
    QGridLayout *jpgButtonsLayout;
    QPushButton *showButton;
    QPushButton *panButton;
    QHBoxLayout *opacityLayout;
    QLabel *opacityLabel;
    QSlider *opacitySlider;
    QHBoxLayout *horizontalLayout;
    QToolButton *jpg_gleft;
    QLabel *jpgtls_filenamelabel;
    QLabel *jpgtls_filenamedisp;
    QToolButton *jpg_gright;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_7;
    QGroupBox *transformJPGbox;
    QGridLayout *gridLayout_9;
    QDial *t_rotation;
    QDoubleSpinBox *t_ySpin;
    QLabel *label_10;
    QDoubleSpinBox *t_rSpin;
    QGridLayout *gridLayout_10;
    QPushButton *t_right;
    QPushButton *t_left;
    QPushButton *t_up;
    QPushButton *t_down;
    QDoubleSpinBox *t_xSpin;
    QLabel *label_8;
    QDoubleSpinBox *t_sSpin;
    QScrollBar *t_scale;
    QLabel *label_9;
    QLabel *label_11;
    QWidget *cfg_tab;
    QGridLayout *gridLayout_6;
    QLabel *label_14;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_11;
    QLabel *label_20;
    QLineEdit *TCPIPxml;
    QLabel *label_3;
    QDoubleSpinBox *refreshtelemetryxml;
    QGridLayout *gridLayout_12;
    QLabel *label_18;
    QLabel *label_15;
    QLabel *label_16;
    QDoubleSpinBox *diaThetaAzimuth;
    QLabel *label_17;
    QDoubleSpinBox *diaDriftAngle;
    QDoubleSpinBox *diaTimexml;
    QDoubleSpinBox *diaRangexml;
    QLabel *label_19;
    QRadioButton *providerGoogle;
    QRadioButton *providerESRI;
    QRadioButton *providerOSM;
    QDoubleSpinBox *predictRangexml;
    QLabel *label_13;
    QLineEdit *TCPPortxml;
    QPushButton *selectFolderButton;
    QLineEdit *UDPIPxml;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_5;
    QLineEdit *UDPPortxml;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *saveSettings;
    QPushButton *discardSettings;
    QWidget *link_tab;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *UDPConsole;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *udpStopButton;
    QGridLayout *gridLayout_3;
    QTextEdit *udpIn;
    QPushButton *udpSendButton;
    QTextEdit *udpDisp;
    QWidget *info_tab;
    QGridLayout *gridLayout_8;
    QPushButton *DecodeJPG;
    QLabel *infoLabel;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusBar;
    QDockWidget *docker;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *gpsPanClone;
    QPushButton *rulerButton;
    QPushButton *changeMapMode;

    void setupUi(QMainWindow *uiSAR)
    {
        if (uiSAR->objectName().isEmpty())
            uiSAR->setObjectName(QString::fromUtf8("uiSAR"));
        uiSAR->setWindowModality(Qt::ApplicationModal);
        uiSAR->resize(1301, 729);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uiSAR->sizePolicy().hasHeightForWidth());
        uiSAR->setSizePolicy(sizePolicy);
        uiSAR->setMinimumSize(QSize(1300, 650));
        uiSAR->setMaximumSize(QSize(16777215, 16777215));
        uiSAR->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/ui.png"), QSize(), QIcon::Normal, QIcon::Off);
        uiSAR->setWindowIcon(icon);
        uiSAR->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        uiSAR->setDocumentMode(false);
        uiSAR->setTabShape(QTabWidget::Rounded);
        uiSAR->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(uiSAR);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMaximumSize(QSize(4096, 2048));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        osmMap = new QQuickWidget(centralwidget);
        osmMap->setObjectName(QString::fromUtf8("osmMap"));
        osmMap->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(osmMap->sizePolicy().hasHeightForWidth());
        osmMap->setSizePolicy(sizePolicy2);
        osmMap->setMaximumSize(QSize(4096, 2048));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        osmMap->setFont(font);
        osmMap->setCursor(QCursor(Qt::CrossCursor));
        osmMap->setMouseTracking(true);
        osmMap->setResizeMode(QQuickWidget::SizeRootObjectToView);
        osmMap->setSource(QUrl(QString::fromUtf8("qrc:/map.qml")));

        gridLayout->addWidget(osmMap, 0, 2, 10, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setMinimumSize(QSize(400, 0));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(48, 48));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tabWidget->setDocumentMode(true);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(true);
        map_tab = new QWidget();
        map_tab->setObjectName(QString::fromUtf8("map_tab"));
        gridLayout_5 = new QGridLayout(map_tab);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        line = new QFrame(map_tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 1, 0, 1, 3);

        NAVSAR = new QGroupBox(map_tab);
        NAVSAR->setObjectName(QString::fromUtf8("NAVSAR"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(NAVSAR->sizePolicy().hasHeightForWidth());
        NAVSAR->setSizePolicy(sizePolicy4);
        NAVSAR->setFlat(false);
        formLayout = new QFormLayout(NAVSAR);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nav_latlabel = new QLabel(NAVSAR);
        nav_latlabel->setObjectName(QString::fromUtf8("nav_latlabel"));
        nav_latlabel->setFrameShape(QFrame::NoFrame);

        formLayout->setWidget(0, QFormLayout::LabelRole, nav_latlabel);

        nav_latdisp = new QLabel(NAVSAR);
        nav_latdisp->setObjectName(QString::fromUtf8("nav_latdisp"));
        nav_latdisp->setScaledContents(false);
        nav_latdisp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nav_latdisp->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        formLayout->setWidget(0, QFormLayout::FieldRole, nav_latdisp);

        nav_lonlabel = new QLabel(NAVSAR);
        nav_lonlabel->setObjectName(QString::fromUtf8("nav_lonlabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, nav_lonlabel);

        nav_londisp = new QLabel(NAVSAR);
        nav_londisp->setObjectName(QString::fromUtf8("nav_londisp"));
        nav_londisp->setScaledContents(false);
        nav_londisp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nav_londisp->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        formLayout->setWidget(1, QFormLayout::FieldRole, nav_londisp);

        nav_acclabel = new QLabel(NAVSAR);
        nav_acclabel->setObjectName(QString::fromUtf8("nav_acclabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, nav_acclabel);

        nav_accdisp = new QLabel(NAVSAR);
        nav_accdisp->setObjectName(QString::fromUtf8("nav_accdisp"));
        nav_accdisp->setScaledContents(false);
        nav_accdisp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nav_accdisp->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        formLayout->setWidget(2, QFormLayout::FieldRole, nav_accdisp);

        nav_altlabel = new QLabel(NAVSAR);
        nav_altlabel->setObjectName(QString::fromUtf8("nav_altlabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, nav_altlabel);

        nav_altdisp = new QLabel(NAVSAR);
        nav_altdisp->setObjectName(QString::fromUtf8("nav_altdisp"));
        nav_altdisp->setScaledContents(false);
        nav_altdisp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nav_altdisp->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        formLayout->setWidget(3, QFormLayout::FieldRole, nav_altdisp);


        gridLayout_5->addWidget(NAVSAR, 4, 0, 1, 3);

        verticalSpacer_6 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_5->addItem(verticalSpacer_6, 2, 0, 1, 1);

        label_5 = new QLabel(map_tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFrameShape(QFrame::NoFrame);
        label_5->setFrameShadow(QFrame::Plain);
        label_5->setLineWidth(0);
        label_5->setMidLineWidth(0);
        label_5->setTextFormat(Qt::AutoText);

        gridLayout_5->addWidget(label_5, 0, 0, 1, 3);

        markerLayout = new QHBoxLayout();
        markerLayout->setSpacing(5);
        markerLayout->setObjectName(QString::fromUtf8("markerLayout"));
        markerLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(map_tab);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy5);

        markerLayout->addWidget(label);

        placeMarkerButton = new QPushButton(map_tab);
        placeMarkerButton->setObjectName(QString::fromUtf8("placeMarkerButton"));
        sizePolicy4.setHeightForWidth(placeMarkerButton->sizePolicy().hasHeightForWidth());
        placeMarkerButton->setSizePolicy(sizePolicy4);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/add_marker.png"), QSize(), QIcon::Normal, QIcon::Off);
        placeMarkerButton->setIcon(icon1);
        placeMarkerButton->setCheckable(false);

        markerLayout->addWidget(placeMarkerButton);

        saveMarkerButton = new QPushButton(map_tab);
        saveMarkerButton->setObjectName(QString::fromUtf8("saveMarkerButton"));
        saveMarkerButton->setEnabled(false);
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(saveMarkerButton->sizePolicy().hasHeightForWidth());
        saveMarkerButton->setSizePolicy(sizePolicy6);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveMarkerButton->setIcon(icon2);

        markerLayout->addWidget(saveMarkerButton);

        loadMarkerButton = new QPushButton(map_tab);
        loadMarkerButton->setObjectName(QString::fromUtf8("loadMarkerButton"));
        loadMarkerButton->setEnabled(false);
        sizePolicy6.setHeightForWidth(loadMarkerButton->sizePolicy().hasHeightForWidth());
        loadMarkerButton->setSizePolicy(sizePolicy6);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadMarkerButton->setIcon(icon3);

        markerLayout->addWidget(loadMarkerButton);


        gridLayout_5->addLayout(markerLayout, 7, 0, 1, 3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(4);
        nav_follow = new QCheckBox(map_tab);
        nav_follow->setObjectName(QString::fromUtf8("nav_follow"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/follow.png"), QSize(), QIcon::Normal, QIcon::Off);
        nav_follow->setIcon(icon4);

        gridLayout_2->addWidget(nav_follow, 0, 1, 1, 1);

        nav_displaytriangle = new QCheckBox(map_tab);
        nav_displaytriangle->setObjectName(QString::fromUtf8("nav_displaytriangle"));
        nav_displaytriangle->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/radar.png"), QSize(), QIcon::Normal, QIcon::Off);
        nav_displaytriangle->setIcon(icon5);
        nav_displaytriangle->setChecked(true);

        gridLayout_2->addWidget(nav_displaytriangle, 4, 1, 1, 1);

        planeCheckbox = new QCheckBox(map_tab);
        planeCheckbox->setObjectName(QString::fromUtf8("planeCheckbox"));
        planeCheckbox->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/planeSmall.png"), QSize(), QIcon::Normal, QIcon::Off);
        planeCheckbox->setIcon(icon6);
        planeCheckbox->setChecked(true);

        gridLayout_2->addWidget(planeCheckbox, 5, 1, 1, 1);

        showCoordsBox = new QCheckBox(map_tab);
        showCoordsBox->setObjectName(QString::fromUtf8("showCoordsBox"));
        sizePolicy.setHeightForWidth(showCoordsBox->sizePolicy().hasHeightForWidth());
        showCoordsBox->setSizePolicy(sizePolicy);
        showCoordsBox->setMaximumSize(QSize(16777215, 25));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/take_coords.png"), QSize(), QIcon::Normal, QIcon::Off);
        showCoordsBox->setIcon(icon7);
        showCoordsBox->setChecked(true);

        gridLayout_2->addWidget(showCoordsBox, 6, 1, 1, 1);

        nav_displayroute = new QCheckBox(map_tab);
        nav_displayroute->setObjectName(QString::fromUtf8("nav_displayroute"));
        nav_displayroute->setEnabled(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/img/route.png"), QSize(), QIcon::Normal, QIcon::Off);
        nav_displayroute->setIcon(icon8);
        nav_displayroute->setChecked(true);

        gridLayout_2->addWidget(nav_displayroute, 1, 1, 1, 1);

        checkBox = new QCheckBox(map_tab);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/img/path.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBox->setIcon(icon9);

        gridLayout_2->addWidget(checkBox, 3, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 5, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 9, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_9 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_9);

        panGPS = new QPushButton(map_tab);
        panGPS->setObjectName(QString::fromUtf8("panGPS"));
        sizePolicy4.setHeightForWidth(panGPS->sizePolicy().hasHeightForWidth());
        panGPS->setSizePolicy(sizePolicy4);
        panGPS->setMinimumSize(QSize(0, 0));
        panGPS->setMaximumSize(QSize(999999, 27));
        panGPS->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/img/nav_pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        panGPS->setIcon(icon10);
        panGPS->setIconSize(QSize(21, 21));

        verticalLayout->addWidget(panGPS);

        clearTrack = new QPushButton(map_tab);
        clearTrack->setObjectName(QString::fromUtf8("clearTrack"));
        clearTrack->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: #b46363;\n"
"  color: #E0E1E3;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"  border: none;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"  background-color: rgb(131, 79, 79);\n"
"  color: #9DA9B5;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgb(255, 213, 213);\n"
"  color: #E0E1E3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"  background-color: rgb(223, 223, 223);\n"
"}\n"
""));

        verticalLayout->addWidget(clearTrack);

        verticalSpacer_2 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout_5->addLayout(verticalLayout, 5, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        gridLayout_5->addLayout(horizontalLayout_3, 8, 1, 1, 1);

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/tabIcons/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(map_tab, icon11, QString());
        tcp_tab = new QWidget();
        tcp_tab->setObjectName(QString::fromUtf8("tcp_tab"));
        gridLayout_11 = new QGridLayout(tcp_tab);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        line_4 = new QFrame(tcp_tab);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_4, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(tcp_tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFlat(false);
        gridLayout_13 = new QGridLayout(groupBox_2);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        consoleMain = new Console(groupBox_2);
        consoleMain->setObjectName(QString::fromUtf8("consoleMain"));

        gridLayout_13->addWidget(consoleMain, 0, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_2, 4, 0, 1, 1);

        label_12 = new QLabel(tcp_tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_11->addWidget(label_12, 1, 0, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_11->addItem(verticalSpacer_10, 3, 0, 1, 1);

        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/tabIcons/connectTcp.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tcp_tab, icon12, QString());
        img_tab = new QWidget();
        img_tab->setObjectName(QString::fromUtf8("img_tab"));
        img_tab->setEnabled(true);
        gridLayout_7 = new QGridLayout(img_tab);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        line_3 = new QFrame(img_tab);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_3, 1, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_7->addItem(verticalSpacer_8, 2, 0, 1, 1);

        groupBox = new QGroupBox(img_tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(false);
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        jpgtls_latlabel = new QLabel(groupBox);
        jpgtls_latlabel->setObjectName(QString::fromUtf8("jpgtls_latlabel"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(jpgtls_latlabel->sizePolicy().hasHeightForWidth());
        jpgtls_latlabel->setSizePolicy(sizePolicy7);
        jpgtls_latlabel->setCursor(QCursor(Qt::IBeamCursor));
        jpgtls_latlabel->setTextFormat(Qt::AutoText);
        jpgtls_latlabel->setScaledContents(false);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, jpgtls_latlabel);

        jpgtls_latdisp = new QLabel(groupBox);
        jpgtls_latdisp->setObjectName(QString::fromUtf8("jpgtls_latdisp"));
        sizePolicy7.setHeightForWidth(jpgtls_latdisp->sizePolicy().hasHeightForWidth());
        jpgtls_latdisp->setSizePolicy(sizePolicy7);
        jpgtls_latdisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, jpgtls_latdisp);

        jpgtls_lonlabel = new QLabel(groupBox);
        jpgtls_lonlabel->setObjectName(QString::fromUtf8("jpgtls_lonlabel"));
        sizePolicy7.setHeightForWidth(jpgtls_lonlabel->sizePolicy().hasHeightForWidth());
        jpgtls_lonlabel->setSizePolicy(sizePolicy7);
        jpgtls_lonlabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, jpgtls_lonlabel);

        jpgtls_londisp = new QLabel(groupBox);
        jpgtls_londisp->setObjectName(QString::fromUtf8("jpgtls_londisp"));
        sizePolicy7.setHeightForWidth(jpgtls_londisp->sizePolicy().hasHeightForWidth());
        jpgtls_londisp->setSizePolicy(sizePolicy7);
        jpgtls_londisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, jpgtls_londisp);

        jpgtls_dxlabel = new QLabel(groupBox);
        jpgtls_dxlabel->setObjectName(QString::fromUtf8("jpgtls_dxlabel"));
        sizePolicy7.setHeightForWidth(jpgtls_dxlabel->sizePolicy().hasHeightForWidth());
        jpgtls_dxlabel->setSizePolicy(sizePolicy7);
        jpgtls_dxlabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, jpgtls_dxlabel);

        jpgtls_dxdisp = new QLabel(groupBox);
        jpgtls_dxdisp->setObjectName(QString::fromUtf8("jpgtls_dxdisp"));
        sizePolicy7.setHeightForWidth(jpgtls_dxdisp->sizePolicy().hasHeightForWidth());
        jpgtls_dxdisp->setSizePolicy(sizePolicy7);
        jpgtls_dxdisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, jpgtls_dxdisp);

        jpgtls_dylabel = new QLabel(groupBox);
        jpgtls_dylabel->setObjectName(QString::fromUtf8("jpgtls_dylabel"));
        sizePolicy7.setHeightForWidth(jpgtls_dylabel->sizePolicy().hasHeightForWidth());
        jpgtls_dylabel->setSizePolicy(sizePolicy7);
        jpgtls_dylabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, jpgtls_dylabel);

        jpgtls_dydisp = new QLabel(groupBox);
        jpgtls_dydisp->setObjectName(QString::fromUtf8("jpgtls_dydisp"));
        sizePolicy7.setHeightForWidth(jpgtls_dydisp->sizePolicy().hasHeightForWidth());
        jpgtls_dydisp->setSizePolicy(sizePolicy7);
        jpgtls_dydisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, jpgtls_dydisp);

        jpgtls_x0label = new QLabel(groupBox);
        jpgtls_x0label->setObjectName(QString::fromUtf8("jpgtls_x0label"));
        sizePolicy7.setHeightForWidth(jpgtls_x0label->sizePolicy().hasHeightForWidth());
        jpgtls_x0label->setSizePolicy(sizePolicy7);
        jpgtls_x0label->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, jpgtls_x0label);

        jpgtls_x0disp = new QLabel(groupBox);
        jpgtls_x0disp->setObjectName(QString::fromUtf8("jpgtls_x0disp"));
        sizePolicy7.setHeightForWidth(jpgtls_x0disp->sizePolicy().hasHeightForWidth());
        jpgtls_x0disp->setSizePolicy(sizePolicy7);
        jpgtls_x0disp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, jpgtls_x0disp);

        jpgtls_y0label = new QLabel(groupBox);
        jpgtls_y0label->setObjectName(QString::fromUtf8("jpgtls_y0label"));
        sizePolicy7.setHeightForWidth(jpgtls_y0label->sizePolicy().hasHeightForWidth());
        jpgtls_y0label->setSizePolicy(sizePolicy7);
        jpgtls_y0label->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, jpgtls_y0label);

        jpgtls_y0disp = new QLabel(groupBox);
        jpgtls_y0disp->setObjectName(QString::fromUtf8("jpgtls_y0disp"));
        sizePolicy7.setHeightForWidth(jpgtls_y0disp->sizePolicy().hasHeightForWidth());
        jpgtls_y0disp->setSizePolicy(sizePolicy7);
        jpgtls_y0disp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, jpgtls_y0disp);

        jpgtls_anglabel = new QLabel(groupBox);
        jpgtls_anglabel->setObjectName(QString::fromUtf8("jpgtls_anglabel"));
        sizePolicy7.setHeightForWidth(jpgtls_anglabel->sizePolicy().hasHeightForWidth());
        jpgtls_anglabel->setSizePolicy(sizePolicy7);
        jpgtls_anglabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, jpgtls_anglabel);

        jpgtls_angdisp = new QLabel(groupBox);
        jpgtls_angdisp->setObjectName(QString::fromUtf8("jpgtls_angdisp"));
        sizePolicy7.setHeightForWidth(jpgtls_angdisp->sizePolicy().hasHeightForWidth());
        jpgtls_angdisp->setSizePolicy(sizePolicy7);
        jpgtls_angdisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, jpgtls_angdisp);


        gridLayout_7->addWidget(groupBox, 10, 0, 1, 1);

        jpgButtonsLayout = new QGridLayout();
        jpgButtonsLayout->setObjectName(QString::fromUtf8("jpgButtonsLayout"));
        jpgButtonsLayout->setSizeConstraint(QLayout::SetMinimumSize);
        jpgButtonsLayout->setHorizontalSpacing(6);
        jpgButtonsLayout->setVerticalSpacing(1);
        showButton = new QPushButton(img_tab);
        showButton->setObjectName(QString::fromUtf8("showButton"));
        sizePolicy7.setHeightForWidth(showButton->sizePolicy().hasHeightForWidth());
        showButton->setSizePolicy(sizePolicy7);
        showButton->setToolTipDuration(1);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/img/toggle_overlay.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_toggledispico_A.png"), QSize(), QIcon::Active, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_toggledispico_A.png"), QSize(), QIcon::Selected, QIcon::Off);
        showButton->setIcon(icon13);
        showButton->setIconSize(QSize(16, 16));

        jpgButtonsLayout->addWidget(showButton, 0, 0, 1, 1);

        panButton = new QPushButton(img_tab);
        panButton->setObjectName(QString::fromUtf8("panButton"));
        sizePolicy7.setHeightForWidth(panButton->sizePolicy().hasHeightForWidth());
        panButton->setSizePolicy(sizePolicy7);
        panButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/img/jpg_pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon14.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_centeronjpgico_A.png"), QSize(), QIcon::Active, QIcon::Off);
        icon14.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_centeronjpgico_A.png"), QSize(), QIcon::Selected, QIcon::Off);
        panButton->setIcon(icon14);
        panButton->setIconSize(QSize(16, 16));
        panButton->setCheckable(false);
        panButton->setChecked(false);

        jpgButtonsLayout->addWidget(panButton, 0, 1, 1, 1);


        gridLayout_7->addLayout(jpgButtonsLayout, 4, 0, 1, 1);

        opacityLayout = new QHBoxLayout();
        opacityLayout->setSpacing(10);
        opacityLayout->setObjectName(QString::fromUtf8("opacityLayout"));
        opacityLayout->setContentsMargins(0, 0, -1, -1);
        opacityLabel = new QLabel(img_tab);
        opacityLabel->setObjectName(QString::fromUtf8("opacityLabel"));
        sizePolicy4.setHeightForWidth(opacityLabel->sizePolicy().hasHeightForWidth());
        opacityLabel->setSizePolicy(sizePolicy4);
        opacityLabel->setFrameShape(QFrame::NoFrame);
        opacityLabel->setFrameShadow(QFrame::Sunken);
        opacityLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        opacityLayout->addWidget(opacityLabel);

        opacitySlider = new QSlider(img_tab);
        opacitySlider->setObjectName(QString::fromUtf8("opacitySlider"));
        opacitySlider->setEnabled(true);
        sizePolicy5.setHeightForWidth(opacitySlider->sizePolicy().hasHeightForWidth());
        opacitySlider->setSizePolicy(sizePolicy5);
        opacitySlider->setCursor(QCursor(Qt::SizeHorCursor));
        opacitySlider->setValue(99);
        opacitySlider->setOrientation(Qt::Horizontal);
        opacitySlider->setInvertedAppearance(true);

        opacityLayout->addWidget(opacitySlider);


        gridLayout_7->addLayout(opacityLayout, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        jpg_gleft = new QToolButton(img_tab);
        jpg_gleft->setObjectName(QString::fromUtf8("jpg_gleft"));
        jpg_gleft->setEnabled(false);
        sizePolicy6.setHeightForWidth(jpg_gleft->sizePolicy().hasHeightForWidth());
        jpg_gleft->setSizePolicy(sizePolicy6);
        jpg_gleft->setCursor(QCursor(Qt::PointingHandCursor));
        jpg_gleft->setIconSize(QSize(10, 10));
        jpg_gleft->setCheckable(false);
        jpg_gleft->setChecked(false);
        jpg_gleft->setAutoRaise(true);
        jpg_gleft->setArrowType(Qt::LeftArrow);

        horizontalLayout->addWidget(jpg_gleft);

        jpgtls_filenamelabel = new QLabel(img_tab);
        jpgtls_filenamelabel->setObjectName(QString::fromUtf8("jpgtls_filenamelabel"));
        sizePolicy7.setHeightForWidth(jpgtls_filenamelabel->sizePolicy().hasHeightForWidth());
        jpgtls_filenamelabel->setSizePolicy(sizePolicy7);
        jpgtls_filenamelabel->setCursor(QCursor(Qt::IBeamCursor));
        jpgtls_filenamelabel->setTextFormat(Qt::AutoText);

        horizontalLayout->addWidget(jpgtls_filenamelabel);

        jpgtls_filenamedisp = new QLabel(img_tab);
        jpgtls_filenamedisp->setObjectName(QString::fromUtf8("jpgtls_filenamedisp"));
        sizePolicy7.setHeightForWidth(jpgtls_filenamedisp->sizePolicy().hasHeightForWidth());
        jpgtls_filenamedisp->setSizePolicy(sizePolicy7);
        jpgtls_filenamedisp->setCursor(QCursor(Qt::IBeamCursor));

        horizontalLayout->addWidget(jpgtls_filenamedisp);

        jpg_gright = new QToolButton(img_tab);
        jpg_gright->setObjectName(QString::fromUtf8("jpg_gright"));
        jpg_gright->setEnabled(false);
        sizePolicy6.setHeightForWidth(jpg_gright->sizePolicy().hasHeightForWidth());
        jpg_gright->setSizePolicy(sizePolicy6);
        jpg_gright->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon15.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right_disabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        jpg_gright->setIcon(icon15);
        jpg_gright->setIconSize(QSize(10, 10));
        jpg_gright->setCheckable(false);
        jpg_gright->setChecked(false);
        jpg_gright->setAutoRaise(true);
        jpg_gright->setArrowType(Qt::RightArrow);

        horizontalLayout->addWidget(jpg_gright);


        gridLayout_7->addLayout(horizontalLayout, 6, 0, 1, 1);

        pushButton_3 = new QPushButton(img_tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setEnabled(false);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/img/toggle_overlay.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon16);

        gridLayout_7->addWidget(pushButton_3, 5, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_5, 14, 0, 1, 1);

        label_7 = new QLabel(img_tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_7->addWidget(label_7, 0, 0, 1, 1);

        transformJPGbox = new QGroupBox(img_tab);
        transformJPGbox->setObjectName(QString::fromUtf8("transformJPGbox"));
        transformJPGbox->setEnabled(false);
        gridLayout_9 = new QGridLayout(transformJPGbox);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        t_rotation = new QDial(transformJPGbox);
        t_rotation->setObjectName(QString::fromUtf8("t_rotation"));
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(t_rotation->sizePolicy().hasHeightForWidth());
        t_rotation->setSizePolicy(sizePolicy8);
        t_rotation->setMaximum(360);
        t_rotation->setOrientation(Qt::Horizontal);
        t_rotation->setWrapping(false);
        t_rotation->setNotchTarget(30.000000000000000);
        t_rotation->setNotchesVisible(true);

        gridLayout_9->addWidget(t_rotation, 0, 5, 4, 1);

        t_ySpin = new QDoubleSpinBox(transformJPGbox);
        t_ySpin->setObjectName(QString::fromUtf8("t_ySpin"));
        t_ySpin->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        t_ySpin->setAccelerated(true);
        t_ySpin->setDecimals(1);
        t_ySpin->setMinimum(-10000.000000000000000);
        t_ySpin->setMaximum(10000.000000000000000);
        t_ySpin->setSingleStep(3.000000000000000);

        gridLayout_9->addWidget(t_ySpin, 1, 1, 1, 1);

        label_10 = new QLabel(transformJPGbox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_9->addWidget(label_10, 2, 0, 1, 1);

        t_rSpin = new QDoubleSpinBox(transformJPGbox);
        t_rSpin->setObjectName(QString::fromUtf8("t_rSpin"));
        t_rSpin->setMinimum(-360.000000000000000);
        t_rSpin->setMaximum(360.000000000000000);

        gridLayout_9->addWidget(t_rSpin, 2, 1, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setVerticalSpacing(0);
        t_right = new QPushButton(transformJPGbox);
        t_right->setObjectName(QString::fromUtf8("t_right"));
        sizePolicy6.setHeightForWidth(t_right->sizePolicy().hasHeightForWidth());
        t_right->setSizePolicy(sizePolicy6);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        t_right->setIcon(icon17);

        gridLayout_10->addWidget(t_right, 1, 2, 1, 1);

        t_left = new QPushButton(transformJPGbox);
        t_left->setObjectName(QString::fromUtf8("t_left"));
        sizePolicy6.setHeightForWidth(t_left->sizePolicy().hasHeightForWidth());
        t_left->setSizePolicy(sizePolicy6);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        t_left->setIcon(icon18);

        gridLayout_10->addWidget(t_left, 1, 0, 1, 1);

        t_up = new QPushButton(transformJPGbox);
        t_up->setObjectName(QString::fromUtf8("t_up"));
        sizePolicy6.setHeightForWidth(t_up->sizePolicy().hasHeightForWidth());
        t_up->setSizePolicy(sizePolicy6);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        t_up->setIcon(icon19);

        gridLayout_10->addWidget(t_up, 0, 1, 1, 1);

        t_down = new QPushButton(transformJPGbox);
        t_down->setObjectName(QString::fromUtf8("t_down"));
        sizePolicy6.setHeightForWidth(t_down->sizePolicy().hasHeightForWidth());
        t_down->setSizePolicy(sizePolicy6);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        t_down->setIcon(icon20);

        gridLayout_10->addWidget(t_down, 2, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_10, 0, 3, 4, 2);

        t_xSpin = new QDoubleSpinBox(transformJPGbox);
        t_xSpin->setObjectName(QString::fromUtf8("t_xSpin"));
        t_xSpin->setFont(font);
        t_xSpin->setWrapping(false);
        t_xSpin->setFrame(true);
        t_xSpin->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        t_xSpin->setAccelerated(true);
        t_xSpin->setDecimals(1);
        t_xSpin->setMinimum(-10000.000000000000000);
        t_xSpin->setMaximum(10000.000000000000000);
        t_xSpin->setSingleStep(3.000000000000000);

        gridLayout_9->addWidget(t_xSpin, 0, 1, 1, 1);

        label_8 = new QLabel(transformJPGbox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_9->addWidget(label_8, 0, 0, 1, 1);

        t_sSpin = new QDoubleSpinBox(transformJPGbox);
        t_sSpin->setObjectName(QString::fromUtf8("t_sSpin"));
        t_sSpin->setDecimals(1);
        t_sSpin->setMinimum(-1.500000000000000);
        t_sSpin->setMaximum(1.500000000000000);
        t_sSpin->setSingleStep(0.100000000000000);
        t_sSpin->setValue(0.000000000000000);

        gridLayout_9->addWidget(t_sSpin, 3, 1, 1, 1);

        t_scale = new QScrollBar(transformJPGbox);
        t_scale->setObjectName(QString::fromUtf8("t_scale"));
        t_scale->setMinimum(-150);
        t_scale->setMaximum(150);
        t_scale->setValue(0);
        t_scale->setOrientation(Qt::Vertical);

        gridLayout_9->addWidget(t_scale, 0, 2, 4, 1);

        label_9 = new QLabel(transformJPGbox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_9->addWidget(label_9, 1, 0, 1, 1);

        label_11 = new QLabel(transformJPGbox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_9->addWidget(label_11, 3, 0, 1, 1);


        gridLayout_7->addWidget(transformJPGbox, 13, 0, 1, 1);

        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/tabIcons/jpg.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(img_tab, icon21, QString());
        cfg_tab = new QWidget();
        cfg_tab->setObjectName(QString::fromUtf8("cfg_tab"));
        gridLayout_6 = new QGridLayout(cfg_tab);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_14 = new QLabel(cfg_tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_6->addWidget(label_14, 7, 0, 1, 1);

        label_2 = new QLabel(cfg_tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        gridLayout_6->addWidget(label_2, 3, 0, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_6->addItem(verticalSpacer_11, 2, 0, 1, 1);

        label_20 = new QLabel(cfg_tab);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_6->addWidget(label_20, 0, 0, 1, 4);

        TCPIPxml = new QLineEdit(cfg_tab);
        TCPIPxml->setObjectName(QString::fromUtf8("TCPIPxml"));
        TCPIPxml->setInputMethodHints(Qt::ImhNone);
        TCPIPxml->setMaxLength(15);

        gridLayout_6->addWidget(TCPIPxml, 5, 1, 1, 2);

        label_3 = new QLabel(cfg_tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);

        gridLayout_6->addWidget(label_3, 4, 0, 1, 1);

        refreshtelemetryxml = new QDoubleSpinBox(cfg_tab);
        refreshtelemetryxml->setObjectName(QString::fromUtf8("refreshtelemetryxml"));
        refreshtelemetryxml->setMinimum(0.050000000000000);
        refreshtelemetryxml->setMaximum(100.000000000000000);
        refreshtelemetryxml->setSingleStep(0.500000000000000);
        refreshtelemetryxml->setValue(0.500000000000000);

        gridLayout_6->addWidget(refreshtelemetryxml, 6, 1, 1, 3);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_18 = new QLabel(cfg_tab);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_12->addWidget(label_18, 1, 2, 1, 1);

        label_15 = new QLabel(cfg_tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_12->addWidget(label_15, 0, 0, 1, 1);

        label_16 = new QLabel(cfg_tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_12->addWidget(label_16, 0, 2, 1, 1);

        diaThetaAzimuth = new QDoubleSpinBox(cfg_tab);
        diaThetaAzimuth->setObjectName(QString::fromUtf8("diaThetaAzimuth"));
        diaThetaAzimuth->setMaximum(360.000000000000000);
        diaThetaAzimuth->setValue(15.000000000000000);

        gridLayout_12->addWidget(diaThetaAzimuth, 1, 1, 1, 1);

        label_17 = new QLabel(cfg_tab);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_12->addWidget(label_17, 1, 0, 1, 1);

        diaDriftAngle = new QDoubleSpinBox(cfg_tab);
        diaDriftAngle->setObjectName(QString::fromUtf8("diaDriftAngle"));
        diaDriftAngle->setMaximum(360.000000000000000);
        diaDriftAngle->setValue(13.000000000000000);

        gridLayout_12->addWidget(diaDriftAngle, 1, 3, 1, 1);

        diaTimexml = new QDoubleSpinBox(cfg_tab);
        diaTimexml->setObjectName(QString::fromUtf8("diaTimexml"));
        diaTimexml->setDecimals(1);
        diaTimexml->setMinimum(1.000000000000000);
        diaTimexml->setMaximum(50.000000000000000);
        diaTimexml->setValue(15.000000000000000);

        gridLayout_12->addWidget(diaTimexml, 0, 1, 1, 1);

        diaRangexml = new QDoubleSpinBox(cfg_tab);
        diaRangexml->setObjectName(QString::fromUtf8("diaRangexml"));
        diaRangexml->setDecimals(1);
        diaRangexml->setMaximum(30.000000000000000);
        diaRangexml->setValue(3.000000000000000);

        gridLayout_12->addWidget(diaRangexml, 0, 3, 1, 1);

        label_19 = new QLabel(cfg_tab);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_12->addWidget(label_19, 2, 0, 1, 1);

        providerGoogle = new QRadioButton(cfg_tab);
        providerGoogle->setObjectName(QString::fromUtf8("providerGoogle"));
        providerGoogle->setToolTipDuration(5000);
        providerGoogle->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"  background-color: transparent;\n"
"  color: #03DAC6;\n"
"  spacing: 4px;\n"
"  padding-top: 4px;\n"
"  padding-bottom: 4px;\n"
"  border: none;\n"
"  outline: none;\n"
"}\n"
"\n"
"QRadioButton:focus {\n"
"  border: none;\n"
"}\n"
"\n"
"QRadioButton:disabled {\n"
"  background-color: #19232D;\n"
"  color: #9DA9B5;\n"
"  border: none;\n"
"  outline: none;\n"
"}\n"
"\n"
"QRadioButton QWidget {\n"
"  background-color: transparent;\n"
"  color: #E0E1E3;\n"
"  spacing: 0px;\n"
"  padding: 0px;\n"
"  outline: none;\n"
"  border: none;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"  border: none;\n"
"  outline: none;\n"
"  margin-left: 2px;\n"
"  height: 14px;\n"
"  width: 14px;\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked {\n"
"  image: url(\":/qss_icons/dark/rc/radio_unchecked.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover, QRadioButton::indicator:unchecked:focus, QRadioButton::indicator:unchecked:pressed {\n"
"  border: none;\n"
"  outline: none;\n"
"  image: url(\":/qss_icon"
                        "s/dark/rc/radio_unchecked_focus.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:disabled {\n"
"  image: url(\":/qss_icons/dark/rc/radio_unchecked_disabled.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"  border: none;\n"
"  outline: none;\n"
"  image: url(\":/qss_icons/dark/rc/radio_checked.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:hover, QRadioButton::indicator:checked:focus, QRadioButton::indicator:checked:pressed {\n"
"  border: none;\n"
"  outline: none;\n"
"  image: url(\":/qss_icons/dark/rc/radio_checked_focus.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:disabled {\n"
"  outline: none;\n"
"  image: url(\":/qss_icons/dark/rc/radio_checked_disabled.png\");\n"
"}\n"
""));
        providerGoogle->setChecked(true);

        gridLayout_12->addWidget(providerGoogle, 2, 1, 1, 1);

        providerESRI = new QRadioButton(cfg_tab);
        providerESRI->setObjectName(QString::fromUtf8("providerESRI"));

        gridLayout_12->addWidget(providerESRI, 2, 2, 1, 1);

        providerOSM = new QRadioButton(cfg_tab);
        providerOSM->setObjectName(QString::fromUtf8("providerOSM"));
        providerOSM->setToolTipDuration(5000);
        providerOSM->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"  background-color: transparent;\n"
"	color: #CF6679;\n"
"  spacing: 4px;\n"
"  padding-top: 4px;\n"
"  padding-bottom: 4px;\n"
"  border: none;\n"
"  outline: none;\n"
"}\n"
"\n"
"QRadioButton:focus {\n"
"  border: none;\n"
"}\n"
"\n"
"QRadioButton:disabled {\n"
"  background-color: #19232D;\n"
"  color: #9DA9B5;\n"
"  border: none;\n"
"  outline: none;\n"
"}\n"
"\n"
"QRadioButton QWidget {\n"
"  background-color: transparent;\n"
"  color: #E0E1E3;\n"
"  spacing: 0px;\n"
"  padding: 0px;\n"
"  outline: none;\n"
"  border: none;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"  border: none;\n"
"  outline: none;\n"
"  margin-left: 2px;\n"
"  height: 14px;\n"
"  width: 14px;\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked {\n"
"  image: url(\":/qss_icons/dark/rc/radio_unchecked.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover, QRadioButton::indicator:unchecked:focus, QRadioButton::indicator:unchecked:pressed {\n"
"  border: none;\n"
"  outline: none;\n"
"  image: url(\":/qss_icons"
                        "/dark/rc/radio_unchecked_focus.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:disabled {\n"
"  image: url(\":/qss_icons/dark/rc/radio_unchecked_disabled.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"  border: none;\n"
"  outline: none;\n"
"  image: url(\":/qss_icons/dark/rc/radio_checked.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:hover, QRadioButton::indicator:checked:focus, QRadioButton::indicator:checked:pressed {\n"
"  border: none;\n"
"  outline: none;\n"
"  image: url(\":/qss_icons/dark/rc/radio_checked_focus.png\");\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:disabled {\n"
"  outline: none;\n"
"  image: url(\":/qss_icons/dark/rc/radio_checked_disabled.png\");\n"
"}\n"
""));

        gridLayout_12->addWidget(providerOSM, 2, 3, 1, 1);


        gridLayout_6->addLayout(gridLayout_12, 8, 0, 1, 4);

        predictRangexml = new QDoubleSpinBox(cfg_tab);
        predictRangexml->setObjectName(QString::fromUtf8("predictRangexml"));
        predictRangexml->setDecimals(1);
        predictRangexml->setMaximum(20.000000000000000);
        predictRangexml->setValue(5.000000000000000);

        gridLayout_6->addWidget(predictRangexml, 7, 1, 1, 3);

        label_13 = new QLabel(cfg_tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_6->addWidget(label_13, 6, 0, 1, 1);

        TCPPortxml = new QLineEdit(cfg_tab);
        TCPPortxml->setObjectName(QString::fromUtf8("TCPPortxml"));
        TCPPortxml->setMaximumSize(QSize(50, 16777215));
        TCPPortxml->setMaxLength(5);

        gridLayout_6->addWidget(TCPPortxml, 5, 3, 1, 1);

        selectFolderButton = new QPushButton(cfg_tab);
        selectFolderButton->setObjectName(QString::fromUtf8("selectFolderButton"));

        gridLayout_6->addWidget(selectFolderButton, 3, 2, 1, 2);

        UDPIPxml = new QLineEdit(cfg_tab);
        UDPIPxml->setObjectName(QString::fromUtf8("UDPIPxml"));
        UDPIPxml->setMaxLength(15);
        UDPIPxml->setClearButtonEnabled(false);

        gridLayout_6->addWidget(UDPIPxml, 4, 1, 1, 2);

        label_4 = new QLabel(cfg_tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_6->addWidget(label_4, 5, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_4, 12, 0, 1, 1);

        line_5 = new QFrame(cfg_tab);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_5, 1, 0, 1, 4);

        UDPPortxml = new QLineEdit(cfg_tab);
        UDPPortxml->setObjectName(QString::fromUtf8("UDPPortxml"));
        sizePolicy6.setHeightForWidth(UDPPortxml->sizePolicy().hasHeightForWidth());
        UDPPortxml->setSizePolicy(sizePolicy6);
        UDPPortxml->setMaximumSize(QSize(50, 16777215));
        UDPPortxml->setMaxLength(5);
        UDPPortxml->setFrame(true);
        UDPPortxml->setEchoMode(QLineEdit::Normal);

        gridLayout_6->addWidget(UDPPortxml, 4, 3, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        saveSettings = new QPushButton(cfg_tab);
        saveSettings->setObjectName(QString::fromUtf8("saveSettings"));
        saveSettings->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: #521AD5;\n"
"  color: #E0E1E3;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"  border: none;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"  background-color: #222222;\n"
"  color: #AAAAAA;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"  background-color: #93E5DD;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"}\n"
"\n"
"QPushButton:checked:disabled {\n"
"  background-color: #272727;\n"
"  color: #AAAAAA;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"}\n"
"\n"
"QPushButton:checked:selected {\n"
"  background: #93E5DD;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: #BBBBBB;\n"
"  color: #E0E1E3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"  background-color: #93E5DD;\n"
"}\n"
"\n"
"QPushButton:selected {\n"
"  background: #93E5DD;\n"
"  color: #E0E1E3;\n"
"}\n"
"\n"
"QPushButton::menu-indicator {\n"
"  subcontrol-origin: padding;\n"
"  subcontrol-position:"
                        " bottom right;\n"
"  bottom: 4px;\n"
"}"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/img/save_white.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveSettings->setIcon(icon22);

        horizontalLayout_4->addWidget(saveSettings);

        discardSettings = new QPushButton(cfg_tab);
        discardSettings->setObjectName(QString::fromUtf8("discardSettings"));
        discardSettings->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: #b46363;\n"
"  color: #E0E1E3;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"  border: none;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"  background-color: #222222;\n"
"  color: #AAAAAA;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"}\n"
"\n"
"QPushButton:checked {\n"
"  background-color: #93E5DD;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"}\n"
"\n"
"QPushButton:checked:disabled {\n"
"  background-color: #272727;\n"
"  color: #AAAAAA;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"}\n"
"\n"
"QPushButton:checked:selected {\n"
"  background: #93E5DD;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: #BBBBBB;\n"
"  color: #E0E1E3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"  background-color: #93E5DD;\n"
"}\n"
"\n"
"QPushButton:selected {\n"
"  background: #93E5DD;\n"
"  color: #E0E1E3;\n"
"}\n"
"\n"
"QPushButton::menu-indicator {\n"
"  subcontrol-origin: padding;\n"
"  subcontrol-position:"
                        " bottom right;\n"
"  bottom: 4px;\n"
"}"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/img/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        discardSettings->setIcon(icon23);

        horizontalLayout_4->addWidget(discardSettings);


        gridLayout_6->addLayout(horizontalLayout_4, 9, 0, 1, 4);

        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/tabIcons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(cfg_tab, icon24, QString());
        link_tab = new QWidget();
        link_tab->setObjectName(QString::fromUtf8("link_tab"));
        verticalLayout_2 = new QVBoxLayout(link_tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(link_tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        line_2 = new QFrame(link_tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        verticalSpacer_7 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_7);

        UDPConsole = new QGroupBox(link_tab);
        UDPConsole->setObjectName(QString::fromUtf8("UDPConsole"));
        sizePolicy2.setHeightForWidth(UDPConsole->sizePolicy().hasHeightForWidth());
        UDPConsole->setSizePolicy(sizePolicy2);
        UDPConsole->setMinimumSize(QSize(452, 170));
        UDPConsole->setAutoFillBackground(false);
        UDPConsole->setFlat(false);
        UDPConsole->setCheckable(false);
        gridLayout_4 = new QGridLayout(UDPConsole);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton_2 = new QPushButton(UDPConsole);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(true);
        sizePolicy5.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy5);
        pushButton_2->setCheckable(false);

        gridLayout_4->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton = new QPushButton(UDPConsole);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);
        sizePolicy5.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy5);
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setCheckable(false);

        gridLayout_4->addWidget(pushButton, 1, 0, 1, 1);

        udpStopButton = new QPushButton(UDPConsole);
        udpStopButton->setObjectName(QString::fromUtf8("udpStopButton"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(udpStopButton->sizePolicy().hasHeightForWidth());
        udpStopButton->setSizePolicy(sizePolicy9);
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/img/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        udpStopButton->setIcon(icon25);
        udpStopButton->setIconSize(QSize(12, 12));

        gridLayout_4->addWidget(udpStopButton, 1, 2, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        udpIn = new QTextEdit(UDPConsole);
        udpIn->setObjectName(QString::fromUtf8("udpIn"));
        sizePolicy4.setHeightForWidth(udpIn->sizePolicy().hasHeightForWidth());
        udpIn->setSizePolicy(sizePolicy4);
        udpIn->setMinimumSize(QSize(0, 20));
        udpIn->setMaximumSize(QSize(16777215, 20));
        udpIn->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        udpIn->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        udpIn->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse|Qt::TextBrowserInteraction|Qt::TextEditable|Qt::TextEditorInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(udpIn, 1, 0, 1, 1);

        udpSendButton = new QPushButton(UDPConsole);
        udpSendButton->setObjectName(QString::fromUtf8("udpSendButton"));
        sizePolicy6.setHeightForWidth(udpSendButton->sizePolicy().hasHeightForWidth());
        udpSendButton->setSizePolicy(sizePolicy6);
        udpSendButton->setMinimumSize(QSize(20, 20));
        udpSendButton->setMaximumSize(QSize(20, 20));
        udpSendButton->setSizeIncrement(QSize(0, 0));
        udpSendButton->setStyleSheet(QString::fromUtf8("\n"
"border-radius: 1px;"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        udpSendButton->setIcon(icon26);
        udpSendButton->setIconSize(QSize(10, 10));

        gridLayout_3->addWidget(udpSendButton, 1, 1, 1, 1);

        udpDisp = new QTextEdit(UDPConsole);
        udpDisp->setObjectName(QString::fromUtf8("udpDisp"));
        sizePolicy2.setHeightForWidth(udpDisp->sizePolicy().hasHeightForWidth());
        udpDisp->setSizePolicy(sizePolicy2);
        udpDisp->setReadOnly(true);

        gridLayout_3->addWidget(udpDisp, 0, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 3);


        verticalLayout_2->addWidget(UDPConsole);

        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/tabIcons/connectUdp.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(link_tab, icon27, QString());
        info_tab = new QWidget();
        info_tab->setObjectName(QString::fromUtf8("info_tab"));
        gridLayout_8 = new QGridLayout(info_tab);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        DecodeJPG = new QPushButton(info_tab);
        DecodeJPG->setObjectName(QString::fromUtf8("DecodeJPG"));
        DecodeJPG->setEnabled(true);
        sizePolicy6.setHeightForWidth(DecodeJPG->sizePolicy().hasHeightForWidth());
        DecodeJPG->setSizePolicy(sizePolicy6);
        DecodeJPG->setMaximumSize(QSize(1, 1));
        DecodeJPG->setAutoDefault(true);
        DecodeJPG->setFlat(true);

        gridLayout_8->addWidget(DecodeJPG, 1, 1, 1, 1);

        infoLabel = new QLabel(info_tab);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));

        gridLayout_8->addWidget(infoLabel, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 2, 0, 1, 1);

        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/tabIcons/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(info_tab, icon28, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        uiSAR->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(uiSAR);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        uiSAR->setStatusBar(statusBar);
        docker = new QDockWidget(uiSAR);
        docker->setObjectName(QString::fromUtf8("docker"));
        QSizePolicy sizePolicy10(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(docker->sizePolicy().hasHeightForWidth());
        docker->setSizePolicy(sizePolicy10);
        docker->setMinimumSize(QSize(325, 58));
        docker->setMaximumSize(QSize(524287, 58));
        docker->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        docker->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gpsPanClone = new QPushButton(dockWidgetContents_2);
        gpsPanClone->setObjectName(QString::fromUtf8("gpsPanClone"));
        gpsPanClone->setEnabled(true);
        sizePolicy6.setHeightForWidth(gpsPanClone->sizePolicy().hasHeightForWidth());
        gpsPanClone->setSizePolicy(sizePolicy6);
        gpsPanClone->setIcon(icon10);

        horizontalLayout_2->addWidget(gpsPanClone);

        rulerButton = new QPushButton(dockWidgetContents_2);
        rulerButton->setObjectName(QString::fromUtf8("rulerButton"));
        rulerButton->setEnabled(false);
        sizePolicy6.setHeightForWidth(rulerButton->sizePolicy().hasHeightForWidth());
        rulerButton->setSizePolicy(sizePolicy6);
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/img/ruler.png"), QSize(), QIcon::Normal, QIcon::Off);
        rulerButton->setIcon(icon29);

        horizontalLayout_2->addWidget(rulerButton);

        changeMapMode = new QPushButton(dockWidgetContents_2);
        changeMapMode->setObjectName(QString::fromUtf8("changeMapMode"));
        changeMapMode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color:#7c513a;\n"
"  color: #E0E1E3;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"  border: none;\n"
"}\n"
"\n"
"\n"
"QPushButton:checked {\n"
"  background-color:#00564d;\n"
"  border-radius: 4px;\n"
"  padding: 2px;\n"
"  outline: none;\n"
"}\n"
"\n"
"QPushButton:checked:selected {\n"
"  background: rgb(207, 255, 176);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: #AAAAAA;\n"
"  color: #E0E1E3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"  background-color: #60798B;\n"
"}\n"
"\n"
"QPushButton:selected {\n"
"  background: #60798B;\n"
"  color: #E0E1E3;\n"
"}"));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/img/swapMode.png"), QSize(), QIcon::Normal, QIcon::Off);
        changeMapMode->setIcon(icon30);
        changeMapMode->setCheckable(true);
        changeMapMode->setChecked(true);

        horizontalLayout_2->addWidget(changeMapMode);

        docker->setWidget(dockWidgetContents_2);
        uiSAR->addDockWidget(Qt::TopDockWidgetArea, docker);

        retranslateUi(uiSAR);

        tabWidget->setCurrentIndex(5);
        DecodeJPG->setDefault(false);


        QMetaObject::connectSlotsByName(uiSAR);
    } // setupUi

    void retranslateUi(QMainWindow *uiSAR)
    {
        uiSAR->setWindowTitle(QCoreApplication::translate("uiSAR", "\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\270\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201 \320\240\320\233\320\241", nullptr));
        NAVSAR->setTitle(QCoreApplication::translate("uiSAR", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\320\276\320\275\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        nav_latlabel->setText(QCoreApplication::translate("uiSAR", "\320\250\320\270\321\200\320\276\321\202\320\260", nullptr));
        nav_latdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        nav_lonlabel->setText(QCoreApplication::translate("uiSAR", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260", nullptr));
        nav_londisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        nav_acclabel->setText(QCoreApplication::translate("uiSAR", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        nav_accdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        nav_altlabel->setText(QCoreApplication::translate("uiSAR", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        nav_altdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213 \320\272\320\260\321\200\321\202\321\213</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("uiSAR", "\320\234\320\260\321\200\320\272\320\265\321\200\321\213 \320\275\320\260 \320\272\320\260\321\200\321\202\320\265", nullptr));
        placeMarkerButton->setText(QCoreApplication::translate("uiSAR", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\274\320\260\321\200\320\272\320\265\321\200", nullptr));
        saveMarkerButton->setText(QString());
        loadMarkerButton->setText(QString());
        nav_follow->setText(QCoreApplication::translate("uiSAR", "\320\241\320\273\320\265\320\264\320\270\321\202\321\214 \320\267\320\260 \321\201\320\260\320\274\320\276\320\273\320\265\321\202\320\276\320\274", nullptr));
        nav_displaytriangle->setText(QCoreApplication::translate("uiSAR", "\320\224\320\270\320\260\320\263\321\200\320\260\320\274\320\274\320\260 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\275\320\276\321\201\321\202\320\270", nullptr));
        planeCheckbox->setText(QCoreApplication::translate("uiSAR", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\261\320\276\321\200\321\202\320\260", nullptr));
        showCoordsBox->setText(QCoreApplication::translate("uiSAR", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\272\321\203\321\200\321\201\320\276\321\200\320\260", nullptr));
        nav_displayroute->setText(QCoreApplication::translate("uiSAR", "\320\242\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \320\277\320\276\320\273\320\265\321\202\320\260", nullptr));
        checkBox->setText(QCoreApplication::translate("uiSAR", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\276\320\273\320\265\321\202\320\260", nullptr));
        panGPS->setText(QCoreApplication::translate("uiSAR", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\240\320\233\320\241", nullptr));
        clearTrack->setText(QCoreApplication::translate("uiSAR", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\202\321\200\320\265\320\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(map_tab), QString());
        groupBox_2->setTitle(QCoreApplication::translate("uiSAR", "\320\232\320\276\320\275\321\201\320\276\320\273\321\214", nullptr));
        label_12->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\243\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\265 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265 \321\201 \320\240\320\233\320\241</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tcp_tab), QString());
        groupBox->setTitle(QCoreApplication::translate("uiSAR", "\320\234\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\320\265 \320\240\320\233\320\230", nullptr));
        jpgtls_latlabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">\320\250\320\270\321\200\320\276\321\202\320\260</span></p></body></html>", nullptr));
        jpgtls_latdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpgtls_lonlabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">\320\224\320\276\320\273\320\263\320\276\321\202\320\260:</span></p></body></html>", nullptr));
        jpgtls_londisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpgtls_dxlabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">\316\224x:</span></p></body></html>", nullptr));
        jpgtls_dxdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpgtls_dylabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">\316\224y:</span></p></body></html>", nullptr));
        jpgtls_dydisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpgtls_x0label->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">x</span><span style=\" font-size:7pt; vertical-align:sub;\">0</span><span style=\" font-size:7pt;\">:</span></p></body></html>", nullptr));
        jpgtls_x0disp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpgtls_y0label->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">y</span><span style=\" font-size:7pt; vertical-align:sub;\">0</span><span style=\" font-size:7pt;\">:</span></p></body></html>", nullptr));
        jpgtls_y0disp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpgtls_anglabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-size:7pt;\">\320\243\320\263\320\276\320\273:</span></p></body></html>", nullptr));
        jpgtls_angdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-size:7pt; font-weight:600;\">-----------</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        showButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        showButton->setText(QCoreApplication::translate("uiSAR", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\240\320\233\320\230", nullptr));
        panButton->setText(QCoreApplication::translate("uiSAR", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\240\320\233\320\230 ", nullptr));
        opacityLabel->setText(QCoreApplication::translate("uiSAR", "\320\237\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214 \321\201\320\273\320\276\321\217 \320\240\320\233\320\230", nullptr));
        jpg_gleft->setText(QString());
        jpgtls_filenamelabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p>\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \321\204\320\260\320\271\320\273:</p></body></html>", nullptr));
        jpgtls_filenamedisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpg_gright->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("uiSAR", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\262\321\201\320\265", nullptr));
        label_7->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\240\320\260\320\264\320\270\320\276\320\273\320\276\320\272\320\260\321\206\320\270\320\276\320\275\320\275\321\213\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217</span></p></body></html>", nullptr));
        transformJPGbox->setTitle(QCoreApplication::translate("uiSAR", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\263\320\265\320\276\320\274\320\265\321\202\321\200\320\270\320\270 \320\240\320\233\320\230", nullptr));
        t_ySpin->setSuffix(QCoreApplication::translate("uiSAR", " \320\274", nullptr));
        label_10->setText(QCoreApplication::translate("uiSAR", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217 \320\262\321\200\320\260\321\211\320\265\320\275\320\270\321\217", nullptr));
        t_rSpin->setSuffix(QCoreApplication::translate("uiSAR", " \342\210\230", nullptr));
        t_right->setText(QString());
        t_left->setText(QString());
        t_up->setText(QString());
        t_down->setText(QString());
        t_xSpin->setPrefix(QString());
        t_xSpin->setSuffix(QCoreApplication::translate("uiSAR", " \320\274", nullptr));
        label_8->setText(QCoreApplication::translate("uiSAR", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217 \320\277\320\276 X", nullptr));
        label_9->setText(QCoreApplication::translate("uiSAR", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217 \320\277\320\276 Y", nullptr));
        label_11->setText(QCoreApplication::translate("uiSAR", "\320\232\320\276\321\200\321\200\320\265\320\272\321\206\320\270\321\217 \321\200\320\260\320\267\320\274\320\265\321\200\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(img_tab), QString());
        label_14->setText(QCoreApplication::translate("uiSAR", "\320\224\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\276\321\202\321\200\320\270\321\201\320\276\320\262\320\272\320\270 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217 \320\277\320\276\320\273\320\265\321\202\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("uiSAR", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263 \320\277\320\276\320\270\321\201\320\272\320\260 \321\200\320\260\320\264\320\270\320\276\320\273\320\276\320\272\320\260\321\206\320\270\320\276\320\275\320\275\321\213\321\205 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\271:", nullptr));
        label_20->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("uiSAR", "\320\220\320\264\321\200\320\265\321\201 UDP \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216:", nullptr));
        refreshtelemetryxml->setSuffix(QCoreApplication::translate("uiSAR", " c", nullptr));
        label_18->setText(QCoreApplication::translate("uiSAR", "\320\243\320\263\320\276\320\273 \321\201\320\275\320\276\321\201\320\260:", nullptr));
        label_15->setText(QCoreApplication::translate("uiSAR", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \321\201\321\212\320\265\320\274\320\272\320\270:", nullptr));
        label_16->setText(QCoreApplication::translate("uiSAR", "\320\224\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \321\201\321\212\320\265\320\274\320\272\320\270:", nullptr));
        diaThetaAzimuth->setSuffix(QCoreApplication::translate("uiSAR", " \302\260", nullptr));
        label_17->setText(QCoreApplication::translate("uiSAR", "\316\270-\320\260\320\267\320\270\320\274\321\203\321\202:", nullptr));
        diaDriftAngle->setSuffix(QCoreApplication::translate("uiSAR", " \302\260", nullptr));
        diaTimexml->setSuffix(QCoreApplication::translate("uiSAR", " \321\201", nullptr));
        diaRangexml->setSuffix(QCoreApplication::translate("uiSAR", " \320\272\320\274", nullptr));
        label_19->setText(QCoreApplication::translate("uiSAR", "\320\237\320\276\321\201\321\202\320\260\320\262\321\211\320\270\320\272 \320\272\320\260\321\200\321\202: ", nullptr));
#if QT_CONFIG(tooltip)
        providerGoogle->setToolTip(QCoreApplication::translate("uiSAR", "\320\240\320\265\320\272\320\276\320\274\320\265\320\275\320\264\321\203\320\265\321\202\321\201\321\217", nullptr));
#endif // QT_CONFIG(tooltip)
        providerGoogle->setText(QCoreApplication::translate("uiSAR", "Google", nullptr));
        providerESRI->setText(QCoreApplication::translate("uiSAR", "Mapbox", nullptr));
#if QT_CONFIG(tooltip)
        providerOSM->setToolTip(QCoreApplication::translate("uiSAR", "\320\235\320\265 \321\200\320\265\320\272\320\276\320\274\320\265\320\275\320\264\321\203\320\265\321\202\321\201\321\217: \320\276\321\202\321\201\321\203\321\202\321\201\321\202\320\262\321\203\321\216\321\202 \321\201\320\277\321\203\321\202\320\275\320\270\320\272\320\276\320\262\321\213\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
#endif // QT_CONFIG(tooltip)
        providerOSM->setText(QCoreApplication::translate("uiSAR", "OpenStreet", nullptr));
        predictRangexml->setSuffix(QCoreApplication::translate("uiSAR", " \320\272\320\274", nullptr));
        label_13->setText(QCoreApplication::translate("uiSAR", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\276\320\261\320\275\320\276\320\262\320\273\320\265\320\275\320\270\321\217 \320\264\320\260\320\275\320\275\321\213\321\205 \321\202\320\265\320\273\320\265\320\274\320\265\321\202\321\200\320\270\320\270:", nullptr));
        selectFolderButton->setText(QCoreApplication::translate("uiSAR", "\320\243\320\272\320\260\320\267\320\260\321\202\321\214", nullptr));
        UDPIPxml->setText(QCoreApplication::translate("uiSAR", "48.78.136.210", nullptr));
        label_4->setText(QCoreApplication::translate("uiSAR", "\320\220\320\264\321\200\320\265\321\201 TCP \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216:", nullptr));
        UDPPortxml->setText(QCoreApplication::translate("uiSAR", "9999", nullptr));
        saveSettings->setText(QCoreApplication::translate("uiSAR", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        discardSettings->setText(QCoreApplication::translate("uiSAR", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(cfg_tab), QString());
        label_6->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213 \321\203\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217 </span><span style=\" font-weight:600; color:#aaaaff;\">UDP</span></p></body></html>", nullptr));
        UDPConsole->setTitle(QCoreApplication::translate("uiSAR", "\320\232\320\276\320\275\321\201\320\276\320\273\321\214 UDP", nullptr));
        pushButton_2->setText(QCoreApplication::translate("uiSAR", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\277\321\200\320\270\320\265\320\274 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        pushButton->setText(QCoreApplication::translate("uiSAR", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203 \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216", nullptr));
        udpStopButton->setText(QString());
        udpSendButton->setText(QString());
        udpDisp->setMarkdown(QString());
        udpDisp->setHtml(QCoreApplication::translate("uiSAR", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        udpDisp->setPlaceholderText(QCoreApplication::translate("uiSAR", "Waiting for connection...  type \"connect ip:port\" for udp connection or connect via default UDP IP  type \"help\" for additional command info  ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(link_tab), QString());
        DecodeJPG->setText(QString());
        infoLabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"center\"><img src=\":/img/ui.png\"/></p><p>\320\222\320\265\321\200\321\201\320\270\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213: <span style=\" font-weight:600; font-style:italic; color:#aa4444;\">alpha </span><span style=\" font-weight:600; font-style:italic; color:#c77777;\">0.1.0</span></p><p>\320\241\320\276\320\261\321\200\320\260\320\275\320\276 <span style=\" font-weight:600;\">06.11.2021</span></p><p><a href=\"https://github.com/whs31/qtsar_ui\"><span style=\" text-decoration: underline; color:#395f78;\">github.com/qtsar_ui</span></a></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(info_tab), QString());
        docker->setWindowTitle(QCoreApplication::translate("uiSAR", "\320\237\320\260\320\275\320\265\320\273\321\214 \320\270\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\276\320\262", nullptr));
        gpsPanClone->setText(QString());
        rulerButton->setText(QString());
        changeMapMode->setText(QCoreApplication::translate("uiSAR", "\320\241\320\277\321\203\321\202\320\275\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class uiSAR: public Ui_uiSAR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UISAR_H
