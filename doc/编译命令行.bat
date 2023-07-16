set tmp_qmake_path=D:\Qt\Qt5.12.9\5.12.9\mingw73_64\bin;
set tmp_mingw_path=D:\Qt\Qt5.12.9\Tools\mingw730_64\bin;
set PATH=%tmp_qmake_path%%tmp_mingw_path%%PATH%

qmake bombtest.pro -spec win32-g++
mingw32-make qmake_all
mingw32-make -f Makefile.Release
cd release && windeployqt bombtest.exe