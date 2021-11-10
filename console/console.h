#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QFont>
#include <QFontDatabase>
#include <QFontMetrics>

extern "C"{
#include "fvemu.h"
}

class Console : public QTextEdit
{
    Q_OBJECT
public:

    int fontWidth;
    int fontHeight;
    int consoleWidth;
    int consoleHeight;

    explicit Console(QWidget *parent = nullptr, int w = 80, int h = 24);
    int write(QByteArray data);
    void flush();
    void reset();
    bool escClosed(QByteArray data);

private:

    QFont setFont(QString name, int size);

    struct emuState *s;
    char *rawbuf;
    bool waitForClose = false;
    //QByteArray tmp;

private slots:
    void resizeEvent(QResizeEvent *event);

signals:

};

#endif // CONSOLE_H
