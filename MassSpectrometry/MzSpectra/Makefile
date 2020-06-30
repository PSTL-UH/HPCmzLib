#
# Copyright (c) 2019-2020     University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
#
include ../../Makefile.defs

HEADER = IsotopicEnvelope.h \
	MzPeak.h \
	MzSpectrum.h

OBJ = 	IsotopicEnvelope.o \
	MzPeak.o \
	MzSpectrum.o


.SUFFIXES: .o.cpp

all:    
	$(MAKE) $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
