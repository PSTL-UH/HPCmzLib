#!/bin/bash
if [ ! -f "elements.dat" ]; then
    ln -s ../UsefulProteomicsDatabases/Datafiles/elements.dat .
fi

echo " "
echo "  TestElementsAndIsotopes"
make -s TestElementsAndIsotopes
./TestElementsAndIsotopes

echo " "
echo "  TestAminoAcids"
make -s TestAminoAcids
./TestAminoAcids

echo " "
echo "  TestChemicalFormula"
make -s TestChemicalFormula
./TestChemicalFormula

echo " "
echo "  TestModifications  "
make -s TestModifications
./TestModifications

echo " "
echo "  TestDigestionMotif  "
make -s TestDigestionMotif
./TestDigestionMotif

echo " "
echo "  TestPeptides  "
make -s TestPeptides
./TestPeptides

echo " "
echo "  TestPeptideWithSetMods  "
make -s TestPeptideWithSetMods
./TestPeptideWithSetMods

echo " "
echo "  TestFragments  "
make -s TestFragments
./TestFragments

echo " "
echo "  TestMetaMorpheus"
make -s TestMetaMorpheus
./TestMetaMorpheus

echo " "
echo "  TestSpectra"
make -s TestSpectra
./TestSpectra

echo " "
echo "  TestMzML"
make -s TestMzML
./TestMzML

echo " "
echo "  TestPtmListLoader"
make -s TestPtmListLoader
./TestPtmListLoader

echo " "
echo "  TestModFits"
make -s TestModFits
./TestModFits


echo " "
echo "  TestProteinProperties"
make -s TestProteinProperties
./TestProteinProperties

echo " "
echo "  TestProteinDigestion"
make -s TestProteinDigestion
./TestProteinDigestion


echo " "
echo "  TestMgf"
make -s TestMgf
./TestMgf

echo " "
echo "  TestSerialization"
make -s TestSerialization
./TestSerialization

cd DatabaseTests ; ./runtest.sh ; cd ..
cd TestFlashLFQ ; ./runtest.sh ; cd ..
