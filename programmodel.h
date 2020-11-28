#ifndef PROGRAMMODEL_H
#define PROGRAMMODEL_H

#include <QAbstractListModel>

class ProgramModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ProgramModel(QObject *parent = nullptr);

    enum ProgramRoles {
        NameRole = Qt::UserRole + 1,
    };

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int,QByteArray> roleNames() const override;

private:
    bool readJsonFile(QString file_path, QVariantMap& result);

    QVector<QString> strings;
};

#endif // PROGRAMMODEL_H
