QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abb.cpp \
    avltree.cpp \
    blockchain.cpp \
    btree.cpp \
    contador.cpp \
    globals.cpp \
    huffman.cpp \
    listapublicaciones.cpp \
    listasimple.cpp \
    listasimpleamigos.cpp \
    listasimplesolicitudes.cpp \
    listasugerencias.cpp \
    main.cpp \
    login.cpp \
    matrix.cpp \
    nodoamigos.cpp \
    nodosolicitud.cpp \
    pilasolicitudes.cpp \
    profileadministrator.cpp \
    profileuser.cpp \
    redsocial.cpp \
    registrarusuario.cpp \
    relationlist.cpp \
    solicitudamistad.cpp

HEADERS += \
    abb.h \
    avltree.h \
    blockchain.h \
    btree.h \
    contador.h \
    globals.h \
    huffman.h \
    listapublicaciones.h \
    listasimple.h \
    listasimpleamigos.h \
    listasimplesolicitudes.h \
    listasugerencias.h \
    login.h \
    matrix.h \
    nodoamigos.h \
    nodosolicitud.h \
    nodosugerencias.h \
    pilasolicitudes.h \
    profileadministrator.h \
    profileuser.h \
    redsocial.h \
    registrarusuario.h \
    relationlist.h \
    solicitudamistad.h

FORMS += \
    login.ui \
    profileadministrator.ui \
    profileuser.ui \
    registrarusuario.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    resources.qrc
