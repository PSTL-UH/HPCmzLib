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
	DatabaseLoaderTests	  	\
	ElementsAndIsotopesTests	\
	FakeMsDataFile 		        \
	MassTestFixture		        \
	MyTests 			\
	SetUpTests	                \
	TestAminoAcids			\
	TestChromatogram		\
	TestDataFile			\
	TestFragments			\
	TestIsolation			\
	TestModifications		\
	TestMzML			\
	TestPeptides			\
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

ChemicalFormulaTestFixture: ChemicalFormulaTestFixture.o
	$(CXX) $^ -o $@ $(LDFLAGS)
#
DatabaseLoaderTests: DatabaseLoaderTests.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
ElementsAndIsotopesTests: ElementsAndIsotopesTests.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#
FakeMsDataFile: FakeMsDataFile.o 
	$(CXX) $^ -o $@ $(LDFLAGS)

###################################################################################################


clean:
	rm -rf *.o *~

	rm -f ChemicalFormulaTestFixture DatabaseLoaderTests ElementsAndIsotopesTests FakeMsDataFile
