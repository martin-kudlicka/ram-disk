#ifndef RAMDISKSMODEL_H
#define RAMDISKSMODEL_H

#include "ramdisks.h"

class RamDisksModel : public QAbstractItemModel
{
  public:
    enum class Column
    {
      Enabled,
      Drive,
      Size,
      Count
    };

    virtual ~RamDisksModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    void        insert (const MUuidPtr &id);
    RamDiskSPtr ramDisk(const MUuidPtr &id);
    void        remove (const QModelIndex &index);

  private:
    RamDisks _disks;

    virtual int         columnCount(const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
    virtual QVariant    data       (const QModelIndex &index, int role = Qt::DisplayRole)                 const Q_DECL_OVERRIDE;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent = QModelIndex())       const Q_DECL_OVERRIDE;
    virtual bool        insertRows (int row, int count, const QModelIndex &parent = QModelIndex())              Q_DECL_OVERRIDE;
    virtual QModelIndex parent     (const QModelIndex &child)                                             const Q_DECL_OVERRIDE;
    virtual bool        removeRows (int row, int count, const QModelIndex &parent = QModelIndex())              Q_DECL_OVERRIDE;
    virtual int         rowCount   (const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
};

#endif