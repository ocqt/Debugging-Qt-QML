#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QSettings>


#include <QTranslator>
#include <QDebug>

#include "QQuickViewReload.h"
#include "ViewManager.h"
#include "Translator.h"
#include "DebugTests.h"

QQuickViewReload* appView;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName("ICS Qt Quick Reload");
    app.setApplicationDisplayName("ICS Qt Quick Reload");
    app.setOrganizationName("Integrated Computer Solutions");
    app.setOrganizationDomain("com.ics");


    QQuickViewReload mainWindow;


    QString DEFAULT_TEMPLATE_NAME =  ":/templates/default.json";
    gTranslator.init();
    gViewManager.init(DEFAULT_TEMPLATE_NAME);

    mainWindow.rootContext()->setContextProperty("Translator", &gTranslator); // using extern
    mainWindow.rootContext()->setContextProperty("ViewManager", &gViewManager);  // using extern

    mainWindow.rootContext()->setContextProperty("DebugTests", DebugTests::instance()); // using singleton

    mainWindow.setResizeMode(QQuickView::SizeRootObjectToView);
    mainWindow.setSource( QUrl( "qrc:/qml/main.qml") );
    mainWindow.setPosition(400,400);

    gViewManager.show(&mainWindow);

    return app.exec();
}
