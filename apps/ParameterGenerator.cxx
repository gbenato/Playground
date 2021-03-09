#include "Global.hh"
#include "Log.hh"
#include "Variable.hh"
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
    

    unsigned seed = 12345;
    Random rdm(seed);
    for( int i=0; i<10; i++ )
	Log::OutDebug( "Random " + std::to_string(i) +
		       ": " + std::to_string( rdm.GetGaussian( 3, 1, 2.5,3.5 ) ) );


    Variable* par = new Variable( "TestPar", 0., 10., "cm" );
    par->SetPrior( Variable::PriorType::kGaussian, 5., 1. );
    
    #ifdef HAVE_ROOT
	    TH1D* histo = new TH1D();
	    Log::OutDebug( "Created histo" );
    #endif
    
    Log::OutSummary( "Everything done." );
    
    return 0;
}
