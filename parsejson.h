#ifndef PARSEJSON_H
#define PARSEJSON_H
#include <QString>
#include <QJsonObject>
struct Cppmember{
    QString Id;
    int Msec;
    int Min;
    int Max;
};

struct Qmlmember{
    QString Id;
    int X, Y;
    QString color_Hex;
    QString dataSource;
};

struct matchmember{
    QString Id_qml;
    int X, Y;
    QString color_Hex;

    QString Id_cpp;
    int Msec;
    int Min;
    int Max;
};

struct Config {
    QList<Cppmember> cppMembers;
    QList<Qmlmember> qmlMembers;

    QList<matchmember> member;
};



class ParseJson{
public:

    ParseJson(const QString &fileAddress);
    QList<matchmember>& get(){
        return config.member;
    }

private:
    Config config;
    bool parseCppmember(const QJsonObject &root);
    bool parseQmlmember(const QJsonObject &root);

};

#endif // PARSEJSON_H
