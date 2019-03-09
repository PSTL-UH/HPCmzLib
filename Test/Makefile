#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

CEXECS = ChemicalFormulaTestFixture	\
	ElementsAndIsotopesTests	\
	TestAminoAcids			\
	TestFragments			\
	TestModifications		\
	TestPeptides			\
	DatabaseLoaderTests	  	\
	FakeMsDataFile 		        \
	MassTestFixture		        \
	MyTests 			\
	SetUpTests	                \
	TestChromatogram		\
	TestDataFile			\
	TestIsolation			\
	TestMzML			\
	TestProteinReader		\
	TestProteomicsReadWrite		\
	TestRange			\
	TestSpectrap			\
	TestTolerance


.SUFFIXES: .cxx .h  

###################################################################################################

all: ctests 

cxxtests: $(CEXECS)


###################################################################################################
### CXXTESTS                                                                                      ###
###################################################################################################
ElementsAndIsotopesTests: ElementsAndIsotopesTests.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
ChemicalFormulaTestFixture: ChemicalFormulaTestFixture.o
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
