#include "Global.hh"
#include "Log.hh"
#include "MultiVariateModel.hh"
#include "Random.hh"
#include "Space.hh"
#include "Point.hh"

#ifdef HAVE_ROOT
#include "TH1D.h"
#endif


int main()
{

    int verbosity = 4;
    Log::OpenLog( verbosity );

    Global::Initialize();

    unsigned seed = 12345;
    Random rdm(seed);
    
    MultiVariateModel* model = new MultiVariateModel();
    Space*             space = model->GetPhysicalSpace();
    for( int i=0; i<100; i++ )
	{
	    Point point( space );
	    point.GenerateRandomPosition();
	    Log::OutDebug( "Likelihood: " + std::to_string( model->MeasureLikelihood( &point ) ) );
	}
    
    Log::OutSummary( "Everything done." );
    
    return 0;
}
