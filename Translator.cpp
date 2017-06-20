#include "Translator.h"

#include <QCoreApplication>
#include <QSettings>
#include <QStringList>
#include <QDebug>
#include <QDir>


/***************************   Global Variables   ****************************/
Translator gTranslator;


Translator::Translator()
{

}



void Translator::init()
{

  QString settingsPath =  QCoreApplication::applicationDirPath() + QDir::separator() +  "appsettings.ini";;
  m_settings = new QSettings(settingsPath, QSettings::IniFormat, this);

  // If no entry for keyLanguage default to "en_US"
  loadLocale( QLocale(m_settings->value(keyLanguage, "en_US").toString()) );

}


QString Translator::name() const
{
    return m_locale.name();
}

void Translator::setLocaleList(const QStringList& localeCodes)
{
    m_localeList.clear();
    foreach(QString localeCode, localeCodes)
        m_localeList << QLocale(localeCode);

    //qDebug() << "m_localeList" << m_localeList;
    emit languageListChanged();
}


QStringList Translator::languageList() const
{
    QStringList languageNames;
    foreach (QLocale locale, m_localeList) {
        QString lang = QLocale::languageToString(locale.language());
        languageNames << QString("%1").arg(lang);

    }
    //qDebug() << "languageNames" << languageNames;
    return languageNames;
}


QStringList Translator::translatedLanguageList() const
{
  QStringList returnList;
  foreach (const QString languageName, languageList())
  {
    returnList.append(tr(languageName.toUtf8()));
  }
  return returnList;
}

int Translator::languageIndex() const
{
    return m_localeList.indexOf(m_locale);
}


void Translator::setLanguageIndex(int languageIndex)
{
    qDebug() << "Translator::setLanguageIndex " << languageIndex;
    QLocale locale = m_localeList.value(languageIndex);
    loadLocale(locale);
    emit localeNameChanged();
}

void Translator::loadLocale(QLocale locale)
{
    m_locale = locale;
    QLocale::setDefault(m_locale);

    QString localeName = locale.name();

    qDebug() << "loadLocale settings " << m_settings->value(keyLanguage).toString() << "localeName " << localeName;

    if (m_settings->value(keyLanguage, "en_US").toString() != localeName)
    {
        m_settings->setValue(keyLanguage, localeName);
        m_settings->sync();
        loadLocale(locale);

        emit languageIndexChanged(localeName);
    }

}



QString Translator::localeName() const
{
  return m_locale.name();
}




QString Translator::getLocaleName(int index)
{
  QString str = "";
  if(index < m_localeList.size())
  {
    str = m_localeList.at(index).name();
  }
  return (str);
}

