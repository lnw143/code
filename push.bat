@echo off
chcp 65001
cd /d D:\code
git add .
git commit -m "%date% %time% By lnw143"
git push
pause