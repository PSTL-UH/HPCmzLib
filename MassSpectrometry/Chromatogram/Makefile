#
# Copyright (c) 2019-2020      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
#
include ../../Makefile.defs

HEADER = Chromatogram.h                  \
	ChromatographicElutionProfile.h  \
	ChromatographicPeak.h

OBJ = 	Chromatogram.o                   \
	ChromatographicElutionProfile.o  \
	ChromatographicPeak.o


.SUFFIXES: .o.cpp

all:    
	$(MAKE) $(MZLIB_LIB)

Chromatogram.o:  Chromatogram.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c Chromatogram.cpp  

$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
