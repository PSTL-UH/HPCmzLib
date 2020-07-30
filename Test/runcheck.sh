#!/bin/bash
if [ ! -f "elements.dat" ]; then
    ln -s ../UsefulProteomicsDatabases/Datafiles/elements.dat .
fi

make TestElementsAndIsotopes -s
./TestElementsAndIsotopes > tt.out
str=$(wc -l tt.out)
str2="3 tt.out"
if [ "$str" = "$str2" ]; then
    echo "Pass"
    exit 0;
else
    echo "Fail"
fi

exit 1;

