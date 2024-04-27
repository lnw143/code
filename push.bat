@echo off
git status
echo Sure?
pause >nul
git add .
git commit -m "nothing By lnw143"
git push
pause