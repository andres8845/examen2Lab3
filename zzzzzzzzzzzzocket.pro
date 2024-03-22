QT       += core gui
QT       += core network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChatProtocol.cpp \
    ChatProtocolserver.cpp \
    ClientChatWidget.cpp \
    ClientManager.cpp \
    ClientServerManager.cpp \
    ServerManager.cpp \
    cliente.cpp \
    main.cpp \
    mainwindow.cpp \
    msg.cpp \
    usuario.cpp

HEADERS += \
    ../chatFinal/qtchatapplication-master/Client/mainwindow.h \
    ChatProtocol.h \
    ClientChatWidget.h \
    ClientManager.h \
    ClientServerManager.h \
    ChatProtocolserver.h \
    ServerManager.h \
    cliente.h \
    mainwindow.h \
    msg.h \
    usuario.h

FORMS += \
    ClientChatWidget.ui \
    cliente.ui \
    mainwindow.ui \
    msg.ui \
    msg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Client/Client.pro \
    Server/Server.pro

RESOURCES += \
    Server/icons.qrc

DISTFILES += \
    Server/icons/available.png \
    Server/icons/away.png \
    Server/icons/busy.png


FORMS += \
    ClientChatWidget.ui \
    cliente.ui \
    mainwindow.ui \
    msg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Client/Client.pro \
    Server/Server.pro

RESOURCES += \
    Server/icons.qrc

DISTFILES += \
    Server/icons/available.png \
    Server/icons/away.png \
    Server/icons/busy.png
