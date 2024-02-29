@echo off
for /d %%f in (*) do (
	rmdir /s /q "%%f/.vscode"
	rmdir /s /q "%%f/.cph"
)
pause
del /s *.exe
del /s *.in
del /s *.out
del /s *.ans
del /s *.std
