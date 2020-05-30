#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T23:44:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg opengl

TARGET = SVGViewer
TEMPLATE = app

VERSION = 0.1.0
DEFINES += "APP_VERSION=\"\\\"$$VERSION\\\"\""


CONFIG(release, debug|release) {
    BASEDESTDIR = ..\SVGViewer-deploy
    QMAKE_CXXFLAGS_RELEASE -= -O2

    win32{
        DESTDIR = $${BASEDESTDIR}-win32
        QMAKE_POST_LINK += windeployqt $$DESTDIR --no-translations --release --force
        RC_FILE = windows/svg_viewer.rc
    }
    # Code from https://stackoverflow.com/questions/356666/identifier-for-win64-configuration-in-qmake:
    #win32 {
    #
    #    ## Windows common build here
    #
    #    !contains(QMAKE_TARGET.arch, x86_64) {
    #        message("x86 build")
    #
    #        ## Windows x86 (32bit) specific build here
    #
    #    } else {
    #        message("x86_64 build")
    #
    #        ## Windows x64 (64bit) specific build here
    #
    #    }
    #}

}

SOURCES += main.cpp\
           mainwindow.cpp \
           svgview.cpp

HEADERS += mainwindow.h \
           defines.h \
           svgview.h

FORMS   += mainwindow.ui

