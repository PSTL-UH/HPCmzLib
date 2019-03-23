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
	cd MzLibUtil ; make ; cd ..
	cd Chemistry ; make ; cd ..
	cd Proteomics ; make ; cd ..
	cd Spectra ; make ; cd ..
	cd MassSpectrometry ; make ; cd ..
	cd UsefulProteomicsDatabases ; make ;  cd ..

$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	cd MzLibUtil ; make clean ; cd ..
	cd Chemistry ; make clean ; cd ..
	cd Proteomics ; make clean ; cd ..
	cd $(MZLIB_LIB_DIR) ; rm -f $(MZLIB_LIB) ; cd ..
	rm -rf *.o *~
