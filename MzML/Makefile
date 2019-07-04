#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

HEADER = IMzmlScan.h              \
	 Mzml.h                   \
	 MzmlMethods.h            \
	 MzmlPeak.h               \
	 MzmlScan.h               \
	 MzmlScanWithPrecursor.h  \
	 MzmlSpectrum.h 

OBJ = 	 IMzmlScan.o              \
	 Mzml.o                   \
	 MzmlMethods.o            \
	 MzmlPeak.o               \
	 MzmlScan.o               \
	 MzmlScanWithPrecursor.o  \
	 MzmlSpectrum.o 


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
