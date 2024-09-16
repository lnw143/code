for ((i=1; i<=1000; ++i))
do
./data > .in
./std < .in > .ans
./code < .in > .out
diff .ans .out
ret=$?
if [ ! $ret == 0 ]; then
sleep 10000
fi
done