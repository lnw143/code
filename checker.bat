@echo off
:sss
data.exe > .in
std.exe < .in > .ans
code.exe < .in > .out
fc .out .ans
if %errorlevel% == 0 goto sss