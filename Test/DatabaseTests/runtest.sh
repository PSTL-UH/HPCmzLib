#!/bin/bash

if [ ! -f "elements.dat" ]; then    
    ln -s ../../UsefulProteomicsDatabases/Datafiles/elements.dat .
fi

if [ ! -f "unimod_tables.xml" ]; then 
    ln -s ../../UsefulProteomicsDatabases/Datafiles/unimod_tables.xml .
fi

if [ ! -f "PSI-MOD.obo.xml" ]; then 
    ln -s ../../UsefulProteomicsDatabases/Datafiles/PSI-MOD.obo.xml .
fi

if [ ! -f "ptmlist.txt" ]; then
    ln -s ../../UsefulProteomicsDatabases/Datafiles/ptmlist.txt .
fi

echo " "
echo "  TestProteomicsReadWrite"
make -s TestProteomicsReadWrite
./TestProteomicsReadWrite

echo " "
echo "  TestDatabaseLoaders"
make -s TestDatabaseLoaders
./TestDatabaseLoaders

