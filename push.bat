@echo off
for /d %%f in (*) do (
	rmdir /s /q "%%f/.vscode"
	rmdir /s /q "%%f/.cph"
)
del /s *.exe
del /s *.in
del /s *.out
del /s *.ans
del /s *.std
git add .
git commit -m "%date% %time% By lnw143"
git push
pause