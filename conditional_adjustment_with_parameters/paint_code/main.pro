QT+=core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG+=c++11
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES+=QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES+=QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES+=\
    source/mainwindow.cpp\
    source/main.cpp
HEADERS+=\
    header/mainwindow.h \
    header/all.h
INCLUDEPATH+=./header
FORMS+=\
    form/mainwindow.ui
# Default rules for deployment.
qnx: target.path=/tmp/$${TARGET}/bin
else: unix:!android: target.path=/opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS+=target
# for_eigen
INCLUDEPATH+=/usr/include/eigen3
# app图标
RC_ICONS=icon/icon.ico
# 初学配置
QMAKE_CXXFLAGS+=-std=c++0x
TARGET=main
TEMPLATE=app
RESOURCES+=\
    main.qrc \
    main.qrc
# 设置各种中间文件及可执行文件生成目录
DESTDIR=build
OBJECTS_DIR=build/obj
MOC_DIR=build/moc
RCC_DIR=build/rcc
UI_DIR=build/ui
