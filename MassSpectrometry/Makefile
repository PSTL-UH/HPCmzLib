#
# Copyright (c) 2019-2020      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
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
	$(MAKE) $(MZLIB_LIB) 
	cd Chromatogram ; $(MAKE) ; cd ..
	cd Enums ; $(MAKE) ; cd ..
	cd MzSpectra ; $(MAKE) ; cd ..

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
	cd Chromatogram ; $(MAKE) clean ; cd ..
	cd Enums ; $(MAKE) clean ; cd ..
	cd MzSpectra ; $(MAKE) clean ; cd ..
