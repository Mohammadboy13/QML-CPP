#ifndef QMLCREATOR_H
#define QMLCREATOR_H

#include "parsejson.h"
#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>

class QMLCreator : public QObject
{
    Q_OBJECT
public:
    explicit QMLCreator(QList<matchmember> obj ,QObject *parent = nullptr);



private:
    QList<matchmember> obje;

signals:
};

#endif // QMLCREATOR_H
