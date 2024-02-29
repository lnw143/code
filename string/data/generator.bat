generator.exe -n=1e2 -s=1e3 -from=0 -to=4 -balance
generator.exe -n=1e2 -s=1e3 -from=5 -to=9
generator.exe -n=1e3 -s=1e6 -from=10 -to=14 -balance
generator.exe -n=1e3 -s=1e6 -from=15 -to=19
generator.exe -n=1e3 -s=1e6 -from=20 -to=24 -hack -mid=100 -balance
generator.exe -n=1e3 -s=1e6 -from=25 -to=29 -hack -mid=100
generator.exe -n=1e4 -s=1e6 -from=30 -to=31 -balance
generator.exe -n=1e4 -s=1e6 -from=32 -to=33
generator.exe -n=1e4 -s=1e6 -from=34 -to=35 -hack -mid=100
generator.exe -n=1e4 -s=1e6 -from=36 -to=39 -hack -mid=100 -balance

for /l %%i in (0,1,9) do (std.exe < string0%%i.in > string0%%i.out)
for /l %%i in (10,1,39) do (std.exe < string%%i.in > string%%i.out)