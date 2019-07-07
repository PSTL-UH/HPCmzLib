#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

HEADER = DeconvolutionFeature.h                  \
	DeconvolutionFeatureWithMassesAndScans.h \
	IFilteringParams.h                       \
	FilteringParams.h                        \
	GeneratedMzSpectrum.h                    \
	GeneratedPeak.h                          \
	IIdentifications.h                       \
	MsDataFile.h                             \
	MsDataScan.h                             \
	SourceFile.h                             \
	SummedMsDataFile.h    


OBJ = 	DeconvolutionFeature.o                   \
	DeconvolutionFeatureWithMassesAndScans.o \
	IFilteringParams.o                       \
	FilteringParams.o                        \
	GeneratedMzSpectrum.o                    \
	GeneratedPeak.o                          \
	IIdentifications.o                       \
	MsDataFile.o                             \
	MsDataScan.o                             \
	SourceFile.o                             \
	SummedMsDataFile.o    


.SUFFIXES: .o.cpp

all:    
	make $(MZLIB_LIB) 
	cd Chromatogram ; make ; cd ..
	cd DataScan ; make ; cd ..
	cd Enums ; make ; cd ..
	cd MzSpectra ; make ; cd ..

GeneratedMzSpectrum.o: 	GeneratedMzSpectrum.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c GeneratedMzSpectrum.cpp	

SummedMsDataFile.o: 	SummedMsDataFile.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) $(CXXLOCALFLAGS) -c SummedMsDataFile.cpp	


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)




$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
	cd Chromatogram ; make clean ; cd ..
	cd Enums ; make clean ; cd ..
	cd MzSpectra ; make clean ; cd ..
