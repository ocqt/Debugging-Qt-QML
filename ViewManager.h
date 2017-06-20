#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QtQuick>
#include "Translator.h"


class QSettings;
class QQuickViewReload;

class ViewManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentScreenId READ currentScreenId  NOTIFY currentScreenChanged)
    Q_PROPERTY(QString currentScreenName READ currentScreenName  NOTIFY currentScreenChanged)
    Q_PROPERTY(QString currentScreenFilename READ currentScreenFilename  NOTIFY currentScreenChanged)

    Q_PROPERTY(QString previousScreenId READ previousScreenId  NOTIFY currentScreenChanged)

public:
    explicit ViewManager();
    ~ViewManager();


    Q_ENUMS(enum_accessLevel)

    void show(QQuickViewReload *view);
    void quit();
    void init(const QString& templateName);

    Q_INVOKABLE void setCurrentScreen(const QString newScreenId);
    Q_INVOKABLE void setPreviousScreen(void);


    Q_INVOKABLE QString screenFilename(QString screenId);

    QString currentScreenId() const;
    QString currentScreenName();
    QString currentScreenFilename();

    QString previousScreenId() const;

    Q_INVOKABLE void loadTemplate(QString templateFile);

public slots:
    void reloadQml();
    void reloadQmlDelayed();  // When changing locale, we must post a message to reload the QML

    void setTemplate(const QString& templateName, bool doReloadQml = false);

signals:

    void currentScreenChanged();
    void qmlReloaded();

private:

    QList<QObject*> screens();

private slots:

    // Translator will call this when the language changes
    void setLanguage(const QString& localeCode);

    void refreshCurrentScreen();

private:

    struct Screen : QObject {
        QString                 id;               // screen id based on old enum
        QString                 name;             // screen name or title
        QString                 filename;         // qml file name
        //enum_accessLevel      accessLevel;      // required operator level

    };

    QQuickViewReload* m_view;

    QMap<QString, Screen*>m_screensMap;

    QString m_currentScreenId;
    QString m_PreviousScreenId;

    bool m_reloadQmlQueued;

    QTranslator m_translator;
    QString m_translationPath;


};

extern ViewManager gViewManager;

#endif // VIEWMANAGER_H
