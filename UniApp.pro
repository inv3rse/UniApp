# Add more folders to ship with the application, here
folder_01.source = qml/UniApp
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += network

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    stineclient.cpp \
    datalayer.cpp \
    log.cpp \
    termin.cpp \
    day.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    qmlData.qrc

HEADERS += \
    stineclient.h \
    datalayer.h \
    log.h \
    termin.h \
    day.h

CONFIG += c++11

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        /home/dennis/Downloads/openssl-1.0.1i/libcrypto.so \
        /home/dennis/Downloads/openssl-1.0.1i/libssl.so
}
