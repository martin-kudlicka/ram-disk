#ifndef DISKS_H
#define DISKS_H

class Disks
{
  public:
    struct Property
    {
      static const QString Group;
    };

    Disks();

    quintptr count  ()               const;
    MUuidPtr id     (quintptr index) const;
    bool     isEmpty()               const;

  private:
    QSettings _settings;
};

#endif