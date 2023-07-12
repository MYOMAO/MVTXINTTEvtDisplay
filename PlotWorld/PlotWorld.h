#ifndef __PlotWorld_H__
#define __PlotWorld_H__

// --- need to check all these includes...
#include <fun4all/SubsysReco.h>
#include <limits.h>
#include <cmath>
#include <fstream>  // std::fstream
#include <string>
#include <vector>
#include <map>
#include <g4main/PHG4VtxPoint.h>
#include <trackbase/ActsGeometry.h>
#include <TString.h>


class TTree;
class TFile;
class TH2F;
class TH3F;

class PdbParameterMap;
class PHCompositeNode;
class PHG4CylinderGeomContainer;
class PHG4HitContainer;
class PHHepMCGenEventMap;
class PHG4TruthInfoContainer;
class PHG4Hit;
class SvtxEvalStack;
//class TrkrClusterHitAssoc;
class TrkrHitSetContainer;
class TrkrHitTruthAssoc;

namespace HepMC
{
class GenEvent;
}

class PlotWorld : public SubsysReco
{
 public:
  PlotWorld(std::string filename, int Detector);

  int Init(PHCompositeNode *);
  int InitRun(PHCompositeNode *);
  int process_event(PHCompositeNode *);
  int End(PHCompositeNode *);
  //! The embedding ID for the HepMC subevent to be analyzed.
  //! embedding ID for the event
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background

  //
  //! The embedding ID for the HepMC subevent to be analyzed.
  //! embedding ID for the event
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background


  int load_nodes(PHCompositeNode* topNode);
//  int GetFELIXID(int LayerNum, int StaveNum);
//  int GetCableID(int LayerNum, int StaveNum);

 private:

  int DetectorType;
  TString DetName;

  ActsGeometry * m_tGeometry;

  PHG4CylinderGeomContainer *m_Geoms;
  PHG4CylinderGeomContainer *m_Geoms2;
  PHG4TruthInfoContainer *m_truthInfo;
 
  std::multimap<std::array<int,2>, int> CableNum;
  std::multimap<std::array<int,2>, int> FELIXNum;


	
};

#endif  // __PlotWorld_H__
