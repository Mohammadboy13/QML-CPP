#include "parsejson.h"


#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


ParseJson::ParseJson(const QString &fileAddress) {
    QFile file(fileAddress);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("couldnt open file");
        return;
    }
    QByteArray jsondata = file.readAll();
    file.close();

    QJsonDocument json = QJsonDocument::fromJson(jsondata);
    if (json.isNull()) {
        qWarning("file is Empty");
        return;
    }

    QJsonObject root = json.object();
    parseCppmember(root);
    parseQmlmember(root);

    for (auto memberqml : std::as_const(this->config.qmlMembers)) {
        for (auto memberscpp : std::as_const(this->config.cppMembers)) {
            if (memberqml.dataSource == memberscpp.Id) {
                matchmember memberr;
                memberr.Id_cpp = memberscpp.Id;
                memberr.Max = memberscpp.Max;
                memberr.Min = memberscpp.Min;
                memberr.Msec = memberscpp.Msec;

                memberr.Id_qml = memberqml.Id;
                memberr.X = memberqml.X;
                memberr.Y = memberqml.Y;
                memberr.color_Hex = memberqml.color_Hex;

                config.member.append(memberr);
            }
        }
    }

}

bool ParseJson::parseCppmember(const QJsonObject &root){
    if( root.contains("cpp") && root["cpp"].isObject()){
        QJsonObject cpp = root["cpp"].toObject();
        if(cpp.contains("member") && cpp["member"].isArray()){
            QJsonArray membersArray = cpp["member"].toArray();
            for (const QJsonValue &value : std::as_const(membersArray)) {
                QJsonObject obj = value.toObject();
                Cppmember member;
                member.Id  =  obj["id"].toString();
                member.Msec = obj["msec"].toInt();
                member.Min = obj["min"].toInt();
                member.Max = obj["max"].toInt();
                config.cppMembers.append(member);
            }
        }else{
            qWarning("cpp object is not define member array or member isn't arrray");;
            return -1;
        }
    }else{
        return -1;
    }
    return 1;
}

bool ParseJson::parseQmlmember(const QJsonObject &root){
    if( root.contains("QML") && root["QML"].isObject()){
        QJsonObject cpp = root["QML"].toObject();
        if(cpp.contains("member") && cpp["member"].isArray()){
            QJsonArray membersArray = cpp["member"].toArray();
            for (const QJsonValue &value : std::as_const(membersArray)) {
                QJsonObject obj = value.toObject();
                Qmlmember member;
                member.Id  =  obj["id"].toString();
                member.X = obj["x"].toInt();
                member.Y = obj["y"].toInt();
                member.color_Hex = obj["color_hex"].toString();
                member.dataSource = obj["dataSource"].toString();
                config.qmlMembers.append(member);
            }
        }else{
            qWarning("cpp object is not define member array or member isn't arrray");;
            return -1;
        }
        return 1;
    }
    return 1;
}
