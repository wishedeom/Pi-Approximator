#!/bin/bash
> rm ~comp428/a1/out/*.txt

for i in {1..10}
do
    echo $(~comp428/a1/bin/pi_approx_serial | cut -f 5 -d ' ')  >> ~comp428/a1/out/out01.txt
done

for n in 3 5 7 9 11 13 15 17 19
do
    for i in {1..10}
    do
        echo "$(mpirun -np $n ~comp428/a1/bin/pi_approx | cut -d ' ' -f 8)"  >> "~comp428/a1/out/out$n".txt
    done
done

