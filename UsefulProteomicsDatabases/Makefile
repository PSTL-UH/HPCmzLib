#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

HEADER =  DecoyType.h          \
	DecoyProteinGenerator.h	\
	Loaders.h              \
	PeriodicTableLoader.h  \
	FastaHeaderFieldRegex.h \
	ProteinDbLoader.h      \
	ProteinDbWriter.h      \
	PtmListLoader.h        \
	UnimodLoader.h


OBJ =   DecoyType.o            \
	DecoyProteinGenerator.o \
	PeriodicTableLoader.o  \
	FastaHeaderFieldRegex.o \
	ProteinDbLoader.o      \
	ProteinDbWriter.o      \
	UnimodLoader.o	

#	Loaders.o              \
#	PtmListLoader.o        \

.SUFFIXES: .o.cpp

all:  

	cd PSI-MOD.obo ; make ; cd ..
	cd unimod_2 ; make ; cd ..
	make $(MZLIB_LIB) 



$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
	cd PSI-MOD.obo ; make clean ; cd ..
	cd unimod_2 ; make clean ; cd ..
