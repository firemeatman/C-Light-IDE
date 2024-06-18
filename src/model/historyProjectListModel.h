#ifndef HISTORYPROJECTLISTMODEL_H
#define HISTORYPROJECTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

typedef struct HistoryProject_s{
    QString name;
    QString rootPath;
}HistoryProject;

class HistoryProjectListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit HistoryProjectListModel(QObject *parent = nullptr);

    virtual QHash<int, QByteArray> roleNames() const override;

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void resetItems(QList<HistoryProject>& list);
    void insetItem(HistoryProject& item, int pos); // pos: 插入位置，-1末尾插入,...
    void deleItem(int index);

private:
    enum RoleType
    {
        IDRole = Qt::UserRole,
        NameRole,
        PathRole
    };

    QList<HistoryProject> historyProjectList;

};

#endif // HISTORYPROJECTLISTMODEL_H
