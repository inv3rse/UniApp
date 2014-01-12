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
    stinedata.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    qmlData.qrc

HEADERS += \
    stineclient.h \
    stinedata.h

ANDROID_EXTRA_LIBS = ../../openssl-1.0.1f/libcrypto.so ../../openssl-1.0.1f/libssl.so

OTHER_FILES += \
    android/libs/armeabi-v7a/libcrypto.so \
    android/libs/armeabi-v7a/libssl.so \
    qml/UniApp/Today.qml
