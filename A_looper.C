#include "TROOT.h"
#include <TFile.h>
#include "MyClass.h"
#include "MyClass.C"

using namespace std;

int main()
{
  MyClass m;
  m.Loop();
}
