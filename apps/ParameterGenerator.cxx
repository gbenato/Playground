#include "Log.hh"
#include "Parameter.hh"

int main()
{
    int verbosity = 4;
    Log::OpenLog( verbosity );

    Parameter* par = new Parameter( "TestPar", 0., 10., "cm" );
    par->SetPrior( Parameter::PriorType::kGaussian, 5., 1. );

    Log::OutSummary( "Everything done." );
    
    return 0;
}
