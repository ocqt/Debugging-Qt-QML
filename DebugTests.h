#ifndef DEBUGTESTS_H
#define DEBUGTESTS_H

#include <QObject>

class DebugTests : public QObject
{
    Q_OBJECT

public:
    DebugTests();
    static DebugTests* instance();

    Q_INVOKABLE QObject *badPointerToQml() const;
    Q_INVOKABLE void badPointer();

    Q_INVOKABLE void breakInLoop();
    Q_INVOKABLE int badMath();
    Q_INVOKABLE int stackOverflow(int i);


signals:

public slots:


private:

    QString* returnBadPointer();

    int m_intValue = 22;
    QString m_stringValue = "Test String";
    QStringList m_stringList;


};



#endif // DEBUGTESTS_H
