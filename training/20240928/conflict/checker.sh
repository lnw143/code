for ((i=1; i<=7; ++i))
do
cat $i.in > conflict.in
./conflict
diff conflict.out $i.ans --ignore-all-space
if (($?!=0))
then
echo "WA on" $i
break
fi
done