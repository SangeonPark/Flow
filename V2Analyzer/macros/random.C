#include "RiceStyle.h"
using namespace std;


void random(){
    TH1* h = new TH1F("h", "h", 100, 0, 1);
         for(size_t i = 0; i < 100000; i++){
    double x = double(rand()) / RAND_MAX;
    h->Fill(x);
  }
  h->SetMinimum(0);
  h->Draw();
}