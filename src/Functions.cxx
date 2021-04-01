#include <iostream>
#include <memory>

#include "UHH2/HHtoWWbbSemiLeptonic/include/Functions.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

using namespace std;
using namespace uhh2;

double TransverseMass(LorentzVector A, LorentzVector B, double mA, double mB) {
  double pTA = A.Pt();
  double pTB = B.Pt();
  double pt = (A+B).Pt();

  //double Et = sqrt(pow(pTA,2)+pow(mA,2))+sqrt(pow(pTB,2)+pow(mB,2));
  double Et = sqrt(pow(pTA,2)+pow(mA,2))+sqrt(pow(pTB,2)+pow(mB,2));
  double mt;
  // save for timelike/spacelike vectors ?
  if(Et > pt) mt = sqrt(pow(Et,2)-pow(pt,2));
  else mt = -sqrt(-(pow(Et,2)-pow(pt,2)));
  //cout << "mt: " << mt << endl;
  return mt;
}

// X->Y+Z, Y->A+B, Z->C+D with A,B,C,D assumed to be massless
double TransverseMass4particles(LorentzVector A, LorentzVector B, LorentzVector C, LorentzVector D) {
  double mtAB = TransverseMass(A,B,0,0);
  double mtCD = TransverseMass(C,D,0,0);
  double mtABCD = TransverseMass(A+B,C+D,mtAB,mtCD);
  return mtABCD;
}
