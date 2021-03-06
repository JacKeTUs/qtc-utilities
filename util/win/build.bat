@echo off

set SELF_PATH=%~dp0
call %SELF_PATH%\env.bat

set QTC_SOURCE=%cd%\qtcreator-latest\src
set QTC_BUILD=%cd%\qtcreator-latest\compiled

rmdir /s /q build
mkdir build

cd build
lrelease %SELF_PATH%\..\..\qtc-utilities.pro
qmake %SELF_PATH%\..\..
nmake
if %errorlevel% neq 0 exit /b %errorlevel%
cd ..


set /p VERSION=<qtcreator-latest\version
set PLUGIN_NAME=QtcUtilities

if not exist qtcreator-latest\compiled\lib\qtcreator\plugins\%PLUGIN_NAME%4.dll  exit /b 1

rd /Q /S dist
mkdir dist\lib\qtcreator\plugins
mkdir dist\share\qtcreator\translations
copy /Y qtcreator-latest\compiled\lib\qtcreator\plugins\%PLUGIN_NAME%4.dll dist\lib\qtcreator\plugins
if %errorlevel% neq 0 exit /b %errorlevel%
copy /Y %SELF_PATH%\..\..\translation\*.qm dist\share\qtcreator\translations

if exist %PLUGIN_NAME%-%VERSION%-win.zip del /Q %PLUGIN_NAME%-%VERSION%-win.zip
cd dist
7z a ..\%PLUGIN_NAME%-%VERSION%-win.zip *
cd ..

