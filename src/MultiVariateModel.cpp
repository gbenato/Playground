#include "MultiVariateModel.hh"
#include "Log.hh"
#include "Space.hh"
#include "Random.hh"
#include "Point.hh"
#include <string>

MultiVariateModel::MultiVariateModel( unsigned int dimension ) : Model()
{
    fDimension = dimension;
    fMean      = new double(fDimension);
    fSigma     = new double(fDimension);
    fRandom    = Random::GetInstance();

    Initialize();
}

MultiVariateModel::~MultiVariateModel()
{
    ;
}

void MultiVariateModel::Initialize()
{
    for( unsigned int i=0; i<fDimension; i++ )
	{
	    double halfrange = fRandom->GetUniform();
	    fPhysicalSpace->AddParameter( "P_" + std::to_string(i),
					  -halfrange,
					  +halfrange );
	    fMean[i]  = fRandom->GetUniform( -halfrange, +halfrange );
	    fSigma[i] = fRandom->GetUniform( 0., std::min( fMean[i]-halfrange, halfrange-fMean[i] ) );
	}
    
    return;
}

double MultiVariateModel::MeasureLikelihood( Point* point )
{
    if( fDimension != point->GetDimension() )
	{
	    Log::OutError( "MultiVariateModel::MeasureLikelihood: point has different dimension. Abort." );
	    exit(1);
	}

    double likelihood = 1.;
    for( unsigned int i=0; i<fDimension; i++ )
	likelihood *= exp( -pow( point->GetPhysical(i) - fMean[i], 2. ) / 2. / pow( fSigma[i], 2. ) ) / fSigma[i];
    likelihood /= sqrt( 2. * M_PI * fDimension );
    
    return likelihood;
}

//double MultiVariateModel::MeasurePrior()
//{
//    return 1.;
//}
