#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

TableModel::TableModel(ListDataType pairs, QObject *parent)
    : QAbstractTableModel(parent)
{
    listOfPairs = pairs;
}

TableModel::~TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return listOfPairs.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if( false == index.isValid() )
    {
        return QVariant();
    }

    if( (index.row() >= listOfPairs.size() ) || (index.row() < 0) )
    {
        return QVariant();
    }

    if(Qt::DisplayRole == role)
    {
        DataType pair = listOfPairs.at( index.row() );

        if( 0 == index.column() )
        {
            return pair.first;
        }
        else if( 1 == index.column() )
        {
            return pair.second;
        }
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayPropertyRole != role)
    {
        return QVariant();
    }

    if(Qt::Horizontal == orientation)
    {
        switch(section)
        {
        case 0:
            return tr("Name");
        case 1:
            return tr("Address");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index )
{
    Q_UNUSED(index);

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; ++row)
    {
        DataType pair(" ", " ");
        listOfPairs.insert(position, pair);
    }
    endInsertRows();

    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);

    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; ++row)
    {
        listOfPairs.removeAt(position);
    }
    endRemoveRows();

    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        DataType p = listOfPairs.value(row);

        if(0 == index.column() )
        {
            p.first = value.toString();
        }
        else if(1 == index.column() )
        {
            p.second = value.toString();
        }
        else
        {
            return false;
        }

        listOfPairs.replace(row, p);
        emit( dataChanged(index, index) );

        return true;
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if( false == index.isValid() )
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

TableModel::ListDataType TableModel::getList()
{
    return listOfPairs;
}
