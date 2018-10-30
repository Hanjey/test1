#!/bin/bash
echo "execute begin---------------"
rm -rf log/*
for((i=0;i<10;i++));
do
echo "execute $i times"
numactl -m 0 -N 0 ./dgemm 200 > log/log-$i.log 
done
echo "execute end----------------"
