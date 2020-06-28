#ifndef DISKOPTIONS_H
#define DISKOPTIONS_H

class DiskOptions : public MSettings
{
  public:
    struct Property
    {
      static const QString Enabled;
      static const QString Drive;
      static const QString Size;
      static const QString Storage;
    };

             DiskOptions(const MUuidPtr &id);
    virtual ~DiskOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    QString  drive()   const;
    bool     enabled() const;
    quintptr size  ()  const;

    private:
      MUuidPtr _id;
};

#endif
