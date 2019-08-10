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
echo "  TestFragments  "
make TestFragments
./TestFragments

echo " "
echo "  TestMetaMorpheus"
make TestMetaMorpheus
./TestMetaMorpheus

echo " "
echo "  TestSpecatr"
make TestSpectra
./TestSpectra
