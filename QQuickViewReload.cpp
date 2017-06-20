#include <QDir>
#include <QQmlEngine>
#include <QDebug>

#include "QQuickViewReload.h"

QString QQuickViewReload::s_RootSourcePath = QString();

QQuickViewReload::QQuickViewReload () :
    m_qmlFilePath(QString())
{
}

QQuickViewReload::~QQuickViewReload ()
{
}

void QQuickViewReload::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_F5)
    {
#ifdef QT_DEBUG  // only invoke the reload in debug mode...
        QMetaObject::invokeMethod(this, "reloadQmlFromDisk", Qt::QueuedConnection);
#endif
    }

    QQuickView::keyPressEvent(e);
}

void QQuickViewReload::setRootSourcePath(QString path)
{
    s_RootSourcePath = path;
}

void QQuickViewReload::setQmlFilePath(QString path)
{
    m_qmlFilePath = path;
}

void QQuickViewReload::reloadQmlFromDisk()
{
    // Initially, the application loads the QML files from the embedded resources.  On F5 reload, it switches to loading
    // directly from the QML source files on disk. This allows a refresh without restarting the application.
    engine()->clearComponentCache();

    QString qmlFilePath = s_RootSourcePath + m_qmlFilePath;
    setSource( QUrl::fromLocalFile(qmlFilePath) );

     emit qmlReloaded();
}



