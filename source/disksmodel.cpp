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

QModelIndex DisksModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  // TODO

  return createIndex(row, column);
}

QModelIndex DisksModel::parent(const QModelIndex &child) const
{
  Q_UNUSED(child);

  return QModelIndex();
}

int DisksModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  // TODO

  return 0;
}