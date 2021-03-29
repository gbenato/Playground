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
    fArea              = 0.;
    fVolume            = 0.;
    fVolumeComputed    = false;
    ComputeVolume();
}

Contour::Contour( const Contour& other )
{
    fPoint             = other.GetPoint();
    fHeight            = other.GetHeight();
    fEllipsoidMatrix   = other.GetEllipsoidMatrix();
    fEigenvectorMatrix = other.GetEigenvectorMatrix();
    fMean              = other.GetMean();
    
    ComputeVolume();
}

Contour::~Contour()
{
    ;
}

void Contour::ComputeArea()// This is actually the volume of the n-dimensional ellipsoid
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
    //fArea = 2. * pow( M_PI, 0.5*n ) / std::tgamma( 0.5*n );
    fArea = pow( M_PI, 0.5*n ) / std::tgamma( 0.5*n + 1. );
    fArea *= pow( fNSigma, n );
    for( unsigned int i=0; i<fPoint->GetDimension(); i++ )
	fArea *= fEllipsoidMatrix->coeff(i,i);
    
    //Log::OutDebug( "Area: " + std::to_string(fArea) );
    
    return;
}

void Contour::ComputeVolume()
{
    ComputeArea();
    
    fVolume         = fArea * fHeight;
    fVolumeComputed = true;
    
    return;
}
/*
double Contour::GetArea() const
{
    //if( fVolumeComputed == false )
	//ComputeVolume();
    
    return fArea;
}

double Contour::GetVolume()
{
    //if( fVolumeComputed == false )
    //	ComputeVolume();
    
    return fVolume;
}
*/
// Operators
Contour& Contour::operator = ( Contour const& other )
{
    if( (void*)this == (void*)&other )
	return *this;
    
    fPoint  = other.GetPoint();
    fHeight = other.GetHeight();
    ComputeVolume();
    
    return *this;
}

bool Contour::operator < ( const Contour& other ) const
{
    return fHeight < other.GetHeight();
}
