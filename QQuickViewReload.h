#ifndef QQUICKVIEWRELOAD_H
#define QQUICKVIEWRELOAD_H

#include <QQuickView>
#include <QGuiApplication>

class QQuickViewReload : public QQuickView
{
    Q_OBJECT

public:
    QQuickViewReload();
    ~QQuickViewReload();
    void keyPressEvent(QKeyEvent* e);

    static void setRootSourcePath(QString path);

    void setQmlFilePath(QString path);

public slots:
    void reloadQmlFromDisk();

signals:
    void qmlReloaded();

protected:

    static QString s_RootSourcePath;
    QString m_qmlFilePath;

};

#endif // QQUICKVIEWRELOAD_H
