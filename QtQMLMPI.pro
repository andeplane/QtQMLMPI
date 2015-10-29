TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += qml quick
CONFIG += c++11
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lmpi

SOURCES += main.cpp \
    mpicontroller.cpp \
    mympicontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mpicontroller.h \
    mympicontroller.h

