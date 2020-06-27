#ifndef DISKOPTIONS_H
#define DISKOPTIONS_H

class DiskOptions : public MSettings
{
  public:
    struct Property
    {
      static const QString Size;
      static const QString Letter;
    };

             DiskOptions(const MUuidPtr &id);
    virtual ~DiskOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    private:
      MUuidPtr _id;
};

#endif
