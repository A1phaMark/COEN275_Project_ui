QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    bugmodel.cpp \
    bugobject.cpp \
    commentmodel.cpp \
    commentobject.cpp \
    db.cpp \
    main.cpp \
    management_tool.cpp \
    participantmodel.cpp \
    participantobject.cpp \
    projectmodel.cpp \
    projectobject.cpp \
    taskmodel.cpp \
    taskobject.cpp \
    timelinemodel.cpp \
    timelineobject.cpp \
    user.cpp \
    usermodel.cpp

HEADERS += \
    auth.h \
    bugmodel.h \
    bugobject.h \
    commentmodel.h \
    commentobject.h \
    db.h \
    management_tool.h \
    participantmodel.h \
    participantobject.h \
    projectmodel.h \
    projectobject.h \
    taskmodel.h \
    taskobject.h \
    timelinemodel.h \
    timelineobject.h \
    user.h \
    usermodel.h

FORMS += \
    management_tool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
