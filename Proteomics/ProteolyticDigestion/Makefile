#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs



HEADER = CleavageSpecificity.h          \
	 InitiatorMethionineBehavior.h  \
	 ProteaseDictionary.h           \
	 ProteolyticPeptide.h           \
	 DigestionMotif.h               \
	 PeptideWithSetModifications.h  \
	 Protease.h                     \
	 DigestionParams.h              \
	 ProductTypeMethods.h           \
	 ProteinDigestion.h

OBJ =    CleavageSpecificity.o          \
	 InitiatorMethionineBehavior.o  \
	 ProteaseDictionary.o           \
	 ProteolyticPeptide.o           \
	 DigestionMotif.o               \
	 PeptideWithSetModifications.o  \
	 Protease.o                     \
	 DigestionParams.o              \
	 ProductTypeMethods.o           \
	 ProteinDigestion.o


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
