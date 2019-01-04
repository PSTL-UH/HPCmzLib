#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs

HEADER = AbsoluteTolerance.h              \
	ClassExtensions.h                 \
	DoubleRange.h                     \
	MzLibException.h                  \
	MzRange.h                         \
	PpmTolerance.h                    \
	Tolerance.h

#SystemInfo.h


OBJ = 	AbsoluteTolerance.o               \
	ClassExtensions.o                 \
	DoubleRange.o                     \
	MzLibException.o                  \
	MzRange.o                         \
	PpmTolerance.o                    \
	Tolerance.o

#	SystemInfo.o                      \


.SUFFIXES: .o.cpp

all:    
	make $(MZLIB_LIB) 


$(MZLIB_LIB): $(HEADER) $(OBJ) 
	$(AR) $(AR_FLAGS) $(MZLIB_LIB_DIR)/$(MZLIB_LIB) $(OBJ)

$(OBJ):	$(HEADER)
.cpp.o:	$(HEADER)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o *~
