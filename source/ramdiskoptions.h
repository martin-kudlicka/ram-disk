#ifndef RAMDISKOPTIONS_H
#define RAMDISKOPTIONS_H

class RamDiskOptions : public MSettings
{
  public:
    struct Property
    {
      static const QString Enabled;
      static const QString Drive;
      static const QString Size;
      static const QString Storage;
    };

             RamDiskOptions(const MUuidPtr &id);
    virtual ~RamDiskOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    QString  drive  () const;
    bool     enabled() const;
    quintptr size   () const;
    QString  storage() const;

    private:
      MUuidPtr _id;
};

#endif
