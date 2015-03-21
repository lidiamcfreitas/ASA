#!/bin/bash

for f in *time.txt
do
python3 readTime.py $f > csv_$f.csv;
done