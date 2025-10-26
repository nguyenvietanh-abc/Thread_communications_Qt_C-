QT += core
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = library_oop
TEMPLATE = app

INCLUDEPATH += src src/core src/thread src/utils

SOURCES += \
    main.cpp \
    src/core/Book.cpp \
    src/core/Library.cpp \
    src/thread/Worker.cpp \
    src/utils/Console.cpp

HEADERS += \
    src/core/Book.h \
    src/core/Library.h \
    src/thread/Worker.h \
    src/utils/Console.h
