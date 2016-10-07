#!/bin/bash
for n in 2 4 6 8 10 12 14 16 18 20
do
    for i in {1..10}
    do
        echo "$(mpirun -np $n ./bin/pi_approx | cut -d ' ' -f 8)"  >> ./"out$n".txt
    done
done
