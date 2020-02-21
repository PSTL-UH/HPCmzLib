#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../../Makefile.defs

HEADER = NelderMeadWithStartPoints.h \
	 IParameterSampler.h	     \
	 OptimizerResult.h	     \
	 ParameterType.h	     \
	 ParameterSampler.h	     


OBJ = 	 NelderMeadWithStartPoints.o  \
	 IParameterSampler.o	     \
	 OptimizerResult.o	     \
	 ParameterSampler.o	     

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
