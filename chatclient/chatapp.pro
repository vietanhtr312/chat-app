QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatclient.cpp \
    creategroupchat.cpp \
    friendrequest.cpp \
    friendslist.cpp \
    invitetoroom.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    removeroomuser.cpp \
    signup.cpp

HEADERS += \
    chatclient.h \
    creategroupchat.h \
    friendrequest.h \
    friendslist.h \
    invitetoroom.h \
    loginwindow.h \
    mainwindow.h \
    removeroomuser.h \
    signup.h

FORMS += \
    creategroupchat.ui \
    friendrequest.ui \
    friendslist.ui \
    loginwindow.ui \
    mainwindow.ui\
    invitetoroom.ui \
    removeroomuser.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resoure.qrc
