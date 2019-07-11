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
	cd AminoAcidPolymer ; make ; cd ..
	cd Modifications ; make ; cd ..
	cd Protein ; make ; cd ..
	cd ProteolyticDigestion ; make ; cd ..
	cd Fragmentation ; make ; cd ..

#	cd RetentionTimePrediction ; make ; cd ..

clean:
	cd AminoAcidPolymer ; make clean; cd ..
	cd Fragmentation ; make clean; cd ..
	cd Modifications ; make clean; cd ..
	cd Protein ; make clean; cd ..
	cd ProteolyticDigestion ; make clean; cd ..

#	cd RetentionTimePrediction ; make clean; cd ..
