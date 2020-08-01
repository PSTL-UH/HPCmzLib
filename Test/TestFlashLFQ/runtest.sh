#!/bin/bash
if [ ! -f "elements.dat" ]; then 
    ln -s ../../UsefulProteomicsDatabases/Datafiles/elements.dat
fi

echo " "
echo "  TestFlashLFQ"
make -s TestFlashLFQ
./TestFlashLFQ

