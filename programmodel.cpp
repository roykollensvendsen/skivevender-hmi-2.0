#include "programmodel.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ProgramModel::ProgramModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QVariantMap result;

    readJsonFile(":/programs.json", result);

    QJsonDocument document = QJsonDocument::fromVariant(result);

    qDebug() << document["common"].isObject();
    qDebug() << document["programs"].isArray();

    QJsonArray array = document["programs"].toArray();

    foreach (const QJsonValue & v, array)
    {
        strings << v.toObject().value("name").toString();
    }
}

QVariant ProgramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug() << __FUNCTION__;

    // FIXME: Implement me!
}

int ProgramModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << __FUNCTION__;

    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return strings.size();
}

QVariant ProgramModel::data(const QModelIndex &index, int role) const
{
    qDebug() << __FUNCTION__;

    if (!index.isValid())
        return QVariant();

    if (role == NameRole) {
        return QVariant(strings[index.row()]);
    }

    return QVariant();
}

QHash<int, QByteArray> ProgramModel::roleNames() const
{
    qDebug() << __FUNCTION__;

    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

bool ProgramModel::readJsonFile(QString file_path, QVariantMap& result)
{
    // step 1
    QFile file_obj(file_path);
    if (!file_obj.open(QIODevice::ReadOnly)) {
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    auto json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()) {
        return false;
    }
    if (!json_doc.isObject()) {
        return false;
    }

    QJsonObject json_obj = json_doc.object();

    if (json_obj.isEmpty()) {
        return false;
    }

    result = json_obj.toVariantMap();
    return true;
}
