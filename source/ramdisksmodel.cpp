#include "pch.h"
#include "ramdisksmodel.h"

void RamDisksModel::insert(const MUuidPtr &id)
{
  auto row = _disks.index(id);

  insertRow(row);
}

RamDiskSPtr RamDisksModel::ramDisk(const MUuidPtr &id)
{
  return _disks.get(id);
}

RamDiskSPtr RamDisksModel::ramDisk(const QModelIndex &index)
{
  return _disks.get(index.internalId());
}

void RamDisksModel::remove(const QModelIndex &index)
{
  removeRow(index.row());
}

int RamDisksModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  return static_cast<int>(Column::Count);
}

QVariant RamDisksModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole && role != Qt::CheckStateRole)
  {
    return QVariant();
  }

  auto disk = const_cast<RamDisks *>(&_disks)->get(index.internalId());

  switch (role)
  {
    case Qt::DisplayRole:
      switch (index.column())
      {
        case Column::Drive:
          return disk->options().drive();
        case Column::Size:
          return disk->options().size();
      }
      break;
    case Qt::CheckStateRole:
      switch (index.column())
      {
        case Column::Enabled:
          return disk->options().enabled() ? Qt::Checked : Qt::Unchecked;
      }
  }

  return {};
}

Qt::ItemFlags RamDisksModel::flags(const QModelIndex &index) const
{
  auto itemFlags = QAbstractItemModel::flags(index);

  switch (index.column())
  {
    case Column::Enabled:
      itemFlags |= Qt::ItemIsUserCheckable;
  }

  return itemFlags;
}

QVariant RamDisksModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
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

QModelIndex RamDisksModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  if (_disks.isEmpty())
  {
    return createIndex(row, column);
  }

  return createIndex(row, column, _disks.id(row));
}

bool RamDisksModel::insertRows(int row, int count, const QModelIndex &parent /* QModelIndex() */)
{
  beginInsertRows(parent, row, row + count - 1);
  // already added
  endInsertRows();

  return true;
}

QModelIndex RamDisksModel::parent(const QModelIndex &child) const
{
  Q_UNUSED(child);

  return QModelIndex();
}

bool RamDisksModel::removeRows(int row, int count, const QModelIndex &parent /* QModelIndex() */)
{
  beginRemoveRows(parent, row, row + count - 1);

  _disks.removeIndex(row);

  endRemoveRows();

  return true;
}

int RamDisksModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return _disks.count();
}

bool RamDisksModel::setData(const QModelIndex &index, const QVariant &value, int role /* Qt::EditRole */)
{
  if (role != Qt::CheckStateRole)
  {
    return QAbstractItemModel::setData(index, value, role);
  }

  auto disk = _disks.get(index.internalId());

  switch (index.column())
  {
    case Column::Enabled:
      disk->options().setEnabled(value.toBool());

      // TODO

      emit dataChanged(index, index);

      return true;
    default:
      Q_UNREACHABLE();
  }

  return false;
}