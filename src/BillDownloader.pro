#-------------------------------------------------
#
# Project created by QtCreator 2018-03-08T14:03:34
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QZXing/QZXing.pri)

TARGET = BillDownloader
TEMPLATE = app

#dependency
# qtdeclarative5-dev libqt5quick5 libqt5quick-dev qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    cwimage.cpp \
    dialogscanreceipt.cpp \
    dialogcopytext.cpp \
    modelscan.cpp \
    export/abilitycash/abilitycashexport.cpp \
    export/abilitycash/ac_currencies.cpp \
    export/abilitycash/ac_classifiers.cpp \
    export/abilitycash/ac_transactions.cpp \
    export/abilitycash/ac_export_options.cpp \
    export/abilitycash/ac_accounts.cpp \
    dialogaddfilter.cpp \
    autofilter.cpp \
    modelreceipts.cpp \
    requestlist.cpp \
    dialogprogress.cpp

HEADERS  += mainwindow.h \
    cwimage.h \
    dialogscanreceipt.h \
    dialogcopytext.h \
    modelscan.h \
    utils.h \
    export/abilitycash/abilitycashexport.h \
    export/abilitycash/ac_currencies.h \
    export/abilitycash/ac_classifiers.h \
    export/abilitycash/ac_transactions.h \
    export/abilitycash/ac_export_options.h \
    export/abilitycash/ac_accounts.h \
    dialogaddfilter.h \
    autofilter.h \
    modelreceipts.h \
    requestlist.h \
    dialogprogress.h

FORMS    += mainwindow.ui \
    dialogscanreceipt.ui \
    dialogcopytext.ui \
    dialogaddfilter.ui \
    dialogprogress.ui

DISTFILES += \
    categories.txt
