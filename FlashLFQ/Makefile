#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

HEADER = ChromatographicPeak.h         \
	DetectionType.h                \
	FlashLfqEngine.h               \
	FlashLFQResults.h              \
	Identification.h               \
	IndexedMassSpectralPeak.h      \
	IntensityNormalizationEngine.h \
	IsotopicEnvelope.h             \
	Ms1ScanInfo.h                  \
	PeakIndexingEngine.h           \
	Peptide.h                      \
	ProteinGroup.h                 \
	ProteinQuantificationEngine.h  \
	RetentionTimeCalibDataPoint.h  \
	SpectraFileInfo.h

OBJ = ChromatographicPeak.o         \
	DetectionType.o                \
	FlashLFQResults.o              \
	Identification.o               \
	IndexedMassSpectralPeak.o      \
	IntensityNormalizationEngine.o \
	IsotopicEnvelope.o             \
	Ms1ScanInfo.o                  \
	Peptide.o                      \
	ProteinGroup.o                 \
	ProteinQuantificationEngine.o  \
	RetentionTimeCalibDataPoint.o  \
	SpectraFileInfo.o              \
	FlashLfqEngine.o               \
	PeakIndexingEngine.o           


.SUFFIXES: .o.cpp

all:    
	cd BoundedNelderMeadOptimizer ; make ; cd ..
	cd SingularValueDecomposition ; make ; cd ..
	make $(MZLIB_LIB) 

$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(FLASHLFQ_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
	cd BoundedNelderMeadOptimizer ; make clean ; cd ..
	cd SingularValueDecomposition ; make clean ; cd ..
