# RAM Disk

Creates RAM disk of specified size (32 MB - 2 GB) with FAT32 filesystem and mounts it to selected drive letter.

![](https://raw.githubusercontent.com/martin-kudlicka/ram-disk/master/web/mainwindow.png)

## Description
This application is for the most part UI which provides memory block in user space to 3rd-party proxy driver.
After disk is created by the driver it's formated with FAT32 filesystem and mounted to selected drive letter (administrator rights are required for this action).
It's possible to minimize application to tray and start it minimized - application needs to stay running to keep RAM disk created and mounted.

## Usage
`RAMDisk.exe`

## Requirements
* Windows Vista (only original NTFS compression will work) or Windows 10 (for additional EXE methods)
* [Visual C++ Redistributable for Visual Studio 2019](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)
* [WinSpd · Windows Storage Proxy Driver](https://github.com/billziss-gh/winspd)

## Components
* [Qt](https://www.qt.io/)
