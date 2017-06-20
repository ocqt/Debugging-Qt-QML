TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    QQuickViewReload.cpp \
    ViewManager.cpp \
    Translator.cpp \
    DebugTests.cpp

RESOURCES += qml.qrc \
    translations.qrc

# This creates a variable we can use from C++ to set
# the QML Quick reload path.
DEFINES += SOURCE_ROOT_PATH=\\\"$$_PRO_FILE_PWD_\\\"

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    QQuickViewReload.h \
    ViewManager.h \
    Translator.h \
    DebugTests.h

