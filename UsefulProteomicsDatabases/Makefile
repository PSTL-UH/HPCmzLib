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
	Loaders.h              \
	PeriodicTableLoader.h  \
	ProteinDbLoader.h      \
	ProteinDbWriter.h      \
	PtmListLoader.h        \
	UnimodLoader.h


OBJ =   DecoyType.o            \
	PeriodicTableLoader.o  

#	Loaders.o              \
#	ProteinDbLoader.o      \
#	ProteinDbWriter.o      \
#	PtmListLoader.o        \
#	UnimodLoader.o	

.SUFFIXES: .o.cpp

all:    
	make $(MZLIB_LIB) 

#	cd Generated ; make ; cd ..


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:  
	rm -rf *.o *~
