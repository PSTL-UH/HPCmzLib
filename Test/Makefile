#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

CEXECS = TestChemicalFormula		\
	TestElementsAndIsotopes		\
	TestAminoAcids			\
	TestFragments			\
	TestModifications		\
	TestPeptides			

#	FakeMsDataFile                       \
#	FixtureSetUp                         \
#	SpectrumProcessingAndFiltering       \
#	TestChromatogram                     \
#	TestDigestionMotif                   \
#	TestIsolation                        \
#	TestMassMzCalculations               \
#	TestMetaMorpheus                     \
#	TestMgf                              \
#	TestModFits                          \
#	TestMsDataFile                       \
#	TestMzML                             \
#	TestPeptideWithSetMods               \
#	TestProductMassesMightHaveDuplicates \
#	TestProteinDigestion                 \
#	TestProteinProperties                \
#	TestPtmListLoader                    \
#	TestRangeAndTolerances               \
#	TestRetentionTimePrediction          \
#	TestSeqCoverage                      \
#	TestSpectra                          \
#	TestVariantProtein


.SUFFIXES: .cxx .h  

###################################################################################################

all: cxxtests 

cxxtests: $(CEXECS)


###################################################################################################
### CXXTESTS                                                                                      ###
###################################################################################################
TestElementsAndIsotopes: TestElementsAndIsotopes.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
TestChemicalFormula: TestChemicalFormula.o
	$(CXX) $^ -o $@ $(LDFLAGS)
#
TestAminoAcids: TestAminoAcids.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
TestModifications: TestModifications.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
TestPeptides: TestPeptides.o 
	$(CXX) $^ -o $@ $(LDFLAGS)


###################################################################################################


clean:
	rm -rf *.o *~

	rm -f ChemicalFormulaTestFixture DatabaseLoaderTests ElementsAndIsotopesTests FakeMsDataFile	   rm -f TestPeptides TestAminoAcids TestModifications
