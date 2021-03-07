#include "Global.hh"
#include "Log.hh"
#include "Parameter.hh"
#include "Random.hh"

#ifdef HAVE_ROOT
#include "TH1D.h"
#endif

int main()
{

    int verbosity = 4;
    Log::OpenLog( verbosity );

    //Global* global = Global::GetInstance();
    Global::Initialize();
    

    Parameter* par = new Parameter( "TestPar", 0., 10., "cm" );
    par->SetPrior( Parameter::PriorType::kGaussian, 5., 1. );

    Random rdm;

    #ifdef HAVE_ROOT
	    TH1D* histo = new TH1D();
	    Log::OutDebug( "Created histo" );
    #endif
    
    Log::OutSummary( "Everything done." );
    
    return 0;
}
