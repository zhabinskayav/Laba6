QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#SET(CMAKE_CXX_STANDARD 17)
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    codeeditor.cpp \
    deparser.cpp \
    error.cpp \
    fas.cpp \
    file.cpp \
    jsontoken.cpp \
    jsonvalue.cpp \
    lexer.cpp \
    logic.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp

HEADERS += \
    codeeditor.h \
    deparser.h \
    error.h \
    fas.h \
    file.h \
    jsontoken.h \
    jsonvalue.h \
    lexer.h \
    logic.h \
    mainwindow.h \
    parser.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
