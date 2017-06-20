
#include <QGuiApplication>
#include <QDir>
#include <QQmlEngine>
#include <QQmlContext>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>

#include "ViewManager.h"
#include "QQuickViewReload.h"

ViewManager gViewManager;

static int s_screenUpdateCount = 0;


ViewManager::ViewManager() :
    m_view(0),
    m_currentScreenId(""),
    m_PreviousScreenId(""),
    m_reloadQmlQueued(false),
    m_translationPath(QString())
{

}


ViewManager::~ViewManager()
{
    qDeleteAll(m_screensMap);
    m_screensMap.clear();

}


void ViewManager::show(QQuickViewReload *view)
{
    m_view = view;

    // Load the top level QML file path. This is a static variable for the entire project
    m_view->setRootSourcePath(SOURCE_ROOT_PATH);

    // Path to the qml file we want to reload relative to the Root Source path
    m_view->setQmlFilePath("/qml/main.qml");

    connect(m_view, SIGNAL(qmlReloaded()), this, SLOT(refreshCurrentScreen()));

    m_view->show();

    setCurrentScreen("UI_BLUE_SCREEN");
}


QString ViewManager::currentScreenName()
{
    Screen* screen = m_screensMap.value(m_currentScreenId);
    if (screen)
    {
        return screen->name;
    }

    return QString();
}

QString ViewManager::currentScreenFilename()
{
    Screen* screen = m_screensMap.value(m_currentScreenId);
    if (screen)
    {
        return screen->filename;
    }

    return QString();
}

QString ViewManager::previousScreenId() const
{
    return m_PreviousScreenId;
}

QString ViewManager::screenFilename(QString screenId)
{
    Screen* screen = m_screensMap.value(screenId);
    if (screen)
    {
        return screen->filename;
    }

    return QString();
}


QString ViewManager::currentScreenId() const
{
    return m_currentScreenId;
}

void ViewManager::setCurrentScreen(const QString newScreenId)
{

    Q_ASSERT_X(m_screensMap.contains(newScreenId), "ViewManager::setCurrentScreen", QString("Invalid screen Id: " + newScreenId).toUtf8() );


    if(m_currentScreenId != newScreenId)
    {
        m_PreviousScreenId = m_currentScreenId;
        m_currentScreenId = newScreenId;
        qDebug() << "ViewManager::setCurrentScreen " <<  this->currentScreenName();
    }
    else
    {
        // This may seem a bit strange, but m_PreviousScreenId was getting out of sync while reloading QML
        m_PreviousScreenId = newScreenId;
    }
    emit currentScreenChanged();
}

void ViewManager::setPreviousScreen()
{
    setCurrentScreen(m_PreviousScreenId);
}



void ViewManager::quit()
{
    qApp->quit();
}

void ViewManager::init(const QString& templateName)
{
    m_translationPath = ":/translations";

    qApp->installTranslator(&m_translator);
    m_translator.load(gTranslator.name(), m_translationPath);

    connect(&gTranslator, SIGNAL(languageIndexChanged(QString)), this, SLOT(setLanguage(QString)));
    connect(&gTranslator, SIGNAL(requestUiReload()),this, SLOT(reloadQml()));

    loadTemplate(templateName);

}


void ViewManager::loadTemplate(QString templateFile)
{
    QFile file(templateFile);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << Q_FUNC_INFO << "can't open file:" << templateFile;
        return;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), & error);
    file.close();
    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << Q_FUNC_INFO << "template config file error:" << error.errorString();
        return;
    }

    QJsonObject json = doc.object();


    QJsonArray screensArray = json.value("Screens").toArray();
    for(int i=0; i < screensArray.size(); ++i)
    {
        QJsonObject screen   = screensArray.at( i ).toObject();
        QString id           = screen.value("id").toString();
        QString name         = screen.value("name").toString();
        QString filename     = screen.value("filename").toString();
        QString accessLevel  = screen.value("accessLevel").toString();
        qDebug() << "screenId" << id << "name" << name << "filename" << filename << "accessLevel" << accessLevel;

        Screen *newScreen = new Screen();
        newScreen->id = id.toInt();
        newScreen->name = name;
        newScreen->filename = filename;
        //newScreen->accessLevel = static_cast<enum_accessLevel>(accessLevel.toInt());

        m_screensMap.insert( id, newScreen );
    }

    QJsonArray localeArr = json.value( "Languages" ).toArray();
    QStringList locales;
    for( int i = 0; i < localeArr.size(); i++ )
    {
        locales << localeArr.at( i ).toString();
    }
    qDebug() << "loading locales: " << locales;
    gTranslator.setLocaleList(locales);

}


void ViewManager::setTemplate(const QString& templateName, bool doReloadQml)
{
    // clear template data, then reload
    qDeleteAll(m_screensMap);
    m_screensMap.clear();

    loadTemplate(templateName);


    if (doReloadQml)
    {
        reloadQml();
    }
}

void ViewManager::reloadQml()
{
    if (!m_reloadQmlQueued)
    {
        m_reloadQmlQueued = true;
        QMetaObject::invokeMethod(this, "reloadQmlDelayed", Qt::QueuedConnection);
    }
}

void ViewManager::reloadQmlDelayed()
{
    m_reloadQmlQueued = false;
    QTime benchmark;
    benchmark.start();

    m_view->setSource(QUrl("qrc:/qml/main.qml"));
    setCurrentScreen(m_currentScreenId);

    qDebug() << "reloadQmlDelayed Reloaded QML in" << benchmark.elapsed() << "ms";
    emit qmlReloaded();
}



//A QML reload is required after a languange change due to a QML bug
void ViewManager::setLanguage(const QString& localeCode)
{
    qDebug() << "ViewManager::setLanguage: " << localeCode << " m_translationPath: " << m_translationPath;

    qApp->installTranslator(&m_translator);
    m_translator.load(localeCode, m_translationPath);

    reloadQml();
}

void ViewManager::refreshCurrentScreen()
{
    setCurrentScreen(m_currentScreenId);
}





