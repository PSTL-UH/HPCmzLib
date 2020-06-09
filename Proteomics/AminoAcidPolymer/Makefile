#
# Copyright (c) 2019      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs



HEADER = AminoAcidPolymer.h           \
	AminoAcidPolymerExtensions.h  \
	ChemicalFormulaFragment.h     \
	ChemicalFormulaModification.h \
	ChemicalFormulaTerminus.h     \
	DigestionPoint.h              \
	IProtease.h		      \
	Fragment.h                    \
	FragmentTypes.h               \
	ModificationCollection.h      \
	ModificationSites.h           \
	OldSchoolModification.h       \
	OldSchoolModificationWithMultiplePossibilities.h   \
	Peptide.h                     \
	Residue.h                     \
	Terminus.h                    

OBJ =   AminoAcidPolymer.o           \
	AminoAcidPolymerExtensions.o  \
	ChemicalFormulaFragment.o     \
	ChemicalFormulaModification.o \
	ChemicalFormulaTerminus.o     \
	DigestionPoint.o              \
	IProtease.o		      \
	Fragment.o                    \
	FragmentTypes.o               \
	ModificationCollection.o      \
	ModificationSites.o           \
	OldSchoolModification.o       \
	OldSchoolModificationWithMultiplePossibilities.o   \
	Peptide.o                     \
	Residue.o                     \
	Terminus.o                    


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
