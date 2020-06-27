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
};

#endif
