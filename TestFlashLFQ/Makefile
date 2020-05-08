#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

CEXECS = TestFlashLFQ

.SUFFIXES: .cxx .h  

###################################################################################################

all: cxxtests 

cxxtests: $(CEXECS)


###################################################################################################
### CXXTESTS                                                                                      ###
###################################################################################################
TestFlashLFQ: TestFlashLFQ.o 
TestFlashLFQ: TestFlashLFQ.o
	$(CXX) $(CXXFLAGS) -c ../Test/FakeMsDataFile.cpp
	$(CXX) $^ -o $@ FakeMsDataFile.o $(LDFLAGS)

###################################################################################################


clean:
	rm -rf *.o *~

	rm -f TestFlashLFQ
