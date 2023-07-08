#ifndef MACRO_FUN4ALLG4PI0_C
#define MACRO_FUN4ALLG4PI0_C

//#include <../src/pi0DecayEval.h>

#include <g4detectors/PHG4CylinderSubsystem.h>
#include <g4detectors/PHG4BlockSubsystem.h>

#include <g4main/PHG4ParticleGenerator.h>
#include <g4main/PHG4Reco.h>
#include <g4main/PHG4TruthSubsystem.h>

#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllDummyInputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <phool/recoConsts.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libg4testbench.so)
R__LOAD_LIBRARY(libg4detectors.so)
//R__LOAD_LIBRARY(libpi0DecayEval.so)

int Fun4All_G4_Pi0(const int nEvents = 10, int addEndcaps = 0)
{
  string outfile = "Fun4All_G4_Pi0";
  if(!addEndcaps) outfile += "_NoEndCaps";
  else outfile += "EndCaps";
  ///////////////////////////////////////////
  // Make the Server
  //////////////////////////////////////////
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(0);

  recoConsts *rc = recoConsts::instance();
  rc->set_IntFlag("RANDOMSEED", 12345);  // if you want to use a fixed seed
  // PHG4ParticleGenerator generates particle
  // distributions in eta/phi/mom range
  PHG4ParticleGenerator *gen = new PHG4ParticleGenerator("PGENERATOR");
  //gen->set_name("gamma");
  gen->set_name("pi0");
  //gen->set_name("eta");
  gen->set_vtx(0, 0, 0);
  //gen->set_eta_range(-0.05, +0.05);
  gen->set_eta_range(-1.2, +1.2);
  gen->set_mom_range(2, 20.0);
  gen->set_phi_range(0., 90. / 180. * TMath::Pi());  // 0-90 deg
  se->registerSubsystem(gen);

  PHG4Reco *g4Reco = new PHG4Reco();
  g4Reco->set_field(0);  // field off
  g4Reco->SetWorldMaterial("G4_Galactic");
  g4Reco->SetWorldSizeX(10.);
  g4Reco->SetWorldSizeZ(120.);
  g4Reco->SetWorldSizeY(10.);
  g4Reco->save_DST_geometry(false);  // no geometry -> crashes when trying to save it
//  g4Reco->set_decayer_active(false);

  PHG4CylinderSubsystem *cyl = new PHG4CylinderSubsystem("BH", 0);
  cyl->set_double_param("radius", 1.);
  if(nEvents >0)
    {
      cyl->set_string_param("material", "G4_Galactic");
      cyl->BlackHole();
    }
  else cyl->set_string_param("material", "G4_POLYSTYRENE");
  cyl->set_double_param("thickness", 0.01);
  cyl->set_double_param("length", 100);
  cyl->SetActive();
  g4Reco->registerSubsystem(cyl);


  if(addEndcaps)
    {
      PHG4BlockSubsystem *box = new PHG4BlockSubsystem("Rightside1");
      box->set_double_param("size_x",10);
      box->set_double_param("size_y",10.);
      box->set_double_param("size_z",1);
      box->set_double_param("place_x",0.);
      box->set_double_param("place_y",0.);
      box->set_double_param("place_z",50.);
      box->set_double_param("rot_x",180.);
      box->set_double_param("rot_y",180.);
      box->set_double_param("rot_z",180.);
      if(nEvents >0)
	{
	  box ->set_string_param("material", "G4_Galactic"); 
	  box -> BlackHole();
	}
      else box->set_string_param("material","G4_POLYSTYRENE"); // material of box
      box->SetActive(); // it is an active volume - save G4Hits
      g4Reco->registerSubsystem(box);

      PHG4BlockSubsystem *box2 = new PHG4BlockSubsystem("Leftside1");
      box2->set_double_param("size_x",10);
      box2->set_double_param("size_y",10.);
      box2->set_double_param("size_z",1);
      box2->set_double_param("place_x",0.);
      box2->set_double_param("place_y",0.);
      box2->set_double_param("place_z",-50.);
      box2->set_double_param("rot_x",180.);
      box2->set_double_param("rot_y",180.);
      box2->set_double_param("rot_z",180.);
      if(nEvents >0)
	{
	  box2 ->set_string_param("material", "G4_Galactic"); 
	  box2 -> BlackHole();
	}
      else box2->set_string_param("material","G4_POLYSTYRENE"); // material of box
      box2->SetActive(); // it is an active volume - save G4Hits
      g4Reco->registerSubsystem(box2);
    }
  PHG4TruthSubsystem *truth = new PHG4TruthSubsystem();
  g4Reco->registerSubsystem(truth);

 
  se->registerSubsystem(g4Reco);
 
 // pi0DecayEval *eval = new pi0DecayEval("decayEval",outfile  + "Eval.root");
 // se -> registerSubsystem(eval);
  

  if (outfile.c_str())
  {
    Fun4AllOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", outfile + ".root");
    se->registerOutputManager(out);
  }
  Fun4AllInputManager *in = new Fun4AllDummyInputManager("JADE");
  se->registerInputManager(in);
  if(nEvents == 0)
    {
      gROOT -> ProcessLine(".L DisplayOn.C");
      gROOT -> ProcessLine(Form("PHG4Reco *g4 = DisplayOn(\"vis.mac\",\"%s\")",outfile.c_str()));
    }
  else if(nEvents > 0)
  {
    se->run(nEvents);
    // finish job - close and save output files
    se->End();
    std::cout << "All done" << std::endl;

    // cleanup - delete the server and exit
    delete se;
    gSystem->Exit(0);
  }
  return 0;
}

PHG4ParticleGenerator *get_gen(const char *name = "PGENERATOR")
{
  Fun4AllServer *se = Fun4AllServer::instance();
  PHG4ParticleGenerator *pgun = (PHG4ParticleGenerator *) se->getSubsysReco(name);
  return pgun;
}

#endif
