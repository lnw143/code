@echo off
chcp 65001 > nul
cd /d D:\code
git add .
git status
echo Sure?
pause >nul
git commit -m "%date% %time% By lnw143"
git push
pause