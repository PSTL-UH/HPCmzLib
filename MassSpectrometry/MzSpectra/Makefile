#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs

HEADER = IMzPeak.h    \
	IMzSpectrum.h \
	IsotopicEnvelope.h \
	MzPeak.h \
	MzSpectrum.h

OBJ = 	IMzPeak.o    \
	IMzSpectrum.o \
	IsotopicEnvelope.o \
	MzPeak.o \
	MzSpectrum.o


.SUFFIXES: .o.cpp

all:    
	make $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
