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

#include <QSettings>

#include "remote/remoteBase.h"
#include "console/console.h"

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
    QSettings *settings;
    static uiSAR * getMainWinPtr();
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
public slots:
    void qmlDialogSlot(float markerLat, float markerLon);
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
    void on_selectFolderButton_clicked();

    void on_nav_displayroute_stateChanged(int arg1);
    void on_clearTrack_clicked();
    void ReadTelemetry(QByteArray data);
    void ReadExec(QByteArray data);

    void on_changeMapMode_toggled(bool checked);
    void on_gpsPanClone_clicked();

    void on_t_up_clicked();
    void on_t_down_clicked();
    void on_t_left_clicked();
    void on_t_right_clicked();
    void on_t_xSpin_valueChanged(double arg1);
    void on_t_ySpin_valueChanged(double arg1);
    void on_t_sSpin_valueChanged(double arg1);
    void on_t_scale_valueChanged(int value);

    void on_UDPIPxml_textChanged(const QString &arg1);

    void on_UDPPortxml_textChanged(const QString &arg1);

    void on_TCPIPxml_textChanged(const QString &arg1);

    void on_TCPPortxml_textChanged(const QString &arg1);

    void on_refreshtelemetryxml_valueChanged(double arg1);

    void on_predictRangexml_valueChanged(double arg1);

    void on_diaTimexml_valueChanged(double arg1);

    void on_diaRangexml_valueChanged(double arg1);

private:
    static uiSAR * pMainWindow;

    int totalJPGDetected;
    double spinxArg0 = 0;
    double spinyArg0 = 0;
    double spinrArg0 = 0;
    double spinsArg0 = 0;

    bool followPlane = false;

    Ui::uiSAR *ui; 
    QTimer *timer;

    Remote *Telemery;
    TelemetryData_t *TelemetryData;

    QStringList imageList;
    int fileCounter = 0;

    void updateTelemetry();
    //TelemetryData_t parseTelemetry(const QByteArray & src);
    void initUI();
    void update_jpgblocklabels_from_field(JPGFields _field);
    bool eventFilter(QObject *watched, QEvent *event);

};

#endif // UISAR_H
