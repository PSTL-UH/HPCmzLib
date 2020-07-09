#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs



HEADER =  CZE.h  SSRCalc3.h     

OBJ =     CZE.o  SSRCalc3.o     

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
