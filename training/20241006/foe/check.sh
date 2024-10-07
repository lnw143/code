for ((i=1; i<=1000; ++i))
do
./data > foe.in
time ./foe
./checker
if (($?!=0)); then break; fi
done