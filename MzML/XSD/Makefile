#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs

HEADER = mzML1.1.0.h                   \
	 	 mzML1.1.1_idx.h            

OBJ = 	mzML1.1.0.o                   \
	 	mzML1.1.1_idx.o            

.SUFFIXES: .o.cpp

all:    
	make $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c $<

clean:  
	rm -rf *.o *~
