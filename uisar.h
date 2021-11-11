#ifndef UISAR_H
#define UISAR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QtPositioning/QGeoCoordinate>

#include <QString>
#include <QImageReader>

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QNetworkDatagram>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QSslSocket>
#include <QtMath>
#include <QtEndian>

#include <QDirIterator>
#include <QDir>
#include <QFileSystemModel>

#include "remote/remoteBase.h"
#include "console/console.h"
#include "filesystem/checkablemodel.h"
#include "image-processing/imageprocessing.h"
//#include "config/config.h"
#include "config/confighandler.h"

#define JPEG_HEADER_SIZE 20

class ImageProcessing;
class ConfigHandler;

QT_BEGIN_NAMESPACE
namespace Ui { class uiSAR; }
QT_END_NAMESPACE

class uiSAR : public QMainWindow
{
    Q_OBJECT

public:
    uiSAR(QWidget *parent = nullptr);
    ~uiSAR();
    static uiSAR * getMainWinPtr();
    friend class ImageProcessing;
    friend class ConfigHandler;

    struct JPGFields {
        double latitude;
        double longitude;
        float dx;
        float dy;
        float x0;
        float y0;
        float angle;
        QString filename;
    };

    struct TelemetryData_t {
        double lat;
        double lon;
        float speed;
        float ele;
    };


    JPGFields decode_jpgs(QString path);
    JPGFields readField();          //эту функцию надо убрать (в целом нужно переосмыслить хранение метаданных в программе)

signals:
    //void toQMLpanButton(float latitude, float longitude, float dx, float dy, float x0, float y0, float angle, QString filename);
public slots:
    void qmlDialogSlot(float markerLat, float markerLon);
private slots:
    //image processing slots
    void on_panButton_clicked();
    void on_opacitySlider_sliderMoved(int position);
    void on_jpg_gright_clicked();
    void on_jpg_gleft_clicked();

    //map tools slots
    void on_showCoordsBox_stateChanged(int arg1);
    void on_placeMarkerButton_clicked();
    void on_nav_displayroute_stateChanged(int arg1);
    void on_clearTrack_clicked();
    void on_panGPS_clicked();
    void on_nav_follow_stateChanged(int arg1);

    //legacy console slots
    void on_udpSendButton_clicked();
    void onTimer();
    void on_pushButton_clicked();       //connect to default udp server
    void on_pushButton_2_clicked();     //start data receiving
    void on_udpStopButton_clicked();

    //config slots
    void on_selectFolderButton_clicked();
    void on_saveSettings_clicked();
    void on_discardSettings_clicked();

    //main console slots
    void ReadTelemetry(QByteArray data);
    void ReadExec(QByteArray data);

    //top toolpanel slots
    void on_changeMapMode_toggled(bool checked);
    void on_gpsPanClone_clicked();
    void on_rulerButton_clicked();

    //image transform slots
    void on_t_up_clicked();
    void on_t_down_clicked();
    void on_t_left_clicked();
    void on_t_right_clicked();
    void on_t_xSpin_valueChanged(double arg1);
    void on_t_ySpin_valueChanged(double arg1);
    void on_t_sSpin_valueChanged(double arg1);
    void on_t_scale_valueChanged(int value);
    void on_t_rSpin_valueChanged(double arg1);
    void on_t_rotation_valueChanged(int value);


private:
    static uiSAR * pMainWindow;

    double spinxArg0 = 0;
    double spinyArg0 = 0;
    double spinrArg0 = 0;
    double spinsArg0 = 0;

    bool followPlane = false;

    Ui::uiSAR *ui; 
    QTimer *timer;
    Remote *Telemery;
    TelemetryData_t *TelemetryData;
    //Config *config;
    ConfigHandler *configHandler;
    ImageProcessing *imageProcessing;

    QStringList imageList;
    int fileCounter = 0;

    void updateTelemetry();
    void initUI();
    void showAllImages();

    void update_jpgblocklabels_from_field(JPGFields _field);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // UISAR_H
