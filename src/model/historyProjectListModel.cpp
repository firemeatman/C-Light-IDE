#include "historyProjectListModel.h"

HistoryProjectListModel::HistoryProjectListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

QHash<int, QByteArray> HistoryProjectListModel::roleNames() const
{
    QHash<int, QByteArray> names = QAbstractItemModel::roleNames();
    names.insert(QHash<int, QByteArray>{
        {IDRole, "id"},
        {NameRole, "name"},
        {PathRole, "path"}
    });
    return names;
}

QVariant HistoryProjectListModel::headerData(int section,
                                             Qt::Orientation orientation,
                                             int role) const
{
    // FIXME: Implement me!
    return QVariant();
}

int HistoryProjectListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return historyProjectList.count();
}

QVariant HistoryProjectListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    HistoryProject item = historyProjectList.at(index.row());

    switch (role) {
    case RoleType::NameRole:
    {
        return item.name;
        break;
    }
    case RoleType::PathRole:
    {
        return item.rootPath;
        break;
    }
    default:
        break;
    }

    // FIXME: Implement me!
    return QVariant();
}

bool HistoryProjectListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool HistoryProjectListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

void HistoryProjectListModel::resetItems(QList<HistoryProject> &list)
{
    beginResetModel();
    this->historyProjectList.clear();
    this->historyProjectList.append(list);
    endResetModel();
}

void HistoryProjectListModel::insetItem(HistoryProject &item, int pos)
{
    QModelIndex parent;
    int row = 0;
    int size = historyProjectList.count();
    if(pos > size){
        return;
    }
    if(pos == -1 || pos < 0){
        row = size;
    }else{
        row = pos;
    }

    beginInsertRows(parent, row, row);
    this->historyProjectList.insert(pos, item);
    endInsertRows();

}

void HistoryProjectListModel::deleItem(int index)
{
    if(index > historyProjectList.count() || index < 0) return;

    QModelIndex parent;
    beginRemoveRows(parent, index, index);
    // FIXME: Implement me!
    endRemoveRows();
}
