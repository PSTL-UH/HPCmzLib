#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs

HEADER = IMsDataScan.h             \
	IMsDataScanWithPrecursor.h \
	MsDataScan.h               \
	MsDataScanWithPrecursor.h

OBJ = 	IMsDataScan.o              \
	IMsDataScanWithPrecursor.o 

LOCALOBJ = MsDataScan.o              \
	MsDataScanWithPrecursor.o


.SUFFIXES: .o.cpp

all:    
	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c MsDataScan.cpp
#	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c MsDataScanWithPrecursor.cpp
	make $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) $(LOCALOBJ)
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ) $(LOCALOBJ)

#$(OBJ):	$(HEADER)
#.cpp.o:	$(HEADER)
#	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
