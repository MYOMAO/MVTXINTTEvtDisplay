#!/bin/bash


source /opt/sphenix/core/bin/sphenix_setup.csh -n  ana.355

rm -r install

mkdir install
export MYINSTALL=$PWD/install/
export LD_LIBRARY_PATH=$MYINSTALL/lib:$LD_LIBRARY_PATH
export PATH=$MYINSTALL/bin:$PATH

#source $OPT_SPHENIX/bin/setup_local.csh $MYINSTALL
echo "Build trackbase_historic"


#cd trackbase_historic 

#autogen.sh --prefix=$MYINSTALL
#make
#make install

#cd ../


echo "-------------- BUILD main ------------------------"

cd PlotWorld/

#cd coresoftware/simulation/g4simulation/g4detectors/
autogen.sh --prefix=$MYINSTALL
make
make install


cd ../


export ROOT_INCLUDE_PATH=${PWD}/macros/common:$ROOT_INCLUDE_PATH

#echo "-------------- DONE CHANGING SOFTWARE NOW BRO --------------------"
