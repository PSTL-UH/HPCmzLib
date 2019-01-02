#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs



HEADER = AminoAcidPolymer.h           \
	ChemicalFormulaFragment.h     \
	ChemicalFormulaModification.h \
	ChemicalFormulaTerminus.h     \
	DatabaseReference.h           \
	DigestionPoint.h              \
	DisulfideBond.h               \
	Fragment.h                    \
	FragmentTypes.h               \
	ModificationCollection.h      \
	Modification.h                \
	ModificationMotif.h           \
	ModificationSites.h           \
	ModificationWithLocation.h    \
	ModificationWithMassAndCf.h   \
	ModificationWithMass.h        \
	OldSchoolModification.h       \
	OldSchoolModificationWithMultiplePossibilities.h   \
	Peptide.h                     \
	Protein.h                     \
	ProteolysisProduct.h          \
	Proteomics.h                  \
	Residue.h                     \
	SequenceVariation.h           \
	Terminus.h                    \
	TerminusLocalization.h

OBJ = 	AminoAcidPolymer.o           \
	ChemicalFormulaFragment.o     \
	ChemicalFormulaModification.o \
	ChemicalFormulaTerminus.o     \
	DatabaseReference.o           \
	DigestionPoint.o              \
	DisulfideBond.o               \
	Fragment.o                    \
	FragmentTypes.o               \
	ModificationCollection.o      \
	Modification.o                \
	ModificationMotif.o           \
	ModificationSites.o           \
	ModificationWithLocation.o    \
	ModificationWithMassAndCf.o   \
	ModificationWithMass.o        \
	OldSchoolModification.o       \
	OldSchoolModificationWithMultiplePossibilities.o   \
	Peptide.o                     \
	Protein.o                     \
	ProteolysisProduct.o          \
	Proteomics.o                  \
	Residue.o                     \
	SequenceVariation.o           \
	Terminus.o                    \
	TerminusLocalization.o


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
