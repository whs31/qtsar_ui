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

#include "remote/remoteBase.h"

#define JPEG_HEADER_SIZE 20

QT_BEGIN_NAMESPACE
namespace Ui { class uiSAR; }
QT_END_NAMESPACE

class uiSAR : public QMainWindow
{
    Q_OBJECT

public:
    uiSAR(QWidget *parent = nullptr);
    ~uiSAR();
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
    JPGFields readField();

signals:
    //void toQMLpanButton(float latitude, float longitude, float dx, float dy, float x0, float y0, float angle, QString filename);
private slots:
    //JPG slots
    void on_DecodeJPG_clicked();
    void on_panButton_clicked();
    void on_showButton_clicked();
    void on_opacitySlider_sliderMoved(int position);
    void on_showCoordsBox_stateChanged(int arg1);

    //Network slots
    void on_udpSendButton_clicked();
    void onTimer();

    void on_placeMarkerButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_udpStopButton_clicked();
    void on_panGPS_clicked();
    void on_nav_follow_stateChanged(int arg1);
    void on_jpg_gright_clicked();
    void on_jpg_gleft_clicked();
    void on_detect_refresh_clicked();
    void on_selectFolderButton_clicked();

    void on_nav_displayroute_stateChanged(int arg1);

    void on_clearTrack_clicked();

    void ReadTelemetry(QByteArray data);

private:

    QString jpg_path;
    int fileCounter;
    int totalJPGDetected;

    bool followPlane = false;
    bool allowRefresh = false;

    Ui::uiSAR *ui; 
    QTimer *timer;

    Remote *Telemery;
    TelemetryData_t *TelemetryData;

    void updateTelemetry();
    void initUI();
    void update_jpgblocklabels_from_field(JPGFields _field);
    bool eventFilter(QObject *watched, QEvent *event);

};

#endif // UISAR_H
