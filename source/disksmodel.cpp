#include "pch.h"
#include "disksmodel.h"

void DisksModel::remove(const QModelIndex &index)
{
  removeRow(index.row());
}

int DisksModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  return static_cast<int>(Column::Count);
}

QVariant DisksModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole && role != Qt::CheckStateRole)
  {
    return QVariant();
  }

  auto rule = const_cast<Disks *>(&_disks)->get(index.internalId());

  switch (role)
  {
    case Qt::DisplayRole:
      switch (index.column())
      {
        case Column::Drive:
          return rule->options().drive();
        case Column::Size:
          return rule->options().size();
      }
      break;
    case Qt::CheckStateRole:
      switch (index.column())
      {
        case Column::Enabled:
          return rule->options().enabled() ? Qt::Checked : Qt::Unchecked;
      }
  }

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
    case Column::Enabled:
      return {};
    case Column::Drive:
      return "Drive";
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