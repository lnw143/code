@echo off
d:
cd code
git add .
git commit -m "%date% %time% By lnw143"
git push
pause