#include "Global.hh"
#include "Log.hh"
#include "Random.hh"

#ifdef HAVE_ROOT
#include "TH1D.h"
#endif

#include "eigen3/Eigen/Eigen"

int main()
{

    int verbosity = 4;
    Log::OpenLog( verbosity );

    Global::Initialize();
    
    unsigned seed = 12345;
    Random rdm(seed);
	    
    Log::OutSummary( "Everything done." );
    
    return 0;
}
