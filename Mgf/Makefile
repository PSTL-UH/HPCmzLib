#
# Copyright (c) 2019-2020      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
#
include ../Makefile.defs

HEADER =   Mgf.h 


OBJ =      Mgf.o 


.SUFFIXES: .o.cpp

all:    
	$(MAKE) $(MZLIB_LIB)


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c $<

clean:  
	rm -rf *.o *~
