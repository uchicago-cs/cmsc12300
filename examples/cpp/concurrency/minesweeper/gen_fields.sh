#!/bin/bash

SEED=42

SIZES="10 25"

PCTS="10 25 50 75 90"

mkdir -p minefields

for SIZE in $SIZES;
do
    for PCT in $PCTS;
    do
        FNAME="minefield_${SIZE}x${SIZE}_${PCT}pct.txt"
        echo $FNAME;
        ./fieldgen -x $SIZE -y $SIZE -p $PCT -s $SEED -f minefields/$FNAME
    done
done
