QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ReplayFile.cpp \
    button_delegate.cpp \
    button_delegate2.cpp \
    checkbox_headerview.cpp \
    combobox_delegate.cpp \
    data_test.cpp \
    frc_const.cpp \
    main.cpp \
    mainwindow.cpp \
    playerform.cpp \
    readonly_delegate.cpp \
    table_model.cpp

HEADERS += \
    Area.h \
    ReplayFile.h \
    Target.h \
    button_delegate.h \
    button_delegate2.h \
    checkbox_headerview.h \
    combobox_delegate.h \
    data_test.h \
    frc_const.h \
    mainwindow.h \
    playerform.h \
    readonly_delegate.h \
    table_model.h

FORMS += \
    mainwindow.ui \
    playerform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
