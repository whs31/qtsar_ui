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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uiSAR
{
public:
    QAction *findFolderJPG;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QQuickWidget *osmMap;
    QTabWidget *tabWidget;
    QWidget *map_tab;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_5;
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
    QFrame *line;
    QHBoxLayout *markerLayout;
    QLabel *label;
    QPushButton *placeMarkerButton;
    QPushButton *saveMarkerButton;
    QPushButton *loadMarkerButton;
    QGridLayout *gridLayout_2;
    QCheckBox *nav_displayroute;
    QCheckBox *nav_displaytriangle;
    QCheckBox *nav_follow;
    QPushButton *panGPS;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_9;
    QCheckBox *showCoordsBox;
    QPushButton *clearTrack;
    QSpacerItem *verticalSpacer_2;
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
    QWidget *tcp_tab;
    QWidget *img_tab;
    QGridLayout *gridLayout_7;
    QFrame *line_3;
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
    QLabel *label_7;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *opacityLayout;
    QLabel *opacityLabel;
    QSlider *opacitySlider;
    QSpacerItem *verticalSpacer_5;
    QGridLayout *jpgButtonsLayout;
    QPushButton *showButton;
    QPushButton *panButton;
    QHBoxLayout *horizontalLayout;
    QToolButton *jpg_gleft;
    QLabel *jpgtls_filenamelabel;
    QLabel *jpgtls_filenamedisp;
    QToolButton *jpg_gright;
    QHBoxLayout *detectLayout;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *detect_refresh;
    QLabel *detect_detectedlabel;
    QLabel *detect_detecteddisp;
    QPushButton *pushButton_3;
    QWidget *cfg_tab;
    QGridLayout *gridLayout_6;
    QLabel *label_3;
    QPushButton *selectFolderButton;
    QLabel *label_2;
    QLineEdit *UDPPortxml;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *UDPIPxml;
    QLabel *label_4;
    QLineEdit *TCPPortxml;
    QLineEdit *TCPIPxml;
    QWidget *info_tab;
    QGridLayout *gridLayout_8;
    QLabel *infoLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *DecodeJPG;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *uiSAR)
    {
        if (uiSAR->objectName().isEmpty())
            uiSAR->setObjectName(QString::fromUtf8("uiSAR"));
        uiSAR->setWindowModality(Qt::ApplicationModal);
        uiSAR->resize(1300, 735);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(uiSAR->sizePolicy().hasHeightForWidth());
        uiSAR->setSizePolicy(sizePolicy);
        uiSAR->setMinimumSize(QSize(1300, 650));
        uiSAR->setMaximumSize(QSize(16777215, 16777215));
        uiSAR->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/ui.png"), QSize(), QIcon::Normal, QIcon::Off);
        uiSAR->setWindowIcon(icon);
        uiSAR->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        uiSAR->setDocumentMode(false);
        uiSAR->setTabShape(QTabWidget::Rounded);
        uiSAR->setUnifiedTitleAndToolBarOnMac(false);
        findFolderJPG = new QAction(uiSAR);
        findFolderJPG->setObjectName(QString::fromUtf8("findFolderJPG"));
        findFolderJPG->setCheckable(false);
        findFolderJPG->setChecked(false);
        findFolderJPG->setEnabled(true);
        QFont font;
        findFolderJPG->setFont(font);
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
        osmMap->setCursor(QCursor(Qt::CrossCursor));
        osmMap->setMouseTracking(true);
        osmMap->setResizeMode(QQuickWidget::SizeRootObjectToView);

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
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        tabWidget->setFont(font1);
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


        gridLayout_5->addWidget(NAVSAR, 3, 0, 1, 3);

        line = new QFrame(map_tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 1, 0, 1, 3);

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


        gridLayout_5->addLayout(markerLayout, 6, 0, 1, 3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(4);
        nav_displayroute = new QCheckBox(map_tab);
        nav_displayroute->setObjectName(QString::fromUtf8("nav_displayroute"));
        nav_displayroute->setEnabled(true);
        nav_displayroute->setChecked(true);

        gridLayout_2->addWidget(nav_displayroute, 1, 1, 1, 1);

        nav_displaytriangle = new QCheckBox(map_tab);
        nav_displaytriangle->setObjectName(QString::fromUtf8("nav_displaytriangle"));
        nav_displaytriangle->setEnabled(false);
        nav_displaytriangle->setChecked(true);

        gridLayout_2->addWidget(nav_displaytriangle, 3, 1, 1, 1);

        nav_follow = new QCheckBox(map_tab);
        nav_follow->setObjectName(QString::fromUtf8("nav_follow"));

        gridLayout_2->addWidget(nav_follow, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 4, 1, 1, 1);

        panGPS = new QPushButton(map_tab);
        panGPS->setObjectName(QString::fromUtf8("panGPS"));
        sizePolicy6.setHeightForWidth(panGPS->sizePolicy().hasHeightForWidth());
        panGPS->setSizePolicy(sizePolicy6);
        panGPS->setMinimumSize(QSize(38, 38));
        panGPS->setMaximumSize(QSize(38, 38));
        panGPS->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/nav_pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        panGPS->setIcon(icon4);
        panGPS->setIconSize(QSize(30, 30));

        gridLayout_5->addWidget(panGPS, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 7, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_9 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_9);

        showCoordsBox = new QCheckBox(map_tab);
        showCoordsBox->setObjectName(QString::fromUtf8("showCoordsBox"));
        sizePolicy.setHeightForWidth(showCoordsBox->sizePolicy().hasHeightForWidth());
        showCoordsBox->setSizePolicy(sizePolicy);
        showCoordsBox->setMaximumSize(QSize(16777215, 25));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/take_coords.png"), QSize(), QIcon::Normal, QIcon::Off);
        showCoordsBox->setIcon(icon5);
        showCoordsBox->setChecked(true);

        verticalLayout->addWidget(showCoordsBox);

        clearTrack = new QPushButton(map_tab);
        clearTrack->setObjectName(QString::fromUtf8("clearTrack"));

        verticalLayout->addWidget(clearTrack);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout_5->addLayout(verticalLayout, 4, 2, 1, 1);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/tabIcons/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(map_tab, icon6, QString());
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
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(udpStopButton->sizePolicy().hasHeightForWidth());
        udpStopButton->setSizePolicy(sizePolicy7);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        udpStopButton->setIcon(icon7);
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
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right@2x.png"), QSize(), QIcon::Normal, QIcon::Off);
        udpSendButton->setIcon(icon8);
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

        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/tabIcons/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(link_tab, icon9, QString());
        tcp_tab = new QWidget();
        tcp_tab->setObjectName(QString::fromUtf8("tcp_tab"));
        tabWidget->addTab(tcp_tab, icon9, QString());
        img_tab = new QWidget();
        img_tab->setObjectName(QString::fromUtf8("img_tab"));
        gridLayout_7 = new QGridLayout(img_tab);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        line_3 = new QFrame(img_tab);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_3, 1, 0, 1, 1);

        groupBox = new QGroupBox(img_tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        jpgtls_latlabel = new QLabel(groupBox);
        jpgtls_latlabel->setObjectName(QString::fromUtf8("jpgtls_latlabel"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(jpgtls_latlabel->sizePolicy().hasHeightForWidth());
        jpgtls_latlabel->setSizePolicy(sizePolicy8);
        jpgtls_latlabel->setCursor(QCursor(Qt::IBeamCursor));
        jpgtls_latlabel->setTextFormat(Qt::AutoText);
        jpgtls_latlabel->setScaledContents(false);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, jpgtls_latlabel);

        jpgtls_latdisp = new QLabel(groupBox);
        jpgtls_latdisp->setObjectName(QString::fromUtf8("jpgtls_latdisp"));
        sizePolicy8.setHeightForWidth(jpgtls_latdisp->sizePolicy().hasHeightForWidth());
        jpgtls_latdisp->setSizePolicy(sizePolicy8);
        jpgtls_latdisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, jpgtls_latdisp);

        jpgtls_lonlabel = new QLabel(groupBox);
        jpgtls_lonlabel->setObjectName(QString::fromUtf8("jpgtls_lonlabel"));
        sizePolicy8.setHeightForWidth(jpgtls_lonlabel->sizePolicy().hasHeightForWidth());
        jpgtls_lonlabel->setSizePolicy(sizePolicy8);
        jpgtls_lonlabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, jpgtls_lonlabel);

        jpgtls_londisp = new QLabel(groupBox);
        jpgtls_londisp->setObjectName(QString::fromUtf8("jpgtls_londisp"));
        sizePolicy8.setHeightForWidth(jpgtls_londisp->sizePolicy().hasHeightForWidth());
        jpgtls_londisp->setSizePolicy(sizePolicy8);
        jpgtls_londisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, jpgtls_londisp);

        jpgtls_dxlabel = new QLabel(groupBox);
        jpgtls_dxlabel->setObjectName(QString::fromUtf8("jpgtls_dxlabel"));
        sizePolicy8.setHeightForWidth(jpgtls_dxlabel->sizePolicy().hasHeightForWidth());
        jpgtls_dxlabel->setSizePolicy(sizePolicy8);
        jpgtls_dxlabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, jpgtls_dxlabel);

        jpgtls_dxdisp = new QLabel(groupBox);
        jpgtls_dxdisp->setObjectName(QString::fromUtf8("jpgtls_dxdisp"));
        sizePolicy8.setHeightForWidth(jpgtls_dxdisp->sizePolicy().hasHeightForWidth());
        jpgtls_dxdisp->setSizePolicy(sizePolicy8);
        jpgtls_dxdisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, jpgtls_dxdisp);

        jpgtls_dylabel = new QLabel(groupBox);
        jpgtls_dylabel->setObjectName(QString::fromUtf8("jpgtls_dylabel"));
        sizePolicy8.setHeightForWidth(jpgtls_dylabel->sizePolicy().hasHeightForWidth());
        jpgtls_dylabel->setSizePolicy(sizePolicy8);
        jpgtls_dylabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, jpgtls_dylabel);

        jpgtls_dydisp = new QLabel(groupBox);
        jpgtls_dydisp->setObjectName(QString::fromUtf8("jpgtls_dydisp"));
        sizePolicy8.setHeightForWidth(jpgtls_dydisp->sizePolicy().hasHeightForWidth());
        jpgtls_dydisp->setSizePolicy(sizePolicy8);
        jpgtls_dydisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, jpgtls_dydisp);

        jpgtls_x0label = new QLabel(groupBox);
        jpgtls_x0label->setObjectName(QString::fromUtf8("jpgtls_x0label"));
        sizePolicy8.setHeightForWidth(jpgtls_x0label->sizePolicy().hasHeightForWidth());
        jpgtls_x0label->setSizePolicy(sizePolicy8);
        jpgtls_x0label->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, jpgtls_x0label);

        jpgtls_x0disp = new QLabel(groupBox);
        jpgtls_x0disp->setObjectName(QString::fromUtf8("jpgtls_x0disp"));
        sizePolicy8.setHeightForWidth(jpgtls_x0disp->sizePolicy().hasHeightForWidth());
        jpgtls_x0disp->setSizePolicy(sizePolicy8);
        jpgtls_x0disp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, jpgtls_x0disp);

        jpgtls_y0label = new QLabel(groupBox);
        jpgtls_y0label->setObjectName(QString::fromUtf8("jpgtls_y0label"));
        sizePolicy8.setHeightForWidth(jpgtls_y0label->sizePolicy().hasHeightForWidth());
        jpgtls_y0label->setSizePolicy(sizePolicy8);
        jpgtls_y0label->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, jpgtls_y0label);

        jpgtls_y0disp = new QLabel(groupBox);
        jpgtls_y0disp->setObjectName(QString::fromUtf8("jpgtls_y0disp"));
        sizePolicy8.setHeightForWidth(jpgtls_y0disp->sizePolicy().hasHeightForWidth());
        jpgtls_y0disp->setSizePolicy(sizePolicy8);
        jpgtls_y0disp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, jpgtls_y0disp);

        jpgtls_anglabel = new QLabel(groupBox);
        jpgtls_anglabel->setObjectName(QString::fromUtf8("jpgtls_anglabel"));
        sizePolicy8.setHeightForWidth(jpgtls_anglabel->sizePolicy().hasHeightForWidth());
        jpgtls_anglabel->setSizePolicy(sizePolicy8);
        jpgtls_anglabel->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, jpgtls_anglabel);

        jpgtls_angdisp = new QLabel(groupBox);
        jpgtls_angdisp->setObjectName(QString::fromUtf8("jpgtls_angdisp"));
        sizePolicy8.setHeightForWidth(jpgtls_angdisp->sizePolicy().hasHeightForWidth());
        jpgtls_angdisp->setSizePolicy(sizePolicy8);
        jpgtls_angdisp->setCursor(QCursor(Qt::IBeamCursor));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, jpgtls_angdisp);


        gridLayout_7->addWidget(groupBox, 11, 0, 1, 1);

        label_7 = new QLabel(img_tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_7->addWidget(label_7, 0, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_7->addItem(verticalSpacer_8, 2, 0, 1, 1);

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
        sizePolicy5.setHeightForWidth(opacitySlider->sizePolicy().hasHeightForWidth());
        opacitySlider->setSizePolicy(sizePolicy5);
        opacitySlider->setCursor(QCursor(Qt::SizeHorCursor));
        opacitySlider->setValue(99);
        opacitySlider->setOrientation(Qt::Horizontal);
        opacitySlider->setInvertedAppearance(true);

        opacityLayout->addWidget(opacitySlider);


        gridLayout_7->addLayout(opacityLayout, 4, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_5, 13, 0, 1, 1);

        jpgButtonsLayout = new QGridLayout();
        jpgButtonsLayout->setObjectName(QString::fromUtf8("jpgButtonsLayout"));
        jpgButtonsLayout->setSizeConstraint(QLayout::SetMinimumSize);
        jpgButtonsLayout->setHorizontalSpacing(6);
        jpgButtonsLayout->setVerticalSpacing(1);
        showButton = new QPushButton(img_tab);
        showButton->setObjectName(QString::fromUtf8("showButton"));
        sizePolicy8.setHeightForWidth(showButton->sizePolicy().hasHeightForWidth());
        showButton->setSizePolicy(sizePolicy8);
        showButton->setToolTipDuration(1);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/img/toggle_overlay.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon10.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_toggledispico_A.png"), QSize(), QIcon::Active, QIcon::Off);
        icon10.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_toggledispico_A.png"), QSize(), QIcon::Selected, QIcon::Off);
        showButton->setIcon(icon10);
        showButton->setIconSize(QSize(16, 16));

        jpgButtonsLayout->addWidget(showButton, 0, 0, 1, 1);

        panButton = new QPushButton(img_tab);
        panButton->setObjectName(QString::fromUtf8("panButton"));
        sizePolicy8.setHeightForWidth(panButton->sizePolicy().hasHeightForWidth());
        panButton->setSizePolicy(sizePolicy8);
        panButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/img/jpg_pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon11.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_centeronjpgico_A.png"), QSize(), QIcon::Active, QIcon::Off);
        icon11.addFile(QString::fromUtf8(":/Desktop/Portable Python/sar_ctrl/img/jpgtls_centeronjpgico_A.png"), QSize(), QIcon::Selected, QIcon::Off);
        panButton->setIcon(icon11);
        panButton->setIconSize(QSize(16, 16));
        panButton->setCheckable(false);
        panButton->setChecked(false);

        jpgButtonsLayout->addWidget(panButton, 0, 1, 1, 1);


        gridLayout_7->addLayout(jpgButtonsLayout, 5, 0, 1, 1);

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
        sizePolicy8.setHeightForWidth(jpgtls_filenamelabel->sizePolicy().hasHeightForWidth());
        jpgtls_filenamelabel->setSizePolicy(sizePolicy8);
        jpgtls_filenamelabel->setCursor(QCursor(Qt::IBeamCursor));
        jpgtls_filenamelabel->setTextFormat(Qt::AutoText);

        horizontalLayout->addWidget(jpgtls_filenamelabel);

        jpgtls_filenamedisp = new QLabel(img_tab);
        jpgtls_filenamedisp->setObjectName(QString::fromUtf8("jpgtls_filenamedisp"));
        sizePolicy8.setHeightForWidth(jpgtls_filenamedisp->sizePolicy().hasHeightForWidth());
        jpgtls_filenamedisp->setSizePolicy(sizePolicy8);
        jpgtls_filenamedisp->setCursor(QCursor(Qt::IBeamCursor));

        horizontalLayout->addWidget(jpgtls_filenamedisp);

        jpg_gright = new QToolButton(img_tab);
        jpg_gright->setObjectName(QString::fromUtf8("jpg_gright"));
        jpg_gright->setEnabled(false);
        sizePolicy6.setHeightForWidth(jpg_gright->sizePolicy().hasHeightForWidth());
        jpg_gright->setSizePolicy(sizePolicy6);
        jpg_gright->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon12.addFile(QString::fromUtf8(":/qss_icons/dark/rc/arrow_right_disabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        jpg_gright->setIcon(icon12);
        jpg_gright->setIconSize(QSize(10, 10));
        jpg_gright->setCheckable(false);
        jpg_gright->setChecked(false);
        jpg_gright->setAutoRaise(true);
        jpg_gright->setArrowType(Qt::RightArrow);

        horizontalLayout->addWidget(jpg_gright);


        gridLayout_7->addLayout(horizontalLayout, 7, 0, 1, 1);

        detectLayout = new QHBoxLayout();
        detectLayout->setSpacing(3);
        detectLayout->setObjectName(QString::fromUtf8("detectLayout"));
        detectLayout->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        detectLayout->addItem(horizontalSpacer_2);

        detect_refresh = new QToolButton(img_tab);
        detect_refresh->setObjectName(QString::fromUtf8("detect_refresh"));
        detect_refresh->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/img/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        detect_refresh->setIcon(icon13);
        detect_refresh->setIconSize(QSize(16, 16));
        detect_refresh->setAutoRepeat(false);
        detect_refresh->setAutoRepeatDelay(10);
        detect_refresh->setAutoRepeatInterval(10);
        detect_refresh->setPopupMode(QToolButton::InstantPopup);
        detect_refresh->setAutoRaise(true);

        detectLayout->addWidget(detect_refresh);

        detect_detectedlabel = new QLabel(img_tab);
        detect_detectedlabel->setObjectName(QString::fromUtf8("detect_detectedlabel"));
        sizePolicy.setHeightForWidth(detect_detectedlabel->sizePolicy().hasHeightForWidth());
        detect_detectedlabel->setSizePolicy(sizePolicy);
        detect_detectedlabel->setScaledContents(true);
        detect_detectedlabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        detectLayout->addWidget(detect_detectedlabel);

        detect_detecteddisp = new QLabel(img_tab);
        detect_detecteddisp->setObjectName(QString::fromUtf8("detect_detecteddisp"));
        detect_detecteddisp->setScaledContents(true);
        detect_detecteddisp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        detectLayout->addWidget(detect_detecteddisp);


        gridLayout_7->addLayout(detectLayout, 3, 0, 1, 1);

        pushButton_3 = new QPushButton(img_tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setEnabled(false);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/img/toggle_overlay.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon14);

        gridLayout_7->addWidget(pushButton_3, 6, 0, 1, 1);

        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/tabIcons/jpg.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(img_tab, icon15, QString());
        cfg_tab = new QWidget();
        cfg_tab->setObjectName(QString::fromUtf8("cfg_tab"));
        gridLayout_6 = new QGridLayout(cfg_tab);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_3 = new QLabel(cfg_tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);

        gridLayout_6->addWidget(label_3, 1, 0, 1, 1);

        selectFolderButton = new QPushButton(cfg_tab);
        selectFolderButton->setObjectName(QString::fromUtf8("selectFolderButton"));

        gridLayout_6->addWidget(selectFolderButton, 0, 2, 1, 2);

        label_2 = new QLabel(cfg_tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        gridLayout_6->addWidget(label_2, 0, 0, 1, 1);

        UDPPortxml = new QLineEdit(cfg_tab);
        UDPPortxml->setObjectName(QString::fromUtf8("UDPPortxml"));
        sizePolicy6.setHeightForWidth(UDPPortxml->sizePolicy().hasHeightForWidth());
        UDPPortxml->setSizePolicy(sizePolicy6);
        UDPPortxml->setMaximumSize(QSize(50, 16777215));
        UDPPortxml->setMaxLength(5);
        UDPPortxml->setFrame(true);
        UDPPortxml->setEchoMode(QLineEdit::Normal);

        gridLayout_6->addWidget(UDPPortxml, 1, 3, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_4, 3, 0, 1, 1);

        UDPIPxml = new QLineEdit(cfg_tab);
        UDPIPxml->setObjectName(QString::fromUtf8("UDPIPxml"));
        UDPIPxml->setMaxLength(15);
        UDPIPxml->setClearButtonEnabled(false);

        gridLayout_6->addWidget(UDPIPxml, 1, 1, 1, 2);

        label_4 = new QLabel(cfg_tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_6->addWidget(label_4, 2, 0, 1, 1);

        TCPPortxml = new QLineEdit(cfg_tab);
        TCPPortxml->setObjectName(QString::fromUtf8("TCPPortxml"));
        TCPPortxml->setMaximumSize(QSize(50, 16777215));
        TCPPortxml->setMaxLength(5);

        gridLayout_6->addWidget(TCPPortxml, 2, 3, 1, 1);

        TCPIPxml = new QLineEdit(cfg_tab);
        TCPIPxml->setObjectName(QString::fromUtf8("TCPIPxml"));
        TCPIPxml->setInputMethodHints(Qt::ImhNone);
        TCPIPxml->setMaxLength(15);

        gridLayout_6->addWidget(TCPIPxml, 2, 1, 1, 2);

        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/tabIcons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(cfg_tab, icon16, QString());
        info_tab = new QWidget();
        info_tab->setObjectName(QString::fromUtf8("info_tab"));
        gridLayout_8 = new QGridLayout(info_tab);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        infoLabel = new QLabel(info_tab);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));

        gridLayout_8->addWidget(infoLabel, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 2, 0, 1, 1);

        DecodeJPG = new QPushButton(info_tab);
        DecodeJPG->setObjectName(QString::fromUtf8("DecodeJPG"));
        DecodeJPG->setEnabled(true);
        sizePolicy6.setHeightForWidth(DecodeJPG->sizePolicy().hasHeightForWidth());
        DecodeJPG->setSizePolicy(sizePolicy6);
        DecodeJPG->setMaximumSize(QSize(1, 1));
        DecodeJPG->setAutoDefault(true);
        DecodeJPG->setFlat(true);

        gridLayout_8->addWidget(DecodeJPG, 1, 1, 1, 1);

        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/tabIcons/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(info_tab, icon17, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        uiSAR->setCentralWidget(centralwidget);
        menubar = new QMenuBar(uiSAR);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1300, 20));
        uiSAR->setMenuBar(menubar);
        statusBar = new QStatusBar(uiSAR);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        uiSAR->setStatusBar(statusBar);

        retranslateUi(uiSAR);

        tabWidget->setCurrentIndex(3);
        DecodeJPG->setDefault(false);


        QMetaObject::connectSlotsByName(uiSAR);
    } // setupUi

    void retranslateUi(QMainWindow *uiSAR)
    {
        uiSAR->setWindowTitle(QCoreApplication::translate("uiSAR", "\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\270\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201 \320\240\320\233\320\241", nullptr));
        findFolderJPG->setText(QCoreApplication::translate("uiSAR", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\320\277\320\272\321\203 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\271", nullptr));
#if QT_CONFIG(tooltip)
        findFolderJPG->setToolTip(QCoreApplication::translate("uiSAR", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\277\320\260\320\277\320\272\321\203 \321\201 \320\262\321\213\321\205\320\276\320\264\320\275\321\213\320\274\320\270 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217\320\274\320\270 \320\240\320\233\320\241.", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\277\320\260\320\277\320\272\321\203 \321\201 \320\262\321\213\321\205\320\276\320\264\320\275\321\213\320\274\320\270 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217\320\274\320\270 \320\240\320\233\320\241."));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        findFolderJPG->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        findFolderJPG->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        label_5->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213 \320\272\320\260\321\200\321\202\321\213</span></p></body></html>", nullptr));
        NAVSAR->setTitle(QCoreApplication::translate("uiSAR", "\320\235\320\260\320\262\320\270\320\263\320\260\321\206\320\270\320\276\320\275\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        nav_latlabel->setText(QCoreApplication::translate("uiSAR", "\320\250\320\270\321\200\320\276\321\202\320\260", nullptr));
        nav_latdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        nav_lonlabel->setText(QCoreApplication::translate("uiSAR", "\320\224\320\276\320\273\320\263\320\276\321\202\320\260", nullptr));
        nav_londisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        nav_acclabel->setText(QCoreApplication::translate("uiSAR", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        nav_accdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        nav_altlabel->setText(QCoreApplication::translate("uiSAR", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        nav_altdisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("uiSAR", "\320\234\320\260\321\200\320\272\320\265\321\200\321\213 \320\275\320\260 \320\272\320\260\321\200\321\202\320\265", nullptr));
        placeMarkerButton->setText(QCoreApplication::translate("uiSAR", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\274\320\260\321\200\320\272\320\265\321\200", nullptr));
        saveMarkerButton->setText(QString());
        loadMarkerButton->setText(QString());
        nav_displayroute->setText(QCoreApplication::translate("uiSAR", "\320\242\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \320\277\320\276\320\273\320\265\321\202\320\260", nullptr));
        nav_displaytriangle->setText(QCoreApplication::translate("uiSAR", "\320\224\320\270\320\260\320\263\321\200\320\260\320\274\320\274\320\260 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\275\320\276\321\201\321\202\320\270", nullptr));
        nav_follow->setText(QCoreApplication::translate("uiSAR", "\320\241\320\273\320\265\320\264\320\270\321\202\321\214 \320\267\320\260 \321\201\320\260\320\274\320\276\320\273\320\265\321\202\320\276\320\274", nullptr));
        panGPS->setText(QString());
        showCoordsBox->setText(QCoreApplication::translate("uiSAR", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213 \320\272\321\203\321\200\321\201\320\276\321\200\320\260", nullptr));
        clearTrack->setText(QCoreApplication::translate("uiSAR", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\202\321\200\320\265\320\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(map_tab), QString());
        label_6->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213 \321\203\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217 </span><span style=\" font-weight:600; color:#aaaaff;\">UDP</span></p></body></html>", nullptr));
        UDPConsole->setTitle(QCoreApplication::translate("uiSAR", "\320\232\320\276\320\275\321\201\320\276\320\273\321\214 UDP", nullptr));
        pushButton_2->setText(QCoreApplication::translate("uiSAR", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\277\321\200\320\270\320\265\320\274 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        pushButton->setText(QCoreApplication::translate("uiSAR", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203 \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216", nullptr));
        udpStopButton->setText(QString());
        udpSendButton->setText(QString());
        //udpDisp->setMarkdown(QString());
        udpDisp->setHtml(QCoreApplication::translate("uiSAR", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        udpDisp->setPlaceholderText(QCoreApplication::translate("uiSAR", "Waiting for connection...  type \"connect ip:port\" for udp connection or connect via default UDP IP  type \"help\" for additional command info  ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(link_tab), QString());
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
        label_7->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p><span style=\" font-weight:600;\">\320\240\320\260\320\264\320\270\320\276\320\273\320\276\320\272\320\260\321\206\320\270\320\276\320\275\320\275\321\213\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217</span></p></body></html>", nullptr));
        opacityLabel->setText(QCoreApplication::translate("uiSAR", "\320\237\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214 \321\201\320\273\320\276\321\217 \320\240\320\233\320\230", nullptr));
#if QT_CONFIG(tooltip)
        showButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        showButton->setText(QCoreApplication::translate("uiSAR", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\240\320\233\320\230", nullptr));
        panButton->setText(QCoreApplication::translate("uiSAR", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\240\320\233\320\230 ", nullptr));
        jpg_gleft->setText(QString());
        jpgtls_filenamelabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p>\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \321\204\320\260\320\271\320\273:</p></body></html>", nullptr));
        jpgtls_filenamedisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"right\"><span style=\" font-weight:600;\">-----------</span></p></body></html>", nullptr));
        jpg_gright->setText(QString());
        detect_refresh->setText(QString());
        detect_detectedlabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p>\320\236\320\261\320\275\320\260\321\200\321\203\320\266\320\265\320\275\320\276 \320\240\320\233\320\230: </p></body></html>", nullptr));
        detect_detecteddisp->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p>0</p></body></html>", nullptr));
        pushButton_3->setText(QCoreApplication::translate("uiSAR", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\262\321\201\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(img_tab), QString());
        label_3->setText(QCoreApplication::translate("uiSAR", "\320\220\320\264\321\200\320\265\321\201 UDP \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216:", nullptr));
        selectFolderButton->setText(QCoreApplication::translate("uiSAR", "\320\243\320\272\320\260\320\267\320\260\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("uiSAR", "\320\232\320\260\321\202\320\260\320\273\320\276\320\263 \320\277\320\276\320\270\321\201\320\272\320\260 \321\200\320\260\320\264\320\270\320\276\320\273\320\276\320\272\320\260\321\206\320\270\320\276\320\275\320\275\321\213\321\205 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\271:", nullptr));
        UDPPortxml->setText(QCoreApplication::translate("uiSAR", "9999", nullptr));
        UDPIPxml->setText(QCoreApplication::translate("uiSAR", "48.78.136.210", nullptr));
        label_4->setText(QCoreApplication::translate("uiSAR", "\320\220\320\264\321\200\320\265\321\201 TCP \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(cfg_tab), QString());
        infoLabel->setText(QCoreApplication::translate("uiSAR", "<html><head/><body><p align=\"center\"><img src=\":/img/ui.png\"/></p><p>\320\222\320\265\321\200\321\201\320\270\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213: <span style=\" font-weight:600; font-style:italic; color:#8f8fff;\">inDev</span><span style=\" font-weight:600; font-style:italic; color:#bbb8ff;\">1102</span></p><p>\320\241\320\276\320\261\321\200\320\260\320\275\320\276 <span style=\" font-weight:600;\">02.11.2021</span></p><p><span style=\" color:#aaffff;\">github.com/whs31/qtsar_ui</span></p></body></html>", nullptr));
        DecodeJPG->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(info_tab), QString());
    } // retranslateUi

};

namespace Ui {
    class uiSAR: public Ui_uiSAR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UISAR_H
