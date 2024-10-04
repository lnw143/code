for ((i=1; i<=1000; ++i))
do
./data > .in
./std < .in > .ans
./code < .in > .out
diff .ans .out -w
if (($?!=0)); then break; fi
done