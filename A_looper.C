#include "TROOT.h"
#include <TFile.h>
#include "MyClass.h"
#include "MyClass.C"

using namespace std;

void A_looper()
{
  MyClass m;
  m.Loop();
}
