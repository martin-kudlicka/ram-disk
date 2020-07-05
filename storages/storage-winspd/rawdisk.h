#ifndef RAWDISK_H
#define RAWDISK_H

struct RawDisk
{
  SPD_STORAGE_UNIT        *storageUnit;
  const RamDiskParameters *parameters;
  LPBYTE                   data;

  RawDisk() : storageUnit(nullptr), data(nullptr)
  {
  }
  ~RawDisk()
  {
    if (data)
    {
      free(data);
    }
  }
};

#endif