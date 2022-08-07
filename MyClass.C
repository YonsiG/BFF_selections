#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyClass::Loop(TString year)
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

   Long64_t nbytes = 0, nb = 0;
   Long64_t total_numbers = 0, Nbjet1=0, Nbjet2=0;
   Long64_t cut_numbers[13];
   for(Long64_t i=0; i<13; i++) cut_numbers[i]=0;

//   MySelector *selector = (MySelector *)TSelector::GetSelector("MySelector.C+");
//   fChain->Process(selector,"",100);
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;  
      int Cut_Return = Cut(ientry, year, cut_numbers);   
      if (Cut_Return > 0) {cout<<jentry<<endl; total_numbers++;} 
      if (Cut_Return == 1) Nbjet1++;
      if (Cut_Return >=2) Nbjet2++;
      if (Cut_Return < 0) continue;
   }
   cout<<"Nentries: "<<nentries<<endl;;
   cout<<"Pass Cut: "<<total_numbers<<endl;
   cout<<"Nb=1: "<<Nbjet1<<endl;
   cout<<"Nb>=2: "<<Nbjet2<<endl;
   cout<<"HLT: "<<cut_numbers[0]<<endl; 
   cout<<"Noise cleaning: "<<cut_numbers[1]<<endl; 
   cout<<"Nan/Inf: "<<cut_numbers[2]<<endl; 
   cout<<"Muon: "<<cut_numbers[3]<<endl; 
   cout<<"Muon match trigger: "<<cut_numbers[4]<<endl; 
   cout<<"has muon pair: "<<cut_numbers[5]<<endl; 
   cout<<"Mmumu>175: "<<cut_numbers[6]<<endl; 
   cout<<"Iso muon: "<<cut_numbers[10]<<endl; 
   cout<<"Iso electron: "<<cut_numbers[11]<<endl; 
   cout<<"Iso lep: "<<cut_numbers[12]<<endl; 
   cout<<"Isotrack: "<<cut_numbers[7]<<endl; 
   cout<<">=1 bjet: "<<cut_numbers[8]<<endl; 
   cout<<"MET>250 && (anti)aligned with l/b: "<<cut_numbers[9]<<endl; 
}
