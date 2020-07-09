#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include Makefile.defs

HEADER = exceptionhelper.h           \
	floating_point_to_integer.h  \
	Nullable.h                   \
	RectangularVectors.h         \
	stringbuilder.h              \
	stringhelper.h               \
	tangible_filesystem.h




.SUFFIXES: .o.cpp

all:    
	cd MzLibUtil ; $(MAKE) ; cd ..
	cd Chemistry ; $(MAKE) ; cd ..
	cd Spectra ; $(MAKE) ; cd ..
	cd MassSpectrometry ; $(MAKE) ; cd ..
	cd UsefulProteomicsDatabases ; $(MAKE) ;  cd ..
	cd Proteomics ; $(MAKE) ; cd ..
	cd MzML ; $(MAKE) ; cd ..
	cd FlashLFQ ; $(MAKE) ; cd ..
	cd pepXML ; $(MAKE) ; cd ..
	cd MzIdentML ; $(MAKE) ; cd ..
	cd Mgf ; $(MAKE) ; cd ..

$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	cd MzLibUtil ; $(MAKE) clean ; cd ..
	cd Chemistry ; $(MAKE) clean ; cd ..
	cd Spectra ; $(MAKE) clean ; cd ..
	cd MassSpectrometry ; $(MAKE) clean ; cd ..
	cd UsefulProteomicsDatabases ; $(MAKE) clean ;  cd ..
	cd Proteomics ; $(MAKE) clean ; cd ..
	cd MzML ; $(MAKE) clean ; cd ..
	cd FlashLFQ ; $(MAKE) clean ; cd ..
	cd pepXML ; $(MAKE) clean ; cd ..
	cd MzIdentML ; $(MAKE) clean ; cd ..
	cd Mgf ; $(MAKE) clean ; cd ..
	cd $(MZLIB_LIB_DIR) ; rm -f $(MZLIB_LIB) ; cd ..
	cd $(MZLIB_LIB_DIR) ; rm -f $(FLASHLFQ_LIB) ; cd ..
	rm -rf *.o *~
