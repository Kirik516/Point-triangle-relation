#-------------------------------------------------
#
# Project created by QtCreator 2022-10-02T21:44:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = check-point-and-triangle-relation-algorithm
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        widget.cpp \
    paint-state.cpp \
    paint-stratagy/line-cross-paint.cpp

HEADERS  += widget.h \
    paint-state.h \
    paint-opetations/paint-operation.h \
    paint-stratagy/paint-stratagy.h \
    paint-stratagy/line-cross-paint.h \
    paint-opetations/vector-product-operations.h
