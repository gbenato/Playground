#include "Contour.hh"
#include "Point.hh"
#include "Log.hh"
#include "Space.hh"

Contour::Contour( Point*           point,
		  Eigen::MatrixXd* ellipsoidmatrix,
		  Eigen::MatrixXd* eigenvectormatrix,
		  Eigen::VectorXd* mean )
{
    fPoint = point;
    if( fPoint->IsProbabilityMeasured() )
	fHeight = fPoint->GetPosteriorProbability();
    else
	{
	    Log::OutError( "Contour::Contour(): point probability not measured. Abort." );
	    exit(1);
	}

    fEllipsoidMatrix   = ellipsoidmatrix;
    fEigenvectorMatrix = eigenvectormatrix;
    fMean              = mean;
    fNSigma            = 0.;
    fVolume            = 0.;
    fIntegral          = 0.;
    fIntegralComputed  = false;
    ComputeIntegral();
}

Contour::Contour( const Contour& other )
{
    fPoint             = other.GetPoint();
    fHeight            = other.GetHeight();
    fEllipsoidMatrix   = other.GetEllipsoidMatrix();
    fEigenvectorMatrix = other.GetEigenvectorMatrix();
    fMean              = other.GetMean();
    
    ComputeIntegral();
}

Contour::~Contour()
{
    ;
}

void Contour::ComputeVolume()
{
    if( fPoint->GetOriginalSpaceType() == Space::kPhysical )
	fPoint->ComputeTransformedCoordinates( fEllipsoidMatrix,
					       fEigenvectorMatrix,
					       fMean );
    
    fNSigma = 0.;

    for( unsigned int i=0; i<fPoint->GetDimension(); i++ )
	fNSigma += pow( fPoint->GetRotated(i), 2. )
	    / pow( fEllipsoidMatrix->coeff(i,i), 2. );
    fNSigma = sqrt( fNSigma );

    //Log::OutDebug( "Gamma: " + std::to_string( std::tgamma( 0.5 * fPoint->GetDimension() + 1 ) ) );
    double n = fPoint->GetDimension();
    //fVolume = 2. * pow( M_PI, 0.5*n ) / std::tgamma( 0.5*n );
    fVolume = pow( M_PI, 0.5*n ) / std::tgamma( 0.5*n + 1. );
    fVolume *= pow( fNSigma, n );
    for( unsigned int i=0; i<fPoint->GetDimension(); i++ )
	fVolume *= fEllipsoidMatrix->coeff(i,i);
    
    //Log::OutDebug( "Volume: " + std::to_string(fVolume) );
    
    return;
}

void Contour::ComputeIntegral()
{
    ComputeVolume();
    
    fIntegral         = fVolume * fHeight;
    fIntegralComputed = true;
    
    return;
}
/*
double Contour::GetVolume() const
{
    //if( fIntegralComputed == false )
	//ComputeIntegral();
    
    return fVolume;
}

double Contour::GetIntegral()
{
    //if( fIntegralComputed == false )
    //	ComputeIntegral();
    
    return fIntegral;
}
*/
// Operators
Contour& Contour::operator = ( Contour const& other )
{
    if( (void*)this == (void*)&other )
	return *this;
    
    fPoint  = other.GetPoint();
    fHeight = other.GetHeight();
    ComputeIntegral();
    
    return *this;
}

bool Contour::operator < ( const Contour& other ) const
{
    return fHeight < other.GetHeight();
}
