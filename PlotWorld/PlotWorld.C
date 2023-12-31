#include "PlotWorld.h"

#include <fun4all/Fun4AllReturnCodes.h>
#include <pdbcalbase/PdbParameterMap.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHTimeServer.h>
#include <phool/PHTimer.h>
#include <phool/getClass.h>

#include <phool/PHCompositeNode.h>

#include <g4main/PHG4Hit.h>
#include <g4main/PHG4HitContainer.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>

#include <trackbase/TrkrHitSetContainerv1.h>
#include <trackbase/TrkrHitTruthAssocv1.h>
#include <trackbase/TrkrClusterHitAssoc.h>
#include <trackbase/TrkrClusterHitAssocv3.h>
#include <trackbase/TrkrHitv2.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrClusterContainerv4.h>
#include <trackbase/TrkrClusterv4.h>

#include <mvtx/CylinderGeom_Mvtx.h>
#include <mvtx/MvtxClusterizer.h>
#include <trackbase/MvtxDefs.h>

#include <intt/CylinderGeomIntt.h>
#include <trackbase/InttDefs.h>

#include <g4detectors/PHG4Cell.h>
#include <g4detectors/PHG4CellContainer.h>
#include <g4detectors/PHG4CylinderCellGeom.h>
#include <g4detectors/PHG4CylinderCellGeomContainer.h>
#include <g4detectors/PHG4CylinderGeom.h>
#include <g4detectors/PHG4CylinderGeomContainer.h>

//#include <g4eval/SvtxEvalStack.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#pragma GCC diagnostic pop
#include <phhepmc/PHHepMCGenEvent.h>
#include <phhepmc/PHHepMCGenEventMap.h>

#include <TDatabasePDG.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TTree.h>

#include <trackbase/ActsSurfaceMaps.h>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

// bool DoClean;

using namespace std;

PlotWorld::PlotWorld(std::string filename, int DetType)
  : SubsysReco("PlotWorld")
  , m_run_clusterizer(false)
{
  cout << "Running - Detector Type - " << DetType << endl;

  DetectorType = DetType;

  //	DoClean = true;
  // Define Cable Number Map
  // Layer 0
  CableNum.insert({{0, 0}, 20});
  CableNum.insert({{0, 1}, 21});
  CableNum.insert({{0, 2}, 22});
  CableNum.insert({{0, 3}, 12});
  CableNum.insert({{0, 4}, 13});
  CableNum.insert({{0, 5}, 14});
  CableNum.insert({{0, 6}, 32});
  CableNum.insert({{0, 7}, 33});
  CableNum.insert({{0, 8}, 34});
  CableNum.insert({{0, 9}, 24});
  CableNum.insert({{0, 10}, 25});
  CableNum.insert({{0, 11}, 26});

  // Layer 1
  CableNum.insert({{1, 0}, 8});
  CableNum.insert({{1, 1}, 9});
  CableNum.insert({{1, 2}, 10});
  CableNum.insert({{1, 3}, 11});
  CableNum.insert({{1, 4}, 16});
  CableNum.insert({{1, 5}, 17});
  CableNum.insert({{1, 6}, 18});
  CableNum.insert({{1, 7}, 19});
  CableNum.insert({{1, 8}, 44});
  CableNum.insert({{1, 9}, 45});
  CableNum.insert({{1, 10}, 46});
  CableNum.insert({{1, 11}, 47});
  CableNum.insert({{1, 12}, 28});
  CableNum.insert({{1, 13}, 29});
  CableNum.insert({{1, 14}, 30});
  CableNum.insert({{1, 15}, 31});

  // Layer 2
  CableNum.insert({{2, 0}, 35});
  CableNum.insert({{2, 1}, 0});
  CableNum.insert({{2, 2}, 1});
  CableNum.insert({{2, 3}, 2});
  CableNum.insert({{2, 4}, 3});
  CableNum.insert({{2, 5}, 27});
  CableNum.insert({{2, 6}, 4});
  CableNum.insert({{2, 7}, 5});
  CableNum.insert({{2, 8}, 6});
  CableNum.insert({{2, 9}, 7});
  CableNum.insert({{2, 10}, 23});
  CableNum.insert({{2, 11}, 36});
  CableNum.insert({{2, 12}, 37});
  CableNum.insert({{2, 13}, 38});
  CableNum.insert({{2, 14}, 39});
  CableNum.insert({{2, 15}, 15});
  CableNum.insert({{2, 16}, 40});
  CableNum.insert({{2, 17}, 41});
  CableNum.insert({{2, 18}, 42});
  CableNum.insert({{2, 19}, 43});

  // Create FELIX Mapping Here
  // Layer 0
  FELIXNum.insert({{0, 0}, 0});
  FELIXNum.insert({{0, 1}, 0});
  FELIXNum.insert({{0, 2}, 1});
  FELIXNum.insert({{0, 3}, 1});
  FELIXNum.insert({{0, 4}, 2});
  FELIXNum.insert({{0, 5}, 2});
  FELIXNum.insert({{0, 6}, 3});
  FELIXNum.insert({{0, 7}, 3});
  FELIXNum.insert({{0, 8}, 4});
  FELIXNum.insert({{0, 9}, 4});
  FELIXNum.insert({{0, 10}, 5});
  FELIXNum.insert({{0, 11}, 5});

  // Layer 1
  FELIXNum.insert({{1, 0}, 5});
  FELIXNum.insert({{1, 1}, 5});
  FELIXNum.insert({{1, 2}, 5});
  FELIXNum.insert({{1, 3}, 0});
  FELIXNum.insert({{1, 4}, 0});
  FELIXNum.insert({{1, 5}, 1});
  FELIXNum.insert({{1, 6}, 1});
  FELIXNum.insert({{1, 7}, 1});
  FELIXNum.insert({{1, 8}, 2});
  FELIXNum.insert({{1, 9}, 2});
  FELIXNum.insert({{1, 10}, 2});
  FELIXNum.insert({{1, 11}, 3});
  FELIXNum.insert({{1, 12}, 3});
  FELIXNum.insert({{1, 13}, 4});
  FELIXNum.insert({{1, 14}, 4});
  FELIXNum.insert({{1, 15}, 4});

  // Layer 2
  FELIXNum.insert({{2, 0}, 4});
  FELIXNum.insert({{2, 1}, 4});
  FELIXNum.insert({{2, 2}, 4});
  FELIXNum.insert({{2, 3}, 5});
  FELIXNum.insert({{2, 4}, 5});
  FELIXNum.insert({{2, 5}, 5});
  FELIXNum.insert({{2, 6}, 0});
  FELIXNum.insert({{2, 7}, 0});
  FELIXNum.insert({{2, 8}, 0});
  FELIXNum.insert({{2, 9}, 0});
  FELIXNum.insert({{2, 10}, 1});
  FELIXNum.insert({{2, 11}, 1});
  FELIXNum.insert({{2, 12}, 1});
  FELIXNum.insert({{2, 13}, 2});
  FELIXNum.insert({{2, 14}, 2});
  FELIXNum.insert({{2, 15}, 2});
  FELIXNum.insert({{2, 16}, 3});
  FELIXNum.insert({{2, 17}, 3});
  FELIXNum.insert({{2, 18}, 3});
  FELIXNum.insert({{2, 19}, 3});
}

int PlotWorld::Init(PHCompositeNode* topNode)
{
  // std::cout << "Initial Bro" << std::endl;

  if (DetectorType == 0) DetName = "MVTX";
  if (DetectorType == 1) DetName = "INTT";
  m_run_clusterizer = true;

  // Basically Copy Pasted Codes Here

  // DONE

  return Fun4AllReturnCodes::EVENT_OK;
}

int PlotWorld::InitRun(PHCompositeNode* topNode)
{
  m_Geoms =
      findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_MVTX");
  if (!m_Geoms)
  {
    ////std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_MVTX" << std::endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }

  m_Geoms2 =
      findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_INTT");
  if (!m_Geoms2)
  {
    ////std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_INTT" << std::endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }

  m_truthInfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
  if (!m_truthInfo)
  {
    ////std::cout << PHWHERE << "ERROR: Can't find node G4TruthInfo" << std::endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }

  m_tGeometry = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
  if (!m_tGeometry)
  {
    cout << "HFMLTriggerInterface::InitRun - WARNING - missing m_tGeometry" << endl;
  }


  //Create a cluster container on the node tree
  auto trkrclusters = findNode::getClass<TrkrClusterContainer>(topNode, "TRKR_CLUSTER");
  if (!trkrclusters)
  {
    PHNodeIterator dstiter(topNode);
    PHCompositeNode *DetNode =
      dynamic_cast<PHCompositeNode *>(dstiter.findFirst("PHCompositeNode", "TRKR"));
    if (!DetNode)
      {
	DetNode = new PHCompositeNode("TRKR");
	topNode->addNode(DetNode);
      }

    trkrclusters = new TrkrClusterContainerv4;
    PHIODataNode<PHObject> *TrkrClusterContainerNode =
      new PHIODataNode<PHObject>(trkrclusters, "TRKR_CLUSTER", "PHObject");
    DetNode->addNode(TrkrClusterContainerNode);
  }

  //Now create a hit set container on the node tree as well for the clusteriser to pick up
  TrkrHitSetContainerv1 *trkrHitSetContainer = findNode::getClass<TrkrHitSetContainerv1>(topNode, "TRKR_HITSET");
  if (!trkrHitSetContainer)
  {
    PHNodeIterator dstiter(topNode);
    PHCompositeNode *DetNode = dynamic_cast<PHCompositeNode *>(dstiter.findFirst("PHCompositeNode", "TRKR"));
    if (!DetNode)
      {
	DetNode = new PHCompositeNode("TRKR");
	topNode->addNode(DetNode);
      }

    trkrHitSetContainer = new TrkrHitSetContainerv1;
    PHIODataNode<PHObject> *TrkrHitSetContainerNode = new PHIODataNode<PHObject>(trkrHitSetContainer, "TRKR_HITSET", "PHObject");
    DetNode->addNode(TrkrHitSetContainerNode);
  }

  //And finally create a hit/cluster association node (or else we'll crash)
  auto clusterhitassoc = findNode::getClass<TrkrClusterHitAssoc>(topNode,"TRKR_CLUSTERHITASSOC");
  if(!clusterhitassoc)
    {
      PHNodeIterator dstiter(topNode);
      PHCompositeNode *DetNode =
        dynamic_cast<PHCompositeNode *>(dstiter.findFirst("PHCompositeNode", "TRKR"));
      if (!DetNode)
	{
	  DetNode = new PHCompositeNode("TRKR");
	  topNode->addNode(DetNode);
	}

      clusterhitassoc = new TrkrClusterHitAssocv3;
      PHIODataNode<PHObject> *newNode = new PHIODataNode<PHObject>(clusterhitassoc, "TRKR_CLUSTERHITASSOC", "PHObject");
      DetNode->addNode(newNode);
    }

  // std::cout << "Basically Copy Paste Codes Here" << "    Again Det Type is = " << DetectorType << std::endl;

  if (DetectorType == 0)
  {
    int Index = 0;

    ifstream FileList("FileList.txt");
    string line;

    while (getline(FileList, line))
    {
      // TString infile = "/sphenix/u/xyu3/workarea/felix-mvtx/software/cpp/decoder_zhaozhong/fhrana_tree/20230627_Run20124_111x111_ZDC100Hz_Trg11kHz_DataRunConfig_MagOn_2mrad/fhrana_20230627_Run20124_111x111_ZDC100Hz_Trg11kHz_DataRunConfig_MagOn_2mrad_FEEID8704.root";

      // TString infile = line;

      cout << "Now Processing MVTX File Index: " << Index << "     Name: " << line.c_str() << endl;

      int event;
      int Nhits;
      int NStrobehits;

      //			Long_t BCO;
      //			int64_t Strobe_BCO;
      //			int Strobe_Index;

      int HeaderFEEID;
      int HeaderStaveID;
      int HeaderLayerID;

      ULong_t BCONew;
      UShort_t BCNew;
      ULong_t StrobeIDNew;
      int StrobeNum;

      ULong_t L1TrigBCONew;
      bool L1TrigNew;

      vector<int>* Stave_hit = 0;
      vector<int>* Layer_hit = 0;
      vector<int>* RowID_hit = 0;
      vector<int>* ColumnID_hit = 0;
      vector<int>* ChipID_hit = 0;
      vector<int>* FEEID_hit = 0;

      TFile* fin = new TFile(line.c_str());
      fin->cd();

      // TTree * tree_fhrana = (TTree *) fin->Get("tree_fhrana");

      TTree* tree_fhrana = (TTree*) fin->Get("tree_fhrana");  // Use old for now

      tree_fhrana->SetBranchAddress("event", &event);
      tree_fhrana->SetBranchAddress("Nhits", &Nhits);
      // tree_fhrana->SetBranchAddress("Strobe_BCO",&Strobe_BCO);
      // tree_fhrana->SetBranchAddress("Strobe_Index",&Strobe_Index);
      tree_fhrana->SetBranchAddress("NStrobehits", &NStrobehits);

      tree_fhrana->SetBranchAddress("HeaderFEEID", &HeaderFEEID);
      tree_fhrana->SetBranchAddress("HeaderStaveID", &HeaderStaveID);
      tree_fhrana->SetBranchAddress("HeaderLayerID", &HeaderLayerID);

      tree_fhrana->SetBranchAddress("RowID_hit", &RowID_hit);
      tree_fhrana->SetBranchAddress("ColumnID_hit", &ColumnID_hit);
      tree_fhrana->SetBranchAddress("ChipID_hit", &ChipID_hit);
      tree_fhrana->SetBranchAddress("Stave_hit", &Stave_hit);
      tree_fhrana->SetBranchAddress("Layer_hit", &Layer_hit);
      tree_fhrana->SetBranchAddress("FEEID_hit", &FEEID_hit);

      tree_fhrana->SetBranchAddress("BCO", &BCONew);
      tree_fhrana->SetBranchAddress("BC", &BCNew);
      tree_fhrana->SetBranchAddress("StrobeID", &StrobeIDNew);
      tree_fhrana->SetBranchAddress("StrobeNum", &StrobeNum);
      tree_fhrana->SetBranchAddress("L1TrigBCO", &L1TrigBCONew);
      tree_fhrana->SetBranchAddress("L1Trig", &L1TrigNew);

      int NEvents = tree_fhrana->GetEntries();

      // NEvents = 10000;

      int EventID;
      int NumberHits;

      int64_t Strobe_BCO_Save;
      int Strobe_Index_Save;
      int64_t Strobe_ID_Save;

      std::vector<int> HitID;
      std::vector<int> StaveID;
      std::vector<int> LayerID;
      std::vector<int> ChipID;
      std::vector<int> RowID;
      std::vector<int> ColID;
      std::vector<int> FEEID;
      std::vector<int> CableID;
      std::vector<int> FELIXID;

      std::vector<float> GlobalX;
      std::vector<float> GlobalY;
      std::vector<float> GlobalZ;

      std::vector<float> LocalX;
      std::vector<float> LocalY;
      std::vector<float> LocalZ;

      std::vector<float> ChipGlobalX;
      std::vector<float> ChipGlobalY;
      std::vector<float> ChipGlobalZ;
      std::vector<int> nAdjPixels;

      // std::cout << "Pass 4" << std::endl;
      /*
         std::vector<long int> * StrobeTimeOrb = 0;
         std::vector<long int> * StrobeBCOID = 0;

         TTree * HBInfoTree = (TTree *) fin->Get("HBInfoTree");

         HBInfoTree->SetBranchAddress("StrobeTimeOrb",&StrobeTimeOrb);
         HBInfoTree->SetBranchAddress("StrobeBCOID",&StrobeBCOID);
         */

      int HeaderCableIDSave;
      int HeaderFELIXIDSave;
      int HeaderFEEIDSave;
      int Strobe_BC_Save;

      int64_t L1TrigBCOSave;
      bool L1TrigSave;

      int NStrobehitsSave;

      TFile* fout = new TFile(Form("OutFile/MVTX/3DHitTree_%d.root", Index), "RECREATE");
      fout->cd();

      TTree* PixelWorldTree = new TTree("MVTXPixelTree", "MVTXPixelTree");

      PixelWorldTree->Branch("EventID", &EventID);
      PixelWorldTree->Branch("Strobe_ID", &Strobe_ID_Save);
      PixelWorldTree->Branch("Strobe_BCO", &Strobe_BCO_Save);
      PixelWorldTree->Branch("Strobe_Index", &Strobe_Index_Save);
      PixelWorldTree->Branch("Strobe_BC", &Strobe_BC_Save);

      PixelWorldTree->Branch("L1TrigBCOSave", &L1TrigBCOSave);
      PixelWorldTree->Branch("L1TrigSave", &L1TrigSave);

      PixelWorldTree->Branch("HeaderFEEID", &HeaderFEEIDSave);
      PixelWorldTree->Branch("HeaderCableID", &HeaderCableIDSave);
      PixelWorldTree->Branch("HeaderFELIXID", &HeaderFELIXIDSave);

      PixelWorldTree->Branch("NumberHits", &NumberHits);
      PixelWorldTree->Branch("NStrobeHits", &NStrobehitsSave);

      PixelWorldTree->Branch("HitID", &HitID);
      PixelWorldTree->Branch("StaveID", &StaveID);
      PixelWorldTree->Branch("FEEID", &FEEID);

      PixelWorldTree->Branch("FELIXID", &FELIXID);
      PixelWorldTree->Branch("CableID", &CableID);

      PixelWorldTree->Branch("LayerID", &LayerID);
      PixelWorldTree->Branch("ChipID", &ChipID);
      PixelWorldTree->Branch("RowID", &RowID);
      PixelWorldTree->Branch("ColID", &ColID);
      PixelWorldTree->Branch("nAdjPixels", &nAdjPixels);

      PixelWorldTree->Branch("GlobalX", &GlobalX);
      PixelWorldTree->Branch("GlobalY", &GlobalY);
      PixelWorldTree->Branch("GlobalZ", &GlobalZ);

      PixelWorldTree->Branch("LocalX", &LocalX);
      PixelWorldTree->Branch("LocalY", &LocalY);
      PixelWorldTree->Branch("LocalZ", &LocalZ);

      PixelWorldTree->Branch("ChipGlobalX", &ChipGlobalX);
      PixelWorldTree->Branch("ChipGlobalY", &ChipGlobalY);
      PixelWorldTree->Branch("ChipGlobalZ", &ChipGlobalZ);

      if (m_run_clusterizer)
      {
        PixelWorldTree->Branch("ClusLayer", &ClusLayer);
        PixelWorldTree->Branch("ClusX", &ClusX);
        PixelWorldTree->Branch("ClusY", &ClusY);
        PixelWorldTree->Branch("ClusZ", &ClusZ);
        PixelWorldTree->Branch("nPixInCluster", &ClusSize);
        PixelWorldTree->Branch("ClusSize_phi", &ClusSize_phi);
        PixelWorldTree->Branch("ClusSize_z", &ClusSize_z);
      }

      // NEvents = 10000000;
      for (int i = 0; i < NEvents; i++)
      {
        //As we're in InitRun and not process event, we should reset the 3 containers I made
        trkrclusters->Reset();
        trkrHitSetContainer->Reset();
        clusterhitassoc->Reset();

        tree_fhrana->GetEntry(i);

        if (i % 100000 == 0) std::cout << "Now Working on Event = " << i << std::endl;

        EventID = event;
        NumberHits = Nhits;
        NStrobehitsSave = NStrobehits;
        //	Strobe_BCO_Save = Strobe_BCO;
        //	Strobe_Index_Save = Strobe_Index;
        //	Strobe_Index_Save = 0;
        //	BCO = StrobeTimeOrb->at(0);

        HeaderFEEIDSave = HeaderFEEID;

        std::array<int, 2> StaveLocator2 = {HeaderLayerID, HeaderStaveID};
        HeaderCableIDSave = -1;
        if (CableNum.find(StaveLocator2) != CableNum.end()) HeaderCableIDSave = CableNum.find(StaveLocator2)->second;
        HeaderFELIXIDSave = -1;
        if (FELIXNum.find(StaveLocator2) != CableNum.end()) HeaderFELIXIDSave = FELIXNum.find(StaveLocator2)->second;

        /*

           if(StrobeTimeOrb->size() > 0){
           Strobe_BCO_Save = StrobeTimeOrb->at(0);
           Strobe_ID_Save = StrobeBCOID->at(0);

           }else{

           std::cout << "LIFE SUCK: StrobeTimeOrb.size() = " << StrobeTimeOrb->size() << std::endl;
           }
           */
        // Use New Data Format by Strobe//

        Strobe_ID_Save = StrobeIDNew;
        Strobe_BCO_Save = BCONew;
        Strobe_BC_Save = BCNew;
        Strobe_Index_Save = StrobeNum;

        L1TrigSave = L1TrigNew;
        L1TrigBCOSave = L1TrigBCONew;

        int NActualHits = ColumnID_hit->size();

        // if(Nhits != NActualHits) continue;

        Nhits = NActualHits;  // Resolve for now, just for now

        //TrkrHitSetContainerv1 *trkrHitSetContainer = new TrkrHitSetContainerv1();

        for (int j = 0; j < Nhits; j++)
        {
          // Hao-Ren Algorithm: Do Isolated Pixel Rejection//

          /*
          bool isIsolatedPixel = true;
          // loop over hits to check if the pixel is isolated
          for (int k = 0; k < Nhits; k++)
          {
                  if (j == k)
                          continue;

                  // check if the pixel is isolated
                  if (abs(ColumnID_hit->at(j) - ColumnID_hit->at(k)) <= 1 && abs(RowID_hit->at(j) - RowID_hit->at(k)) <= 1)
                  {
                          isIsolatedPixel = false;
                          break;
                  }
          }

          if (isIsolatedPixel)
                  continue;
          */

          int NClus = 1;

          for (int k = 0; k < Nhits; k++)
          {
            if (j == k)
              continue;

            // check if the pixel is isolated
            if (abs(ColumnID_hit->at(j) - ColumnID_hit->at(k)) <= 1 && abs(RowID_hit->at(j) - RowID_hit->at(k)) <= 1)
            {
              // isIsolatedPixel = false;
              NClus = NClus + 1;
              // break;
            }
          }

          HitID.push_back(j);
          nAdjPixels.push_back(NClus);
          StaveID.push_back(Stave_hit->at(j));
          LayerID.push_back(Layer_hit->at(j));
          ChipID.push_back(ChipID_hit->at(j));

          RowID.push_back(RowID_hit->at(j));
          ColID.push_back(ColumnID_hit->at(j));

          FEEID.push_back(FEEID_hit->at(j));

          uint8_t NowChip = ChipID_hit->at(j);
          int NowColChip = int(ColumnID_hit->at(j)) / 1024;
          int NowCol = ColumnID_hit->at(j) - NowColChip * 1024;
          int NowRow = RowID_hit->at(j);
          uint8_t NowLayer = Layer_hit->at(j);
          uint8_t NowStave = Stave_hit->at(j);
          auto hitsetkey = MvtxDefs::genHitSetKey(NowLayer, NowStave, NowChip, 0);
          TrkrHitSetContainer::Iterator hitsetit = trkrHitSetContainer->findOrAddHitSet(hitsetkey);
          
          if (m_run_clusterizer)
          {
            // generate the key for this hit
            TrkrDefs::hitkey hitkey = MvtxDefs::genHitKey(NowCol, NowRow);
            // See if this hit already exists
	    TrkrHit* hit = nullptr;
            hit = hitsetit->second->getHit(hitkey);
            if (!hit)
            {
              // Otherwise, create a new one
              hit = new TrkrHitv2();
              hitsetit->second->addHitSpecificKey(hitkey, hit);
            }
          }

          //					unsigned int ReGetChip = MvtxDefs::getChipId(hitsetkey);
          //					unsigned int ReGetStave = MvtxDefs::getStaveId(hitsetkey);

          ////std::cout << "Validation: " << hitsetkey  << "   ChipID = " << NowChip << "      ReGetChip = " << ReGetChip << "  Stave = " <<  Stave_hit->at(j) << "     ReGetStave = " << ReGetStave << "   LayerID = " << Layer_hit->at(j)    << std::endl;
          int GoodLayer = Layer_hit->at(j);

          // geom->find_strip_center_localcoords(NowLadderZID,strip_y,strip_x,local);

          CylinderGeom_Mvtx* geom = dynamic_cast<CylinderGeom_Mvtx*>(m_Geoms->GetLayerGeom(GoodLayer));

          auto surface = m_tGeometry->maps().getSiliconSurface(hitsetkey);

          TVector3 local_coords = geom->get_local_coords_from_pixel(NowRow, NowCol);
          double world_coords[3];
          geom->find_sensor_center(surface, m_tGeometry, world_coords);

          TVector2 LocalUse;
          LocalUse.SetX(local_coords.x());
          LocalUse.SetY(local_coords.z());

          TVector3 PixelWorld = geom->get_world_from_local_coords(surface, m_tGeometry, LocalUse);

          float PixelGlobalX = PixelWorld.x();
          float PixelGlobalY = PixelWorld.y();
          float PixelGlobalZ = PixelWorld.z();

          GlobalX.push_back(PixelGlobalX);
          GlobalY.push_back(PixelGlobalY);
          GlobalZ.push_back(PixelGlobalZ);

          LocalX.push_back(local_coords.x());
          LocalY.push_back(local_coords.y());
          LocalZ.push_back(local_coords.z());

          ChipGlobalX.push_back(world_coords[0]);
          ChipGlobalY.push_back(world_coords[1]);
          ChipGlobalZ.push_back(world_coords[2]);

          std::array<int, 2> StaveLocator = {Layer_hit->at(j), Stave_hit->at(j)};
          int CableNow = -1;

          if (CableNum.find(StaveLocator) != CableNum.end()) CableNow = CableNum.find(StaveLocator)->second;

          int FELIXNow = -1;

          if (FELIXNum.find(StaveLocator) != FELIXNum.end()) FELIXNow = FELIXNum.find(StaveLocator)->second;

          // Checking if there is any error in locating the MVTX staves
          if (CableNow == -1) cout << "Error Found: No Cable ID for the Input Stave!! Stave ID = " << Stave_hit->at(j) << "   LayerID == " << Layer_hit->at(j) << endl;
          if (FELIXNow == -1) cout << "Error Found: No FELIX ID for the Input Stave!! Stave ID = " << Stave_hit->at(j) << "   LayerID == " << Layer_hit->at(j) << endl;

          CableID.push_back(CableNow);
          FELIXID.push_back(FELIXNow);
        }

        //Now make clusters
	if (m_run_clusterizer)
        {
          MvtxClusterizer myClusterizer;
	  myClusterizer.process_event(topNode);
        }
  
        TrkrHitSetContainer::ConstRange hitsetrange = trkrHitSetContainer->getHitSets(TrkrDefs::TrkrId::mvtxId);

        for (TrkrHitSetContainer::ConstIterator hitsetitr = hitsetrange.first; hitsetitr != hitsetrange.second; ++hitsetitr)
        {
          TrkrHitSet *hitset = hitsetitr->second; // hitset : map <TrkrDefs::hitkey, TrkrHit>
          auto hitsetkey = hitset->getHitSetKey();

          int layer = TrkrDefs::getLayer(hitsetkey);
          auto surface = m_tGeometry->maps().getSiliconSurface(hitsetkey);
	  auto layergeom = dynamic_cast<CylinderGeom_Mvtx *>(m_Geoms->GetLayerGeom(layer));
          TVector2 LocalUse;

          TrkrClusterContainer::ConstRange clusterrange = trkrclusters->getClusters(hitsetkey);

          for (TrkrClusterContainer::ConstIterator clusteritr = clusterrange.first; clusteritr != clusterrange.second; ++clusteritr)
          {
            TrkrCluster *cluster = clusteritr->second;

            LocalUse.SetX(cluster->getLocalX());
            LocalUse.SetY(cluster->getLocalY());
            TVector3 ClusterWorld = layergeom->get_world_from_local_coords(surface, m_tGeometry, LocalUse);
            
            ClusLayer.push_back(layer);
            ClusX.push_back(ClusterWorld.X());
            ClusY.push_back(ClusterWorld.Y());
            ClusZ.push_back(ClusterWorld.Z());
            ClusSize.push_back(cluster->getAdc());
            ClusSize_phi.push_back(cluster->getPhiSize());
            ClusSize_z.push_back(cluster->getZSize());
          }
        }

        // HeaderCableID = CableID.at(0);
        // HeaderFELIXID = FELIXID.at(0);
        // HeaderFEEID = FEEID.at(0);

        PixelWorldTree->Fill();

        HitID.clear();
        StaveID.clear();
        LayerID.clear();
        CableID.clear();
        FELIXID.clear();

        nAdjPixels.clear();

        ChipID.clear();
        RowID.clear();
        ColID.clear();

        FEEID.clear();

        GlobalX.clear();
        GlobalY.clear();
        GlobalZ.clear();

        LocalX.clear();
        LocalY.clear();
        LocalZ.clear();

        ChipGlobalX.clear();
        ChipGlobalY.clear();
        ChipGlobalZ.clear();

        ClusLayer.clear();
        ClusX.clear();
        ClusY.clear();
        ClusZ.clear();
        ClusSize.clear();
        ClusSize_phi.clear();
        ClusSize_z.clear();
      }

      fout->cd();

      PixelWorldTree->Write();

      fout->Close();

      Index = Index + 1;
    }
  }

  if (DetectorType == 1)
  {
    ifstream FileList("INTTFileList.txt");
    string line;

    int Index = 0;

    while (getline(FileList, line))
    {
      cout << "Now Processing INTT File Index: " << Index << "     Name: " << line.c_str() << endl;

      int evtSeq;
      int fNhits;

      int chip_id[10000];
      int ladder[10000];
      int arm[10000];
      int bco[10000];
      Long64_t bco_full[10000];
      int module[10000];
      int chan_id[10000];
      int layer[10000];
      int barrel[10000];

      Long64_t bco_event;
      double TimeCal;  // Time in second

      TFile* fin = new TFile(line.c_str());
      fin->cd();

      TTree* tree = (TTree*) fin->Get("tree");

      tree->SetBranchAddress("evtSeq", &evtSeq);
      tree->SetBranchAddress("fNhits", &fNhits);
      tree->SetBranchAddress("fhitArray.chip_id", chip_id);
      tree->SetBranchAddress("fhitArray.chan_id", chan_id);

      tree->SetBranchAddress("fhitArray.ladder", ladder);
      tree->SetBranchAddress("fhitArray.arm", arm);
      tree->SetBranchAddress("fhitArray.bco", bco);
      tree->SetBranchAddress("fhitArray.bco_full", bco_full);
      tree->SetBranchAddress("fhitArray.layer", layer);
      tree->SetBranchAddress("fhitArray.barrel", barrel);
      tree->SetBranchAddress("bco", &bco_event);

      // Local Information

      tree->SetBranchAddress("fhitArray.chip_id", chip_id);
      tree->SetBranchAddress("fhitArray.module", module);
      tree->SetBranchAddress("fhitArray.chan_id", chan_id);

      tree->SetBranchAddress("bco", &bco_event);

      TFile* fout = new TFile(Form("OutFile/INTT/3DHitTree_%d.root", Index), "RECREATE");
      fout->cd();

      int EventID;
      int NumberHits;

      std::vector<int> HitID;
      std::vector<int> LayerID;
      std::vector<int> barrelID;

      std::vector<int> LadderPhiID;
      std::vector<int> LadderZID;
      std::vector<int> ChipID;
      std::vector<int> RowID;
      std::vector<int> ColID;

      std::vector<float> GlobalX;
      std::vector<float> GlobalY;
      std::vector<float> GlobalZ;

      std::vector<float> GlobalX2;
      std::vector<float> GlobalY2;
      std::vector<float> GlobalZ2;

      std::vector<float> LocalX;
      std::vector<float> LocalY;
      std::vector<float> LocalZ;
      std::vector<long int> BCO;
      std::vector<double> Time;
      std::vector<long int> BCOFull;

      TTree* PixelWorldTree = new TTree("INTTHitTree", "INTTHitTree");

      PixelWorldTree->Branch("EventID", &EventID);
      PixelWorldTree->Branch("NumberHits", &NumberHits);
      PixelWorldTree->Branch("HitID", &HitID);
      PixelWorldTree->Branch("LayerID", &LayerID);
      PixelWorldTree->Branch("barrelID", &barrelID);
      PixelWorldTree->Branch("BCO", &BCO);
      PixelWorldTree->Branch("Time", &Time);
      PixelWorldTree->Branch("BCOFull", &BCOFull);

      PixelWorldTree->Branch("LadderPhiID", &LadderPhiID);
      PixelWorldTree->Branch("LadderZID", &LadderZID);
      PixelWorldTree->Branch("ChipID", &ChipID);
      PixelWorldTree->Branch("RowID", &RowID);
      PixelWorldTree->Branch("ColID", &ColID);
      PixelWorldTree->Branch("GlobalX", &GlobalX);
      PixelWorldTree->Branch("GlobalY", &GlobalY);
      PixelWorldTree->Branch("GlobalZ", &GlobalZ);

      PixelWorldTree->Branch("LocalX", &LocalX);
      PixelWorldTree->Branch("LocalY", &LocalY);
      PixelWorldTree->Branch("LocalZ", &LocalZ);

      PixelWorldTree->Branch("GlobalX2", &GlobalX2);
      PixelWorldTree->Branch("GlobalY2", &GlobalY2);
      PixelWorldTree->Branch("GlobalZ2", &GlobalZ2);

      int NEvents = tree->GetEntries();

      // NEvents = 100;

      NEvents = 1000000;

      Long64_t BCOIndex;
      int InEventBCO;
      int MinEvtBCO;
      Long_t AbsBCO;
      bool Set = false;
      Long64_t BCOFullStart = -1;

      for (int i = 0; i < NEvents; i++)
      {
        tree->GetEntry(i);

        EventID = evtSeq;
        NumberHits = fNhits;

        if (EventID == 0 && Set == false)
        {
          BCOFullStart = bco_event;
          Set = true;
        }
        if (!Set) continue;

        BCOIndex = bco_event - BCOFullStart;
        MinEvtBCO = 100000;
        InEventBCO = 0;

        for (int j = 0; j < fNhits; j++)
        {
          if (bco[j] < MinEvtBCO) MinEvtBCO = bco[j];
        }

        for (int j = 0; j < fNhits; j++)
        {
          // Below I tranform INTT decoded data to fit in offline tracking software from simulation

          InEventBCO = bco[j] - MinEvtBCO;
          AbsBCO = InEventBCO + BCOIndex;
          TimeCal = AbsBCO * 106.0 / 1000000000.0;  // In the unit of second (s) 106 ns -> 0.0000000106 s

          int NowChip = chip_id[j];
          int NowLayer = layer[j] + barrel[j] * 2 + 3;
          int NowChannel = chan_id[j];

          int NowLadderPhiID = ladder[j];
          int NowLadderZID = arm[j] * 2 + (NowChip % 13 < 5);

          uint8_t GenLayer = layer[j] + barrel[j] * 2 + 3;
          uint8_t GenLadderPhiID = ladder[j];
          uint8_t GenLadderZID = arm[j] * 2 + (NowChip % 13 < 5);

          int strip_y = -100;

          switch (NowLadderZID)
          {
          case 1:
            strip_y = NowChip % 13;
            break;

          case 0:
            strip_y = NowChip % 13 - 5;
            break;

          case 2:
            strip_y = 12 - (NowChip % 13);
            break;

          case 3:
            strip_y = 4 - (NowChip % 13);
            break;

          default:
            break;
          }

          int strip_x = (arm[j] == (chip_id[j] / 13)) ? NowChannel : 255 - NowChannel;

          int NowCol = strip_x;
          int NowRow = strip_y;

          //	cout << "NowLayer = " << NowLayer << "    NowLadderZID = " << NowLadderZID << "    NowLadderPhiID = " << NowLadderPhiID << endl;
          auto hitsetkey = InttDefs::genHitSetKey(GenLayer, GenLadderZID, GenLadderPhiID, 0);
          //	cout << "NowLayer = " << NowLayer << "    NowLadderZID = " << NowLadderZID << "    NowLadderPhiID = " << NowLadderPhiID << "    hitsetkey = " << hitsetkey << endl;
          auto hitkey = InttDefs::genHitKey(strip_y, strip_x);

          auto surface = m_tGeometry->maps().getSiliconSurface(hitsetkey);

          double local[3] = {0.0, 0.0, 0.0};

          CylinderGeomIntt* geom = dynamic_cast<CylinderGeomIntt*>(m_Geoms2->GetLayerGeom(NowLayer));
          // geom->find_strip_center(surface,m_tGeometry,NowLadderZID,NowLadderPhiID,NowCol,NowRow,hit_location);

          geom->find_strip_center_localcoords(NowLadderZID, strip_y, strip_x, local);

          TVector3 LocalCord;

          LocalCord.SetXYZ(local[0], local[1], local[2]);

          TVector3 Global = geom->get_world_from_local_coords(surface, m_tGeometry, LocalCord);

          HitID.push_back(j);
          LayerID.push_back(NowLayer);
          LadderPhiID.push_back(NowLadderPhiID);
          LadderZID.push_back(NowLadderZID);
          ChipID.push_back(NowChip);
          RowID.push_back(NowRow);
          ColID.push_back(NowCol);

          LocalX.push_back(LocalCord.X());
          LocalY.push_back(LocalCord.Y());
          LocalZ.push_back(LocalCord.Z());

          GlobalX.push_back(Global.X());
          GlobalY.push_back(Global.Y());
          GlobalZ.push_back(Global.Z());

          // Additional Redo//
          double hit_location[3] = {0.0, 0.0, 0.0};

          unsigned int Row2 = InttDefs::getRow(hitkey);
          unsigned int Col2 = InttDefs::getCol(hitkey);
          unsigned int LadderZId2 = InttDefs::getLadderZId(hitsetkey);
          unsigned int LadderPhiId2 = InttDefs::getLadderPhiId(hitsetkey);

          geom->find_strip_center(surface, m_tGeometry, LadderZId2, LadderPhiId2, Col2, Row2, hit_location);

          // Manual Rotation clockwise by 90 degrees to the correct position for old software issue, will be fixed later by the INTT experts

          float RotX = hit_location[1];
          float RotY = -hit_location[0];
          float RotZ = hit_location[2];

          GlobalX2.push_back(RotX);
          GlobalY2.push_back(RotY);
          GlobalZ2.push_back(RotZ);

          BCO.push_back(AbsBCO);
          Time.push_back(TimeCal);
          BCOFull.push_back(bco_full[j]);
        }

        PixelWorldTree->Fill();

        HitID.clear();
        LayerID.clear();
        barrelID.clear();
        LadderPhiID.clear();
        LadderZID.clear();
        ChipID.clear();
        RowID.clear();
        ColID.clear();

        GlobalX.clear();
        GlobalY.clear();
        GlobalZ.clear();

        GlobalX2.clear();
        GlobalY2.clear();
        GlobalZ2.clear();

        LocalX.clear();
        LocalY.clear();
        LocalZ.clear();
        BCO.clear();
        Time.clear();

        BCOFull.clear();
      }

      fout->cd();

      PixelWorldTree->Write();

      fout->Close();

      Index = Index + 1;
    }
  }

  // std::cout << "Pass 10" << std::endl;

  return Fun4AllReturnCodes::EVENT_OK;
}

int PlotWorld::process_event(PHCompositeNode* topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

int PlotWorld::End(PHCompositeNode* topNode)
{
  std::cout << "DONE" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

int PlotWorld::load_nodes(PHCompositeNode* topNode)
{
  //   cout << "Loading Nodes Bro" << endl;

  return Fun4AllReturnCodes::EVENT_OK;
}
