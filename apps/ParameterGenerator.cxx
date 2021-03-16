#include "Global.hh"
#include "Log.hh"
//#include "Variable.hh"
#include "Parameter.hh"
#include "Random.hh"
#include "Space.hh"
#include "Point.hh"

#ifdef HAVE_ROOT
#include "TH1D.h"
#endif

#include "eigen3/Eigen/Eigen"

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

    Space space( "TestSpace" );
    space.AddParameter( "A", 0., 10., "potatoes" );
    space.AddParameter( "B", 0., 5., "bananas" );
    
    Point point( &space );
    point.GenerateRandomPosition();

    Eigen::MatrixXd testmatrix;
    
    #ifdef HAVE_ROOT
	    TH1D* histo = new TH1D();
	    Log::OutDebug( "Created histo" );
    #endif

	    
    Log::OutSummary( "Everything done." );
    
    return 0;
}
