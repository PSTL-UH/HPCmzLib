#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs



HEADER = CompactPeptideBase.h          \
	 FragmentationTerminus.h       \
	 Product.h                     \
	 CompactPeptide.h              \
	 MatchedFragmentIon.h          \
	 ProductType.h                 \
	 DissociationTypeCollection.h  \
	 NeutralTerminusFragment.h     \
	 TerminusSpecificProductTypes.h

OBJ =    CompactPeptideBase.o          \
	 FragmentationTerminus.o       \
	 Product.o                     \
	 CompactPeptide.o              \
	 MatchedFragmentIon.o          \
	 ProductType.o                 \
	 DissociationTypeCollection.o  \
	 NeutralTerminusFragment.o     \
	 TerminusSpecificProductTypes.o


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
