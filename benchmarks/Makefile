#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include Makefile.defs

CEXECS = Benchmark	   	     

.SUFFIXES: .cxx .h  

###################################################################################################

all: cxxtests 

cxxtests: $(CEXECS)


###################################################################################################
### CXXTESTS                                                                                      ###
###################################################################################################
Benchmark: Benchmark.o 
	$(CXX) $^ -o $@ $(LDFLAGS)


###################################################################################################


clean:
	rm -rf *.o *~

	rm -f Benchmark

