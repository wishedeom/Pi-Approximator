#!/bin/bash
> ./out/out01.txt
for i in {1..10}
do
    echo $(./bin/pi_approx_serial | cut -f 5 -d ' ')  >> ./out/out01.txt
done
