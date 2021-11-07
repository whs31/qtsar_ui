QT       += core gui network
QT       += positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11
CONFIG += static

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += "C:\Program Files\OpenSSL-Win64\include"
#LIBS += -L"C:\Program Files\OpenSSL-Win64\lib" -llibcrypto -llibssl
SOURCES += \
    console/console.cpp \
    console/fvemu.c \
    main.cpp \
    qmlinvoker.cpp \
    qmlmarkerdialog.cpp \
    remote/remoteBase.cpp \
    remote/remoteTCP.cpp \
    remote/remoteUDP.cpp \
    uisar.cpp

HEADERS += \
    console/DefaultColors.h \
    console/console.h \
    console/fvemu.h \
    qmlinvoker.h \
    qmlmarkerdialog.h \
    remote/remote.h \
    remote/remoteBase.h \
    remote/remoteTCP.h \
    remote/remoteUDP.h \
    uisar.h

FORMS += \
    qmlmarkerdialog.ui \
    uisar.ui

TRANSLATIONS += \
    uiSAR_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path): INSTALLS += target

DISTFILES += \ \
    console/UbuntuMono.ttf \
    qdarkstyle/dark/rc/.keep \
    qdarkstyle/dark/rc/arrow_down.png \
    qdarkstyle/dark/rc/arrow_down@2x.png \
    qdarkstyle/dark/rc/arrow_down_disabled.png \
    qdarkstyle/dark/rc/arrow_down_disabled@2x.png \
    qdarkstyle/dark/rc/arrow_down_focus.png \
    qdarkstyle/dark/rc/arrow_down_focus@2x.png \
    qdarkstyle/dark/rc/arrow_down_pressed.png \
    qdarkstyle/dark/rc/arrow_down_pressed@2x.png \
    qdarkstyle/dark/rc/arrow_left.png \
    qdarkstyle/dark/rc/arrow_left@2x.png \
    qdarkstyle/dark/rc/arrow_left_disabled.png \
    qdarkstyle/dark/rc/arrow_left_disabled@2x.png \
    qdarkstyle/dark/rc/arrow_left_focus.png \
    qdarkstyle/dark/rc/arrow_left_focus@2x.png \
    qdarkstyle/dark/rc/arrow_left_pressed.png \
    qdarkstyle/dark/rc/arrow_left_pressed@2x.png \
    qdarkstyle/dark/rc/arrow_right.png \
    qdarkstyle/dark/rc/arrow_right@2x.png \
    qdarkstyle/dark/rc/arrow_right_disabled.png \
    qdarkstyle/dark/rc/arrow_right_disabled@2x.png \
    qdarkstyle/dark/rc/arrow_right_focus.png \
    qdarkstyle/dark/rc/arrow_right_focus@2x.png \
    qdarkstyle/dark/rc/arrow_right_pressed.png \
    qdarkstyle/dark/rc/arrow_right_pressed@2x.png \
    qdarkstyle/dark/rc/arrow_up.png \
    qdarkstyle/dark/rc/arrow_up@2x.png \
    qdarkstyle/dark/rc/arrow_up_disabled.png \
    qdarkstyle/dark/rc/arrow_up_disabled@2x.png \
    qdarkstyle/dark/rc/arrow_up_focus.png \
    qdarkstyle/dark/rc/arrow_up_focus@2x.png \
    qdarkstyle/dark/rc/arrow_up_pressed.png \
    qdarkstyle/dark/rc/arrow_up_pressed@2x.png \
    qdarkstyle/dark/rc/base_icon.png \
    qdarkstyle/dark/rc/base_icon@2x.png \
    qdarkstyle/dark/rc/base_icon_disabled.png \
    qdarkstyle/dark/rc/base_icon_disabled@2x.png \
    qdarkstyle/dark/rc/base_icon_focus.png \
    qdarkstyle/dark/rc/base_icon_focus@2x.png \
    qdarkstyle/dark/rc/base_icon_pressed.png \
    qdarkstyle/dark/rc/base_icon_pressed@2x.png \
    qdarkstyle/dark/rc/branch_closed.png \
    qdarkstyle/dark/rc/branch_closed@2x.png \
    qdarkstyle/dark/rc/branch_closed_disabled.png \
    qdarkstyle/dark/rc/branch_closed_disabled@2x.png \
    qdarkstyle/dark/rc/branch_closed_focus.png \
    qdarkstyle/dark/rc/branch_closed_focus@2x.png \
    qdarkstyle/dark/rc/branch_closed_pressed.png \
    qdarkstyle/dark/rc/branch_closed_pressed@2x.png \
    qdarkstyle/dark/rc/branch_end.png \
    qdarkstyle/dark/rc/branch_end@2x.png \
    qdarkstyle/dark/rc/branch_end_disabled.png \
    qdarkstyle/dark/rc/branch_end_disabled@2x.png \
    qdarkstyle/dark/rc/branch_end_focus.png \
    qdarkstyle/dark/rc/branch_end_focus@2x.png \
    qdarkstyle/dark/rc/branch_end_pressed.png \
    qdarkstyle/dark/rc/branch_end_pressed@2x.png \
    qdarkstyle/dark/rc/branch_line.png \
    qdarkstyle/dark/rc/branch_line@2x.png \
    qdarkstyle/dark/rc/branch_line_disabled.png \
    qdarkstyle/dark/rc/branch_line_disabled@2x.png \
    qdarkstyle/dark/rc/branch_line_focus.png \
    qdarkstyle/dark/rc/branch_line_focus@2x.png \
    qdarkstyle/dark/rc/branch_line_pressed.png \
    qdarkstyle/dark/rc/branch_line_pressed@2x.png \
    qdarkstyle/dark/rc/branch_more.png \
    qdarkstyle/dark/rc/branch_more@2x.png \
    qdarkstyle/dark/rc/branch_more_disabled.png \
    qdarkstyle/dark/rc/branch_more_disabled@2x.png \
    qdarkstyle/dark/rc/branch_more_focus.png \
    qdarkstyle/dark/rc/branch_more_focus@2x.png \
    qdarkstyle/dark/rc/branch_more_pressed.png \
    qdarkstyle/dark/rc/branch_more_pressed@2x.png \
    qdarkstyle/dark/rc/branch_open.png \
    qdarkstyle/dark/rc/branch_open@2x.png \
    qdarkstyle/dark/rc/branch_open_disabled.png \
    qdarkstyle/dark/rc/branch_open_disabled@2x.png \
    qdarkstyle/dark/rc/branch_open_focus.png \
    qdarkstyle/dark/rc/branch_open_focus@2x.png \
    qdarkstyle/dark/rc/branch_open_pressed.png \
    qdarkstyle/dark/rc/branch_open_pressed@2x.png \
    qdarkstyle/dark/rc/checkbox_checked.png \
    qdarkstyle/dark/rc/checkbox_checked@2x.png \
    qdarkstyle/dark/rc/checkbox_checked_disabled.png \
    qdarkstyle/dark/rc/checkbox_checked_disabled@2x.png \
    qdarkstyle/dark/rc/checkbox_checked_focus.png \
    qdarkstyle/dark/rc/checkbox_checked_focus@2x.png \
    qdarkstyle/dark/rc/checkbox_checked_pressed.png \
    qdarkstyle/dark/rc/checkbox_checked_pressed@2x.png \
    qdarkstyle/dark/rc/checkbox_indeterminate.png \
    qdarkstyle/dark/rc/checkbox_indeterminate@2x.png \
    qdarkstyle/dark/rc/checkbox_indeterminate_disabled.png \
    qdarkstyle/dark/rc/checkbox_indeterminate_disabled@2x.png \
    qdarkstyle/dark/rc/checkbox_indeterminate_focus.png \
    qdarkstyle/dark/rc/checkbox_indeterminate_focus@2x.png \
    qdarkstyle/dark/rc/checkbox_indeterminate_pressed.png \
    qdarkstyle/dark/rc/checkbox_indeterminate_pressed@2x.png \
    qdarkstyle/dark/rc/checkbox_unchecked.png \
    qdarkstyle/dark/rc/checkbox_unchecked@2x.png \
    qdarkstyle/dark/rc/checkbox_unchecked_disabled.png \
    qdarkstyle/dark/rc/checkbox_unchecked_disabled@2x.png \
    qdarkstyle/dark/rc/checkbox_unchecked_focus.png \
    qdarkstyle/dark/rc/checkbox_unchecked_focus@2x.png \
    qdarkstyle/dark/rc/checkbox_unchecked_pressed.png \
    qdarkstyle/dark/rc/checkbox_unchecked_pressed@2x.png \
    qdarkstyle/dark/rc/line_horizontal.png \
    qdarkstyle/dark/rc/line_horizontal@2x.png \
    qdarkstyle/dark/rc/line_horizontal_disabled.png \
    qdarkstyle/dark/rc/line_horizontal_disabled@2x.png \
    qdarkstyle/dark/rc/line_horizontal_focus.png \
    qdarkstyle/dark/rc/line_horizontal_focus@2x.png \
    qdarkstyle/dark/rc/line_horizontal_pressed.png \
    qdarkstyle/dark/rc/line_horizontal_pressed@2x.png \
    qdarkstyle/dark/rc/line_vertical.png \
    qdarkstyle/dark/rc/line_vertical@2x.png \
    qdarkstyle/dark/rc/line_vertical_disabled.png \
    qdarkstyle/dark/rc/line_vertical_disabled@2x.png \
    qdarkstyle/dark/rc/line_vertical_focus.png \
    qdarkstyle/dark/rc/line_vertical_focus@2x.png \
    qdarkstyle/dark/rc/line_vertical_pressed.png \
    qdarkstyle/dark/rc/line_vertical_pressed@2x.png \
    qdarkstyle/dark/rc/radio_checked.png \
    qdarkstyle/dark/rc/radio_checked@2x.png \
    qdarkstyle/dark/rc/radio_checked_disabled.png \
    qdarkstyle/dark/rc/radio_checked_disabled@2x.png \
    qdarkstyle/dark/rc/radio_checked_focus.png \
    qdarkstyle/dark/rc/radio_checked_focus@2x.png \
    qdarkstyle/dark/rc/radio_checked_pressed.png \
    qdarkstyle/dark/rc/radio_checked_pressed@2x.png \
    qdarkstyle/dark/rc/radio_unchecked.png \
    qdarkstyle/dark/rc/radio_unchecked@2x.png \
    qdarkstyle/dark/rc/radio_unchecked_disabled.png \
    qdarkstyle/dark/rc/radio_unchecked_disabled@2x.png \
    qdarkstyle/dark/rc/radio_unchecked_focus.png \
    qdarkstyle/dark/rc/radio_unchecked_focus@2x.png \
    qdarkstyle/dark/rc/radio_unchecked_pressed.png \
    qdarkstyle/dark/rc/radio_unchecked_pressed@2x.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal@2x.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal_disabled.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal_disabled@2x.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal_focus.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal_focus@2x.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal_pressed.png \
    qdarkstyle/dark/rc/toolbar_move_horizontal_pressed@2x.png \
    qdarkstyle/dark/rc/toolbar_move_vertical.png \
    qdarkstyle/dark/rc/toolbar_move_vertical@2x.png \
    qdarkstyle/dark/rc/toolbar_move_vertical_disabled.png \
    qdarkstyle/dark/rc/toolbar_move_vertical_disabled@2x.png \
    qdarkstyle/dark/rc/toolbar_move_vertical_focus.png \
    qdarkstyle/dark/rc/toolbar_move_vertical_focus@2x.png \
    qdarkstyle/dark/rc/toolbar_move_vertical_pressed.png \
    qdarkstyle/dark/rc/toolbar_move_vertical_pressed@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal_disabled.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal_disabled@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal_focus.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal_focus@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal_pressed.png \
    qdarkstyle/dark/rc/toolbar_separator_horizontal_pressed@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical_disabled.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical_disabled@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical_focus.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical_focus@2x.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical_pressed.png \
    qdarkstyle/dark/rc/toolbar_separator_vertical_pressed@2x.png \
    qdarkstyle/dark/rc/transparent.png \
    qdarkstyle/dark/rc/transparent@2x.png \
    qdarkstyle/dark/rc/transparent_disabled.png \
    qdarkstyle/dark/rc/transparent_disabled@2x.png \
    qdarkstyle/dark/rc/transparent_focus.png \
    qdarkstyle/dark/rc/transparent_focus@2x.png \
    qdarkstyle/dark/rc/transparent_pressed.png \
    qdarkstyle/dark/rc/transparent_pressed@2x.png \
    qdarkstyle/dark/rc/window_close.png \
    qdarkstyle/dark/rc/window_close@2x.png \
    qdarkstyle/dark/rc/window_close_disabled.png \
    qdarkstyle/dark/rc/window_close_disabled@2x.png \
    qdarkstyle/dark/rc/window_close_focus.png \
    qdarkstyle/dark/rc/window_close_focus@2x.png \
    qdarkstyle/dark/rc/window_close_pressed.png \
    qdarkstyle/dark/rc/window_close_pressed@2x.png \
    qdarkstyle/dark/rc/window_grip.png \
    qdarkstyle/dark/rc/window_grip@2x.png \
    qdarkstyle/dark/rc/window_grip_disabled.png \
    qdarkstyle/dark/rc/window_grip_disabled@2x.png \
    qdarkstyle/dark/rc/window_grip_focus.png \
    qdarkstyle/dark/rc/window_grip_focus@2x.png \
    qdarkstyle/dark/rc/window_grip_pressed.png \
    qdarkstyle/dark/rc/window_grip_pressed@2x.png \
    qdarkstyle/dark/rc/window_minimize.png \
    qdarkstyle/dark/rc/window_minimize@2x.png \
    qdarkstyle/dark/rc/window_minimize_disabled.png \
    qdarkstyle/dark/rc/window_minimize_disabled@2x.png \
    qdarkstyle/dark/rc/window_minimize_focus.png \
    qdarkstyle/dark/rc/window_minimize_focus@2x.png \
    qdarkstyle/dark/rc/window_minimize_pressed.png \
    qdarkstyle/dark/rc/window_minimize_pressed@2x.png \
    qdarkstyle/dark/rc/window_undock.png \
    qdarkstyle/dark/rc/window_undock@2x.png \
    qdarkstyle/dark/rc/window_undock_disabled.png \
    qdarkstyle/dark/rc/window_undock_disabled@2x.png \
    qdarkstyle/dark/rc/window_undock_focus.p ng \
    qdarkstyle/dark/rc/window_undock_focus@2x.png \
    qdarkstyle/dark/rc/window_undock_pressed.png \
    qdarkstyle/dark/rc/window_undock_pressed@2x.png \
    qdarkstyle/dark/style.qss \
    qtlog.txt


RESOURCES += \
    img.qrc \
    lstyle.qrc \
    qdarkstyle/dark/style.qrc \
    qml.qrc \


TARGET = Quasar
win32 {
    RC_FILE = winadmin.rc
}

