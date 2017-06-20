#include <QDebug>


#include "DebugTests.h"

DebugTests::DebugTests()
{
   m_stringList << "string 1" << "string 2" << "string 3";
}

DebugTests *DebugTests::instance()
{
    static DebugTests* m_instance = nullptr;

    if (m_instance == nullptr)
    {
        m_instance = new DebugTests();
    }

    return m_instance;
}

QObject *DebugTests::badPointerToQml() const
{
   QScopedPointer<QObject> ptr(new QObject());
   return ptr.data();
}

void DebugTests::badPointer()
{
   QString* pStr = returnBadPointer();

   qDebug() << "bad pointer: " << &pStr;
   pStr->append("BOOM!");

}

QString* DebugTests::returnBadPointer()
{
  QScopedPointer<QString> ptr(new QString());

  // pointer goes out of scope when we return
  return ptr.data();
}

void DebugTests::breakInLoop()
{
    double localDouble = 3.1416;
    QList<QString> localList;

    for (int i=0; i<10; ++i)
    {
        qDebug() << i;
        localList.append("listEntry: " + QString::number(i));
    }

    qDebug() << "localList: " << localList;
    qDebug() << "localDouble: " << QString::number(localDouble);
}

int DebugTests::badMath()
{
    int numerator = m_intValue;
    int denominator = 0;
    double result =  numerator/ denominator;
    return result;
}

int DebugTests::stackOverflow(int i)
{
    stackOverflow(i+ 1);
}



