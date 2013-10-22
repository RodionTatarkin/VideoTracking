# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xEA74C50D

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbians
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
CONFIG += mobility

INCLUDEPATH += . ../maps/inc ../common/inc ../http_requestsMyRodion/inc

MOBILITY += location
MOBILITY += multimedia

LIBS += -L../libMyRodion/ -lcommon -lqjson -lwikigpsHttpMyRodion -lwikigpsJson
# LIBS += -L../lib/ -lmaps -lqjson -lcommon -lwikigpsHttp -lwikigpsJson

SOURCES += main.cpp \
    cam.cpp \
    videowidget.cpp \
    player.cpp \
    mainwindow.cpp \
    geovideo.cpp \
    logindialog.cpp \
    channeldialog.cpp \
    downloadvideowidget.cpp \
    ftpdialog.cpp \
    createchanneldialog.cpp \
    loadinglabel.cpp
HEADERS += \
    cam.h \
    videowidget.h \
    player.h \
    mainwindow.h \
    geovideo.h \
    logindialog.h \
    channeldialog.h \
    downloadvideowidget.h \
    ftpdialog.h \
    createchanneldialog.h \
    loadinglabel.h
FORMS +=

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

RESOURCES += \
    images.qrc
QT += network
