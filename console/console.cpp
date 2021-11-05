#include "console.h"
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QFontMetrics>
#include <QDir>

Console::Console(QWidget *parent, int w, int h) : QTextEdit(parent), consoleWidth(w), consoleHeight(h)
{
    s = emu_core_init(h, w);

    rawbuf = (char*)malloc(w*h*2);

    int id = QFontDatabase::addApplicationFont("C:/Users/0/Documents/uiSAR/consoleUbuntuMono.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont fontConsole(family);
    fontConsole.setPointSize(13);
    this->setFont(fontConsole);
    QFontMetrics metrics = this->fontMetrics();

    this->setFrameStyle (QFrame::Panel | QFrame::Sunken);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("margin: 0px");
    setStyleSheet("padding:0;");


    fontWidth = metrics.width("0");
    fontHeight = metrics.height();
    int margin = document()->documentMargin() *2;

    this->resize(fontWidth *(w+1) + margin, h*fontHeight + margin);


}


int Console::write(QByteArray data){
    return emu_core_run(s, (const uint8_t*)data.data(), data.size() );
}

void Console::flush(){
    memset(rawbuf, 0, consoleWidth*consoleHeight*2);
    int k = 0;

    for(int i = 0; i < consoleHeight; i++){
        char *str = (char*)&s->rows[i]->chars[0];
        for(int j = 0; j < consoleWidth*2; j++){
            char cc = str[j];
            if(cc){
                rawbuf[k] =  cc;
                k++;
            }
        }
    }

    this->setText(rawbuf);
}
