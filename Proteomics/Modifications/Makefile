#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs



HEADER = Modification.h                \
	 ModificationLocalization.h    \
	 ModificationMotif.h           \
	 ModLocationOnPeptideOrProtein.h   

OBJ =   Modification.o                \
	ModificationLocalization.o    \
	ModificationMotif.o           \
	ModLocationOnPeptideOrProtein.o   


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
