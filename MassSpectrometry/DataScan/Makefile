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
	IMsDataScanWithPrecursor.o \
	MsDataScan.o               \
	MsDataScanWithPrecursor.o


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
