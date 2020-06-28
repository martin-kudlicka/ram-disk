#ifndef DISKOPTIONS_H
#define DISKOPTIONS_H

class DiskOptions : public MSettings
{
  public:
    struct Property
    {
      static const QString Letter;
      static const QString Size;
    };

             DiskOptions(const MUuidPtr &id);
    virtual ~DiskOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    QChar    letter() const;
    quintptr size  () const;

    private:
      MUuidPtr _id;
};

#endif
