#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
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

private:
    struct emuState *s;
    char *rawbuf;

signals:

};

#endif // CONSOLE_H
