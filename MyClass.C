#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyClass::Loop(TString year, Int_t Mass, Bool_t Delta_bs1p0)
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Float_t lumi=137.6;
   Float_t xsection=1, genSumWeight=1;
   Long64_t nbytes = 0, nb = 0;
   Long64_t total_numbers = 0, jet1=0, jet2=0;
   Float_t weighted_total = 0, weighted_select=0, weighted_jet1=0, weighted_jet2=0; 
   Long64_t cut_numbers[13];
   for (Long64_t i=0; i<13; i++) cut_numbers[i]=0;
//   if (year=="2016_v7" && Mass == 250) {xsection = 122.5; genSumWeight = 511129;}
   if (year=="2016_v7" && Mass == 250 && Delta_bs1p0 == 0) {xsection = 122.5; genSumWeight = 511129;}
   if (year=="2016_v7" && Mass == 350 && Delta_bs1p0 == 0) {xsection = 31; genSumWeight = 470696;}
   if (year=="2016_v7" && Mass == 350 && Delta_bs1p0 == 1) {xsection = 165.8; genSumWeight = 476490;}
   if (year=="2016_v7" && Mass == 500 && Delta_bs1p0 == 0) {xsection = 6.4; genSumWeight = 421806;}      

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;  
      genWeight = genWeight*lumi*xsection/genSumWeight;
      weighted_total+=genWeight;
      int Cut_Return = Cut(ientry, year, Mass, cut_numbers);   
      if (Cut_Return > 0) {cout<<jentry<<endl; total_numbers++; weighted_select+=genWeight;} 
      if (Cut_Return == 1) {jet2++; weighted_jet2+=genWeight;}
      if (Cut_Return == 2) {jet1++; weighted_jet1+=genWeight;}
      if (Cut_Return < 0) continue;
   }
   cout<<"Nentries: "<<nentries<<endl;;
   cout<<"HLT: "<<cut_numbers[0]<<endl; 
   cout<<"MET Noise cleaning: "<<cut_numbers[1]<<endl; 
   cout<<">=2 Muon: "<<cut_numbers[2]<<endl; 
   cout<<"extra muon cleaning: "<<cut_numbers[3]<<endl; 
   cout<<"extra electron cleaning: "<<cut_numbers[4]<<endl; 
   cout<<"1 or 2 b jet category: "<<cut_numbers[5]<<endl; 
   cout<<"Mmumu>125: "<<cut_numbers[6]<<endl; 
   cout<<"HT-LT: "<<cut_numbers[7]<<endl; 
   cout<<"MET/mll: "<<cut_numbers[8]<<endl; 
   cout<<"Pass Cut: "<<total_numbers<<endl;
   cout<<"N jet=1: "<<jet1<<endl;
   cout<<"N jet=2: "<<jet2<<endl;
   cout<<"weighted total: "<<weighted_total<<endl;
   cout<<"weighted selected: "<<weighted_select<<endl;
   cout<<"weighted N jet=1: "<<weighted_jet1<<endl;
   cout<<"weighted N jet=2: "<<weighted_jet2<<endl;
}
