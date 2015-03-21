#!/bin/bash

for f in *.txt
do
echo $f
for s in {1..20}
do
     { time ./main <$f >remove.txt; } 2>> $f.time.txt
done
done