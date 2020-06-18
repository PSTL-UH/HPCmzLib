#!/bin/bash

echo " "
echo "  TestElementsAndIsotopes"
make TestElementsAndIsotopes
./TestElementsAndIsotopes

echo " "
echo "  TestAminoAcids"
make TestAminoAcids
./TestAminoAcids

echo " "
echo "  TestChemicalFormula"
make TestChemicalFormula
./TestChemicalFormula

echo " "
echo "  TestModifications  "
make TestModifications
./TestModifications

echo " "
echo "  TestDigestionMotif  "
make TestDigestionMotif
./TestDigestionMotif

echo " "
echo "  TestPeptides  "
make TestPeptides
./TestPeptides

echo " "
echo "  TestPeptideWithSetMods  "
make TestPeptideWithSetMods
./TestPeptideWithSetMods

echo " "
echo "  TestFragments  "
make TestFragments
./TestFragments

echo " "
echo "  TestMetaMorpheus"
make TestMetaMorpheus
./TestMetaMorpheus

echo " "
echo "  TestSpectra"
make TestSpectra
./TestSpectra

echo " "
echo "  TestMzML"
make TestMzML
./TestMzML

echo " "
echo "  TestPtmListLoader"
make TestPtmListLoader
./TestPtmListLoader


#echo " "
#echo "  TestProteinProperties"
#make TestProteinProperties
#./TestProteinProperties

echo " "
echo "  TestProteinDigestion"
make TestProteinDigestion
./TestProteinDigestion

cd DatabaseTests ; ./runtest.sh ; cd ..
cd TestFlashLFQ ; ./runtest.sh ; cd ..
