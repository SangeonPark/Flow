#include "RiceStyle.h"

using namespace std;

void systematics_unc_calc(){

	//double ntrk_unc[8] = {0.061,0.058,0.053,0.051,0.047,0.044,0.039,0.032};
	double cent_unc[6] = {0.072,0.068,0.051,0.037,0.011,0.012};
	double vtz_unc = 0.014563107;
	double trk_unc = 0.033980583;

	for (int i = 0; i < 6; ++i)
	{
		cout << sqrt(cent_unc[i]*cent_unc[i]+vtz_unc*vtz_unc+trk_unc*trk_unc) << "," ;
	}




}