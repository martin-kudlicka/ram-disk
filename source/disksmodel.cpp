#include "pch.h"
#include "disksmodel.h"

int DisksModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  return static_cast<int>(Column::Count);
}

QVariant DisksModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  Q_UNUSED(index);
  Q_UNUSED(role);

  // TODO

  return {};
}

QVariant DisksModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
  if (orientation == Qt::Orientation::Vertical || role != Qt::DisplayRole)
  {
    return QVariant();
  }

  switch (section)
  {
    case Column::Letter:
      return "Letter";
    case Column::Size:
      return "Size (MB)";
    default:
      Q_UNREACHABLE();
  }

  return QVariant();
}

QModelIndex DisksModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  if (_disks.isEmpty())
  {
    return createIndex(row, column);
  }

  return createIndex(row, column, _disks.id(row));
}

QModelIndex DisksModel::parent(const QModelIndex &child) const
{
  Q_UNUSED(child);

  return QModelIndex();
}

int DisksModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return _disks.count();
}