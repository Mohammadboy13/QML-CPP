#ifndef QMLCREATOR_H
#define QMLCREATOR_H

#include "parsejson.h"
#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>

class QMLCreator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList members READ getMembers NOTIFY membersChanged)

public:
    explicit QMLCreator(QObject *parent = nullptr) : QObject(parent){};
    QMLCreator(const QList<matchmember>& field, QObject *parent = nullptr) : QObject(parent), m_originalMembers(field){};

    QVariantList getMembers() const { return m_members; }

    // Set the list directly
    Q_INVOKABLE void setMembers(const QList<matchmember>& members){
        m_originalMembers = members;
        m_members.clear();

        // Convert to QVariantList for QML
        for (const matchmember& member : members) {
            QVariantMap map;
            map["Id_qml"] = member.Id_qml;
            map["X"] = member.X;
            map["Y"] = member.Y;
            map["color_Hex"] = member.color_Hex;
            map["Id_cpp"] = member.Id_cpp;
            map["Msec"] = member.Msec;
            map["Min"] = member.Min;
            map["Max"] = member.Max;

            m_members.append(map);
        }

        emit membersChanged();
    }

    // Update position
    Q_INVOKABLE void updatePosition(const QString& id_qml, int x, int y){
        // Update original list
        for (auto& member : m_originalMembers) {
            if (member.Id_qml == id_qml) {
                member.X = x;
                member.Y = y;
                break;
            }
        }

        // Update variant list
        for (int i = 0; i < m_members.size(); ++i) {
            QVariantMap map = m_members[i].toMap();
            if (map["Id_qml"].toString() == id_qml) {
                map["X"] = x;
                map["Y"] = y;
                m_members[i] = map;
                break;
            }
        }

        emit membersChanged();
    }

signals:
    void membersChanged();

private:
    QVariantList m_members;
    QList<matchmember> m_originalMembers;
};

#endif // QMLCREATOR_H
