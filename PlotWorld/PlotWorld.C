#include "PlotWorld.h"

#include <fun4all/Fun4AllReturnCodes.h>
#include <pdbcalbase/PdbParameterMap.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHTimeServer.h>
#include <phool/PHTimer.h>
#include <phool/getClass.h>

#include <phool/PHCompositeNode.h>

#include <g4main/PHG4Hit.h>
#include <g4main/PHG4Particle.h>
#include <g4main/PHG4HitContainer.h>
#include <g4main/PHG4TruthInfoContainer.h>

#include <trackbase/TrkrHitTruthAssocv1.h>
#include <trackbase/TrkrHitSetContainer.h>
//#include <trackbase/TrkrClusterHitAssoc.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHit.h>
//#include <trackbase/TrkrCluster.h>

#include <trackbase/MvtxDefs.h>
#include <mvtx/CylinderGeom_Mvtx.h>

#include <trackbase/InttDefs.h>
#include <intt/CylinderGeomIntt.h>

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



#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <trackbase/ActsSurfaceMaps.h>






using namespace std;

PlotWorld::PlotWorld(std::string filename, int DetType)
	: SubsysReco("PlotWorld")
{  
	cout << "Running - Detector Type - " << DetType << endl;

	DetectorType = DetType;
}

int PlotWorld::Init(PHCompositeNode* topNode)
{

	std::cout << "Initial Bro" << std::endl;

	if(DetectorType == 0) DetName = "MVTX";
	if(DetectorType == 1) DetName = "INTT";

	//Basically Copy Pasted Codes Here


	//DONE

	return Fun4AllReturnCodes::EVENT_OK;
}

int PlotWorld::InitRun(PHCompositeNode* topNode)
{
	m_Geoms =
		findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_MVTX");
	if (!m_Geoms)
	{
		//std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_MVTX" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_Geoms2 =
		findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_INTT");
	if (!m_Geoms2)
	{
		//std::cout << PHWHERE << "ERROR: Can't find node CYLINDERCELLGEOM_INTT" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_truthInfo = findNode::getClass<PHG4TruthInfoContainer>(topNode, "G4TruthInfo");
	if (!m_truthInfo)
	{
		//std::cout << PHWHERE << "ERROR: Can't find node G4TruthInfo" << std::endl;
		return Fun4AllReturnCodes::ABORTRUN;
	}

	m_tGeometry = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
	if (!m_tGeometry)
	{
		cout << "HFMLTriggerInterface::InitRun - WARNING - missing m_tGeometry" << endl;
	}



	std::cout << "Basically Copy Paste Codes Here" << "    Again Det Type is = " << DetectorType << std::endl;

	if(DetectorType == 0){


		int Index = 0;



		ifstream FileList("FileList.txt");    
		string line;

		while(getline(FileList, line))
		{

			//TString infile = "/sphenix/u/xyu3/workarea/felix-mvtx/software/cpp/decoder_zhaozhong/fhrana_tree/20230627_Run20124_111x111_ZDC100Hz_Trg11kHz_DataRunConfig_MagOn_2mrad/fhrana_20230627_Run20124_111x111_ZDC100Hz_Trg11kHz_DataRunConfig_MagOn_2mrad_FEEID8704.root";



			//TString infile = line;

			cout << "Now Processing MVTX File Index: " << Index <<   "     Name: " << line.c_str() << endl;

			int event;
			int Nhits;


			vector<int> * Stave_hit = 0;
			vector<int> * Layer_hit = 0;
			vector<int> * RowID_hit = 0;
			vector<int> * ColumnID_hit = 0;
			vector<int> * ChipID_hit = 0;

			TFile * fin = new TFile(line.c_str());
			fin->cd();

			TTree * tree_fhrana = (TTree *) fin->Get("tree_fhrana");



			tree_fhrana->SetBranchAddress("event",&event);
			tree_fhrana->SetBranchAddress("Nhits",&Nhits);
			tree_fhrana->SetBranchAddress("RowID_hit",&RowID_hit);
			tree_fhrana->SetBranchAddress("ColumnID_hit",&ColumnID_hit);
			tree_fhrana->SetBranchAddress("ChipID_hit",&ChipID_hit);
			tree_fhrana->SetBranchAddress("Stave_hit",&Stave_hit);
			tree_fhrana->SetBranchAddress("Layer_hit",&Layer_hit);


			int NEvents = tree_fhrana->GetEntries();

			NEvents = 10000;


			int EventID;
			int NumberHits;
			std::vector<int> HitID;	
			std::vector<int> StaveID;
			std::vector<int> LayerID;
			std::vector<int> ChipID;
			std::vector<int> RowID;
			std::vector<int> ColID;

			std::vector<float> GlobalX;
			std::vector<float> GlobalY;
			std::vector<float> GlobalZ;

			std::vector<float> LocalX;
			std::vector<float> LocalY;
			std::vector<float> LocalZ;

			std::vector<float> ChipGlobalX;
			std::vector<float> ChipGlobalY;
			std::vector<float> ChipGlobalZ;

			std::cout << "Pass 4" << std::endl;








			TFile * fout = new TFile(Form("OutFile/MVTX/3DHitTree_%d.root",Index),"RECREATE");
			fout->cd();



			TTree * PixelWorldTree = new TTree("MVTXPixelTree","MVTXPixelTree"); 

			PixelWorldTree->Branch("EventID",&EventID);
			PixelWorldTree->Branch("NumberHits",&NumberHits);
			PixelWorldTree->Branch("HitID",&HitID);
			PixelWorldTree->Branch("StaveID",&StaveID);
			PixelWorldTree->Branch("LayerID",&LayerID);
			PixelWorldTree->Branch("ChipID",&ChipID);	
			PixelWorldTree->Branch("RowID",&RowID);
			PixelWorldTree->Branch("ColID",&ColID);
			PixelWorldTree->Branch("GlobalX",&GlobalX);
			PixelWorldTree->Branch("GlobalY",&GlobalY);
			PixelWorldTree->Branch("GlobalZ",&GlobalZ);


			PixelWorldTree->Branch("LocalX",&LocalX);
			PixelWorldTree->Branch("LocalY",&LocalY);
			PixelWorldTree->Branch("LocalZ",&LocalZ);

			PixelWorldTree->Branch("ChipGlobalX",&ChipGlobalX);
			PixelWorldTree->Branch("ChipGlobalY",&ChipGlobalY);
			PixelWorldTree->Branch("ChipGlobalZ",&ChipGlobalZ);


			for(int i = 0; i < NEvents; i++){

				tree_fhrana->GetEntry(i);



				EventID = event;
				NumberHits = Nhits;


				//std::cout << "event = " << event << "     Nhits = " << Nhits << endl;

				for(int j = 0; j < Nhits; j++){



					HitID.push_back(j);
					StaveID.push_back(Stave_hit->at(j));
					LayerID.push_back(Layer_hit->at(j));
					ChipID.push_back(ChipID_hit->at(j));

					RowID.push_back(RowID_hit->at(j));
					ColID.push_back(ColumnID_hit->at(j));


					uint8_t NowChip = ChipID_hit->at(j);
					int NowColChip = int(ColumnID_hit->at(j)) / 1024;
					int NowCol = ColumnID_hit->at(j) - NowColChip * 1024;
					int NowRow = RowID_hit->at(j);
					uint8_t  NowLayer = Layer_hit->at(j);
					uint8_t  NowStave = Stave_hit->at(j);
					auto hitsetkey = MvtxDefs::genHitSetKey(NowLayer,NowStave,NowChip,0);


//					unsigned int ReGetChip = MvtxDefs::getChipId(hitsetkey);
//					unsigned int ReGetStave = MvtxDefs::getStaveId(hitsetkey);


					//std::cout << "Validation: " << hitsetkey  << "   ChipID = " << NowChip << "      ReGetChip = " << ReGetChip << "  Stave = " <<  Stave_hit->at(j) << "     ReGetStave = " << ReGetStave << "   LayerID = " << Layer_hit->at(j)    << std::endl;
					int  GoodLayer = Layer_hit->at(j);




					//geom->find_strip_center_localcoords(NowLadderZID,strip_y,strip_x,local);

			

					CylinderGeom_Mvtx* geom = dynamic_cast<CylinderGeom_Mvtx*>(m_Geoms->GetLayerGeom(GoodLayer));
					

					

					auto surface = m_tGeometry->maps().getSiliconSurface(hitsetkey);



					TVector3 local_coords = geom->get_local_coords_from_pixel(NowRow,NowCol);	
					double world_coords[3];
					geom->find_sensor_center(surface, m_tGeometry ,world_coords);
					

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

				}

				PixelWorldTree->Fill();

				HitID.clear();
				StaveID.clear();
				LayerID.clear();
				ChipID.clear();
				RowID.clear();
				ColID.clear();

				GlobalX.clear();
				GlobalY.clear();
				GlobalZ.clear();

				LocalX.clear();
				LocalY.clear();
				LocalZ.clear();

				ChipGlobalX.clear();
				ChipGlobalY.clear();
				ChipGlobalZ.clear();

			}

			fout->cd();

			PixelWorldTree->Write();		

			fout->Close();

			Index = Index + 1;

		}
		std::cout << "DONE BRo" << std::endl;


	}

	if(DetectorType == 1){



		ifstream FileList("INTTFileList.txt");    
		string line;

		int Index = 0;

		while(getline(FileList, line))
		{
	
			cout << "Now Processing INTT File Index: " << Index <<   "     Name: " << line.c_str() << endl;

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
			double TimeCal;  //Time in second


			TFile * fin = new TFile(line.c_str());
			fin->cd();

			TTree * tree = (TTree *) fin->Get("tree");


			tree->SetBranchAddress("evtSeq",&evtSeq);
			tree->SetBranchAddress("fNhits",&fNhits);
			tree->SetBranchAddress("fhitArray.chip_id",chip_id);
			tree->SetBranchAddress("fhitArray.chan_id",chan_id);
			
			tree->SetBranchAddress("fhitArray.ladder",ladder);
			tree->SetBranchAddress("fhitArray.arm",arm);
			tree->SetBranchAddress("fhitArray.bco",bco);
			tree->SetBranchAddress("fhitArray.bco_full",bco_full);
			tree->SetBranchAddress("fhitArray.layer",layer);
			tree->SetBranchAddress("fhitArray.barrel",barrel);
			tree->SetBranchAddress("bco",&bco_event);

			//Local Information

			tree->SetBranchAddress("fhitArray.chip_id",chip_id);
			tree->SetBranchAddress("fhitArray.module",module);
			tree->SetBranchAddress("fhitArray.chan_id",chan_id);

			tree->SetBranchAddress("bco",&bco_event);



			TFile * fout = new TFile(Form("OutFile/INTT/3DHitTree_%d.root",Index),"RECREATE");
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


			TTree * PixelWorldTree = new TTree("INTTHitTree","INTTHitTree"); 

			PixelWorldTree->Branch("EventID",&EventID);
			PixelWorldTree->Branch("NumberHits",&NumberHits);
			PixelWorldTree->Branch("HitID",&HitID);
			PixelWorldTree->Branch("LayerID",&LayerID);
			PixelWorldTree->Branch("barrelID",&barrelID);
			PixelWorldTree->Branch("BCO",&BCO);
			PixelWorldTree->Branch("Time",&Time);
		
			PixelWorldTree->Branch("LadderPhiID",&LadderPhiID);
			PixelWorldTree->Branch("LadderZID",&LadderZID);
			PixelWorldTree->Branch("ChipID",&ChipID);	
			PixelWorldTree->Branch("RowID",&RowID);
			PixelWorldTree->Branch("ColID",&ColID);
			PixelWorldTree->Branch("GlobalX",&GlobalX);
			PixelWorldTree->Branch("GlobalY",&GlobalY);
			PixelWorldTree->Branch("GlobalZ",&GlobalZ);

			PixelWorldTree->Branch("LocalX",&LocalX);
			PixelWorldTree->Branch("LocalY",&LocalY);
			PixelWorldTree->Branch("LocalZ",&LocalZ);

			PixelWorldTree->Branch("GlobalX2",&GlobalX2);
			PixelWorldTree->Branch("GlobalY2",&GlobalY2);
			PixelWorldTree->Branch("GlobalZ2",&GlobalZ2);


			int NEvents = tree->GetEntries();
	

			//NEvents = 100;




			Long64_t BCOIndex;
			int InEventBCO;
			int MinEvtBCO;
			Long_t AbsBCO;
			bool Set = false;
			Long64_t BCOFullStart = -1;

			for(int i = 0; i < NEvents; i++){

				tree->GetEntry(i);

				EventID = evtSeq;
				NumberHits = fNhits;

				
				if(EventID == 0 && Set == false){
					BCOFullStart = bco_event;
					Set = true;
				}
				if(!Set) continue;

				BCOIndex = bco_event - BCOFullStart;
				MinEvtBCO = 100000;
				InEventBCO = 0;

				for(int j = 0; j < fNhits; j++){
					if(bco[j] < MinEvtBCO) MinEvtBCO = bco[j];
				}


				for(int j = 0; j < fNhits; j++){

					//Below I tranform INTT decoded data to fit in offline tracking software from simulation

					
					InEventBCO = bco[j] - MinEvtBCO;
					AbsBCO = InEventBCO + BCOIndex;
					TimeCal = AbsBCO * 106.0/1000000000.0;  //In the unit of second (s) 106 ns -> 0.0000000106 s

					int NowChip = chip_id[j];
					int NowLayer = layer[j] + barrel[j] * 2 + 3;
					int NowChannel = chan_id[j];


					int NowLadderPhiID = ladder[j];
					int NowLadderZID = arm[j] * 2 + (NowChip % 13 < 5);


					uint8_t GenLayer = layer[j] + barrel[j] * 2 + 3;
					uint8_t GenLadderPhiID = ladder[j];
					uint8_t GenLadderZID = arm[j] * 2 + (NowChip % 13 < 5);


					int strip_y = -100;


					switch(NowLadderZID)
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
					auto hitsetkey = InttDefs::genHitSetKey(GenLayer,GenLadderZID,GenLadderPhiID,0);
				//	cout << "NowLayer = " << NowLayer << "    NowLadderZID = " << NowLadderZID << "    NowLadderPhiID = " << NowLadderPhiID << "    hitsetkey = " << hitsetkey << endl;
					auto hitkey = InttDefs::genHitKey(strip_y,strip_x);

					auto surface = m_tGeometry->maps().getSiliconSurface(hitsetkey);
		

					double local[3] = {0.0,0.0,0.0};
					
					CylinderGeomIntt* geom = dynamic_cast<CylinderGeomIntt*>(m_Geoms2->GetLayerGeom(NowLayer));
					//geom->find_strip_center(surface,m_tGeometry,NowLadderZID,NowLadderPhiID,NowCol,NowRow,hit_location);

					geom->find_strip_center_localcoords(NowLadderZID,strip_y,strip_x,local);
		
			
					TVector3 LocalCord;

					LocalCord.SetXYZ(local[0],local[1],local[2]);
	
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


					//Additional Redo//
					double hit_location[3] = {0.0,0.0,0.0};
				

					unsigned int Row2 = InttDefs::getRow(hitkey);
					unsigned int Col2 = InttDefs::getCol(hitkey);
					unsigned int LadderZId2 = InttDefs::getLadderZId(hitsetkey);
					unsigned int LadderPhiId2 = InttDefs::getLadderPhiId(hitsetkey);


					geom->find_strip_center(surface,m_tGeometry,LadderZId2,LadderPhiId2,Col2,Row2,hit_location);

					//Manual Rotation clockwise by 90 degrees to the correct position for old software issue, will be fixed later by the INTT experts
					
					float RotX = hit_location[1];
					float RotY = -hit_location[0];
					float RotZ = hit_location[2];

					GlobalX2.push_back(RotX);
					GlobalY2.push_back(RotY);
					GlobalZ2.push_back(RotZ);
				
				
					BCO.push_back(AbsBCO);
					Time.push_back(TimeCal);


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

			}

			fout->cd();

			PixelWorldTree->Write();		

			fout->Close();

			Index = Index + 1;
		}

	}



	std::cout << "Pass 10" << std::endl;

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
