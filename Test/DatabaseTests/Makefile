#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs

CEXECS = TestDatabaseLoaders    \
	TestProteinReader       \
	TestProteomicsReadWrite \
	TestVariantProtein




.SUFFIXES: .cxx .h  

###################################################################################################

all: cxxtests 

cxxtests: $(CEXECS)


###################################################################################################
### CXXTESTS                                                                                      ###
###################################################################################################
TestProteomicsReadWrite : TestProteomicsReadWrite.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#

TestProteinReader : TestProteinReader.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#

TestVariantProtein : TestVariantProtein.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#

TestDatabaseLoaders : TestDatabaseLoaders.o 
	$(CXX) $^ -o $@ $(LDFLAGS)
#

###################################################################################################


clean:
	rm -rf *.o *~
	rm -f TestDatabaseLoaders TestProteinReader TestProteomicsReadWrite TestVariantProtein
