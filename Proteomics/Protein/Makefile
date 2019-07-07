#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs



HEADER =  DatabaseReference.h           \
	  Protein.h                     \
	  SequenceVariantDescription.h  \
	  SnpEffAnnotation.h            \
	  VariantApplication.h          \
	  DisulfideBond.h               \
	  ProteolysisProduct.h          \
	  SequenceVariation.h           \
	  SpliceSite.h

OBJ =     DatabaseReference.o           \
	  Protein.o                     \
	  SequenceVariantDescription.o  \
	  SnpEffAnnotation.o            \
	  VariantApplication.o          \
	  DisulfideBond.o               \
	  ProteolysisProduct.o          \
	  SequenceVariation.o           \
	  SpliceSite.o


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
