#include "MultiVariateModel.hh"
#include "Log.hh"
#include "Space.hh"
#include "Random.hh"
#include "Point.hh"

#include <string>
#include <iostream>


MultiVariateModel::MultiVariateModel( unsigned int dimension ) : Model()
{
    fDimension = dimension;
    //fMean      = new double(fDimension);
    //fSigma     = new double(fDimension);
    fRandom    = Random::GetInstance();

    Initialize();
}

MultiVariateModel::~MultiVariateModel()
{
    ;
}

void MultiVariateModel::Initialize()
{
    double angle = fRandom->GetUniform( 0., 2. * M_PI );
    double c     = cos(angle);
    double s     = sin(angle);
    //fRotation = Matrix2D();
    fRotation << c, -s, s, c;
    fInverseRotation << c, s, -s, c;
    
    
    //double mean[fDimension];
    //double sigma[fDimension];
    for( unsigned int i=0; i<fDimension; i++ )
	{
	    fRotatedMean(i) = fRandom->GetUniform();
	    fRotatedSigma(i) = fRandom->GetUniform( 0., fabs(fRotatedMean(i)) );
	    //mean[i]  = fRandom->GetUniform();
	    //sigma[i] = fRandom->GetUniform( 0., fabs(mean) );
	}

    fMean  = fInverseRotation * fRotatedMean;
    fSigma = fInverseRotation * fRotatedSigma;
    for( unsigned int i=0; i<fDimension; i++ )
	fSigma(i) = fabs(fSigma(i));
    
    //fMean[0]  = +mean[0]  * c + mean[1]  * s;
    //fSigma[0] = +sigma[0] * c + sigma[1] * s;
    //fMean[1]  = -mean[0]  * s + mean[1]  * c;
    //fSigma[1] = -sigma[0] * s + sigma[1] * c;
    
    for( unsigned int i=0; i<fDimension; i++ ){
	
	//fMean[i] = fRandom->GetUniform();
	//fSigma[i] = fRandom->GetUniform( 0., fabs( fMean[i] ) );
	    fPhysicalSpace->AddParameter( "P_" + std::to_string(i),
					  fMean(i) - 7. * fSigma(i),
					  fMean(i) + 7. * fSigma(i) );

	    Log::OutDebug( "MultiVariateModel: fMean[" + std::to_string(i) + "]:  " + std::to_string(fMean(i)) );
	    Log::OutDebug( "MultiVariateModel: fSigma[" + std::to_string(i) + "]: " + std::to_string(fSigma(i)) );
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

    Eigen::Vector2d tmp = fRotation * point->GetPhysical();
    for( unsigned int i=0; i<fDimension; i++ )
	likelihood *= exp( -pow( tmp(i) - fRotatedMean(i), 2. ) / 2. / pow( fRotatedSigma(i), 2. ) ) / fRotatedSigma(i);
	//likelihood *= exp( -pow( point->GetPhysical(i) - fMean[i], 2. ) / 2. / pow( fSigma[i], 2. ) ) / fSigma[i];
    likelihood /= sqrt( 2. * M_PI * fDimension );

    return likelihood;
}

//double MultiVariateModel::MeasurePrior()
//{
//    return 1.;
//}
