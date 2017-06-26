@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
cl.exe -Zi code\win32-handmade.cpp User32.lib