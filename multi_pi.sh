#!/bin/bash
> ./out.txt
echo "Processes     Time" >> ./out.txt
echo "====================" >> ./out.txt
for i in 2 4 6 8 10 12 14 16 18 20
do
    echo "$i            $(mpirun -np $i ./bin/pi_approx | cut -d ' ' -f 8)"  >> ./out.txt
done
