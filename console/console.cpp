#include "console.h"
#include <QDebug>
#include <QDir>

Console::Console(QWidget *parent, int w, int h) : QTextEdit(parent), consoleWidth(w), consoleHeight(h)
{
    s = emu_core_init(h, w);

    rawbuf = (char*)malloc(w*h*2);


    QFont fontConsole = setFont("qrc:/console/UbuntuMono.ttf", 13);
    this->QWidget::setFont(fontConsole);
    QFontMetrics metrics = this->fontMetrics();

    //setFrameStyle (QFrame::Panel | QFrame::Sunken);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("margin: 0px");
    setStyleSheet("padding:0;");
    setReadOnly(true);
    setLineWrapMode(QTextEdit::FixedColumnWidth);
    setLineWrapColumnOrWidth(consoleWidth);


    fontWidth = metrics.width("0");
    fontHeight = metrics.height();


    //this->resize(fontWidth *(w+1) + margin, h*fontHeight + margin); //что-то странное происходит с размерами виджета
    //this->resize(431, 500);


}

bool Console::escClosed(QByteArray data){

    int size =  data.size();
    int pos = -1;
    for(int i = size; i >= 0 ; i--){
        if(data[i] == 0x1B){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        return true;
    }

    for(int i = pos; i < size ; i++){
        if(data[i] >= 'A' && data[i] <= 'K'){
            return true;
        }
    }

    return false;
}


int Console::write(QByteArray data){

    static QByteArray tmp; // Возможно, придется заменить на global. Нужно проверить на разных платформах
    // Проверка на целостность ESC-последовательности

    if(waitForClose){
        int i;
        bool found = false;
        for(i = 0; i < data.size(); i++){
            if(data[i] >= 'A' && data[i] <= 'K'){
                found = true;
                break;
            }
        }
        i++;
        tmp.append(data.left(i));

        if(found){
            waitForClose = false;
            emu_core_run(s, (const uint8_t*)tmp.data(), tmp.size() );
            data = data.mid(i);
        }else{
            return 0;
        }


    }


    if(escClosed(data)){
        return emu_core_run(s, (const uint8_t*)data.data(), data.size() );
    }else{
        tmp = data;
        waitForClose = true;
        return 0;
    }
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

QFont Console::setFont(QString name, int size){
    QFont f;
    int id = QFontDatabase::addApplicationFont(name);

    if(id < 0){
        f = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    }else{
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        f.setFamily(family);
    }

    f.setPixelSize(size);

    return f;
}

void Console::resizeEvent(QResizeEvent *event){

    int margin = document()->documentMargin() * 2;

    int w = (this->width() - margin) / fontWidth;
    int h = (this->height() - margin) / fontHeight;

    if(w != consoleWidth || h != consoleHeight){
        consoleWidth = w;
        consoleHeight = h;

        setLineWrapColumnOrWidth(consoleWidth);

        qDebug() << consoleHeight << consoleWidth;

        emu_core_resize(s,consoleHeight, consoleWidth );

        free(rawbuf);
        rawbuf = (char*)malloc(consoleWidth*consoleHeight*2);
    }

    QTextEdit::resizeEvent(event);
}

void Console::reset(){
    if(s){
        emu_term_reset(s);
    }
}
