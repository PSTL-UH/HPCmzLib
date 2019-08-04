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
	TestModifications		\
	TestFragments			\
	TestDigestionMotif		\
	TestMetaMorpheus                \
	TestPeptides			

#	FakeMsDataFile                       \
#	FixtureSetUp                         \
#	SpectrumProcessingAndFiltering       \
#	TestChromatogram                     \
#	TestIsolation                        \
#	TestMassMzCalculations               \
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
#
TestDigestionMotif: TestDigestionMotif.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
TestFragments: TestFragments.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
TestMetaMorpheus: TestMetaMorpheus.o 
	$(CXX) $^ -o $@ $(LDFLAGS)

###################################################################################################


clean:
	rm -rf *.o *~

	rm -f TestChemicalFormula TestElementsAndIsotopes TestDigestionMotif
	rm -f TestPeptides TestAminoAcids TestModifications TestFragments TestMetaMorpheus
