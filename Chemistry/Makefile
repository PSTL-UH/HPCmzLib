#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

HEADER = ChemicalFormula.h                \
	ClassExtensions.h                 \
	Constants.h                       \
	Element.h                         \
	Isotope.h                         \
	IsotopicDistribution.h            \
	PeriodicTable.h


OBJ = 	Constants.o                      \
	Element.o                        \
	ChemicalFormula.o                \
	ClassExtensions.o                \
	Isotope.o                        \
	IsotopicDistribution.o           \
	PeriodicTable.o


.SUFFIXES: .o.cpp

all:    
	make $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(ADCL_LIB_DIR)/$(ADCL_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o *~
