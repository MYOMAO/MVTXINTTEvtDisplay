#include <TDatabasePDG.h>
#include <TFile.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TTree.h>


using namespace std;

void INTTBCO(){



	ifstream FileList("INTTFileList.txt");    
	string line;

	int Index = 0;




	while(getline(FileList, line))
	{

		TFile * fin = new TFile(line.c_str());
		fin->cd();

		TTree * tree = (TTree *) fin->Get("tree");
		

		int evtSeq;
		int fNhits;

		int chip_id[10000];
		int ladder[10000];
		int arm[10000];
		int bco[10000];
		Long64_t bco_full[10000];
		Long64_t bco_event;
		
		int module[10000];
		int chan_id[10000];
		int layer[10000];
		int barrel[10000];


		Long64_t BCOIndex;
		int InEventBCO;
		int MinEvtBCO;
		

		Long64_t BCOFullStart = -1;

		tree->SetBranchAddress("evtSeq",&evtSeq);
		tree->SetBranchAddress("fNhits",&fNhits);
		tree->SetBranchAddress("bco",&bco_event);
		
		tree->SetBranchAddress("fhitArray.chip_id",chip_id);
		tree->SetBranchAddress("fhitArray.chan_id",chan_id);

		tree->SetBranchAddress("fhitArray.ladder",ladder);
		tree->SetBranchAddress("fhitArray.arm",arm);
		tree->SetBranchAddress("fhitArray.bco",bco);
		tree->SetBranchAddress("fhitArray.bco_full",bco_full);
		tree->SetBranchAddress("fhitArray.layer",layer);
		tree->SetBranchAddress("fhitArray.barrel",barrel);

		//Local Information

		tree->SetBranchAddress("fhitArray.chip_id",chip_id);
		tree->SetBranchAddress("fhitArray.module",module);
		tree->SetBranchAddress("fhitArray.chan_id",chan_id);




		
		TFile * fout = new TFile(Form("BCOAna/BCOTree_%d.root",Index),"RECREATE");
		fout->cd();


		
	
		int EventID;
		int NEvtHit;
		int NBCOHit;
		Long_t AbsBCO;
		float Time;

		TTree * BCOTree = new TTree("BCOTree","BCOTree"); 
		BCOTree->Branch("EventID",&EventID,"EventID/I");
		BCOTree->Branch("NEvtHit",&NEvtHit,"NEvtHit/I");
	//	BCOTree->Branch("NBCOHit",&NBCOHit);
		BCOTree->Branch("AbsBCO",&AbsBCO);
		BCOTree->Branch("Time",&Time,"Time/F");
	

		int NEvents = tree->GetEntries();
			
		bool Set = false;
		for(int i = 0; i < NEvents; i++){

				tree->GetEntry(i);
		 

				if(i%10000==0){


					cout << "Now Working at Event " << i << endl;

				}

				EventID = evtSeq;
				NEvtHit = fNhits;
	


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

			//	cout << "EventID = " << EventID << "    BCOIndex = " << BCOIndex <<  "    MinBCO = " << MinEvtBCO << endl;

				for(int j = 0; j < fNhits; j++){
					
					InEventBCO = bco[j] - MinEvtBCO;

					AbsBCO = InEventBCO + BCOIndex;
					Time = AbsBCO * 106.0/1000000000.0;
			
					BCOTree->Fill();
				}



		}
			

		fout->cd();
		BCOTree->Write();		
		fout->Close();




		Index = Index + 1;


	}


}
