@REM @echo off
:while
data.exe
std.exe
G_Points_and_Comparison.exe
fc .out .ans
if %errorlevel% == 0 goto while
