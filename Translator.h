#ifndef TRANSLATOR
#define TRANSLATOR

#ifndef Translator_H
#define Translator_H

#include <QObject>
#include <QLocale>
#include <QDateTime>
#include <QSettings>


class QSettings;

class Translator : public QObject
{
    Q_OBJECT
    Q_ENUMS(TemperatureUnit)
    Q_ENUMS(MeasurementUnits)
    Q_ENUMS(TimeFormat)

    Q_PROPERTY(QStringList languageList READ languageList NOTIFY languageListChanged)
    Q_PROPERTY(QStringList translatedLanguageList READ translatedLanguageList NOTIFY languageListChanged)
    Q_PROPERTY(int languageIndex READ languageIndex WRITE setLanguageIndex NOTIFY languageIndexChanged)

    Q_PROPERTY(QString localeName READ localeName NOTIFY localeNameChanged)


public:
    Q_INVOKABLE QString getLocaleName(int index);

    Translator();

    void init();

    QString name() const;

    void setLocaleList(const QStringList& localeCodes);

    QStringList languageList() const;
    QStringList translatedLanguageList() const;
    int languageIndex() const;
    void setLanguageIndex(int languageIndex);

    void loadLocale(QLocale locale);


    QString localeName() const;

    int defaultLanguageIndex() const;
    void setDefaultLanguageIndex(int languageIndex);


    inline QList<QLocale> getLocaleList( void ) {return m_localeList;}


public slots:



signals:
    void languageListChanged();
    void languageIndexChanged(const QString& localeName);
    void requestUiReload();
    void localeNameChanged();

private:

    QSettings* m_settings;
    QLocale m_locale;
    QList<QLocale> m_localeList;

    const QString keyLanguage = "Language";


    QStringList translatedLanguageNames = QStringList() <<
                                 QT_TRANSLATE_NOOP("Translator","English") <<
                                 QT_TRANSLATE_NOOP("Translator","Spanish") <<
                                 QT_TRANSLATE_NOOP("Translator","French");
};

/***************************   Global Variables   ****************************/
extern Translator gTranslator;


#endif // Translator_H


#endif // TRANSLATOR
