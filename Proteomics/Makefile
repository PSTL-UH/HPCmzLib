#
# Copyright (c) 2018      University of Houston. All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#
include ../Makefile.defs



all:    
	cd AminoAcidPolymer ; $(MAKE) ; cd ..
	cd Modifications ; $(MAKE) ; cd ..
	cd Protein ; $(MAKE) ; cd ..
	cd ProteolyticDigestion ; $(MAKE) ; cd ..
	cd Fragmentation ; $(MAKE) ; cd ..

#	cd RetentionTimePrediction ; $(MAKE) ; cd ..

clean:
	cd AminoAcidPolymer ; $(MAKE) clean; cd ..
	cd Fragmentation ; $(MAKE) clean; cd ..
	cd Modifications ; $(MAKE) clean; cd ..
	cd Protein ; $(MAKE) clean; cd ..
	cd ProteolyticDigestion ; $(MAKE) clean; cd ..

#	cd RetentionTimePrediction ; $(MAKE) clean; cd ..
