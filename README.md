
#Change EvtGen Building Command: #

cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_STANDARD=17 -DCMAKE_INSTALL_PREFIX=/Your/Local/EventGen/Build/Folder -DHEPMC2_ROOT_DIR=/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/opt/sphenix/core/HepMC-2.06.11 -DEVTGEN_PHOTOS=OFF -DEVTGEN_TAUOLA=OFF -DEVTGEN_PYTHIA=ON -DHEPMC3_LIB=/sphenix/user/zshi/FastMLUConn/HFMLTriggerCodes/HepMC3Local/HepMC3/build/outputs/lib64/libHepMC3.so -DHEPMC3_ROOTIO_LIB=//sphenix/user/zshi/FastMLUConn/HFMLTriggerCodes/HepMC3Local/HepMC3/build/outputs/lib64/libHepMC3rootIO.so -DHEPMC3_ROOT_DIR=/sphenix/user/zshi/FastMLUConn/HFMLTriggerCodes/HepMC3Local/HepMC3/build/ -DHepMC3_DIR=/sphenix/user/zshi/FastMLUConn/HFMLTriggerCodes/HepMC3Local/HepMC3/build/share/HepMC3/cmake/ -DPHOTOSPP_ROOT_DIR=/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/opt/sphenix/core/PHOTOS-3.64_hepmc3-3.2.5_root-6.24.06 -DTAUOLAPP_ROOT_DIR=/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/opt/sphenix/core/TAUOLA-1.1.8_hepmc3-3.2.5_root-6.24.06 -DPYTHIA8_ROOT_DIR=/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/opt/sphenix/core/pythia8307_hepmc3-3.2.5_root-6.24.06 -DROOT_DIR=/cvmfs/sphenix.sdcc.bnl.gov/gcc-12.1.0/opt/sphenix/core/root-6.24.06/cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_SKIP_INSTALL_RPATH=ON -DCMAKE_SKIP_RPATH=ON -DCMAKE_VERBOSE_MAKEFILE=ON -DEVTGEN_BUILD_TESTS=OFF -DEVTGEN_BUILD_VALIDATIONS=OFF ../
