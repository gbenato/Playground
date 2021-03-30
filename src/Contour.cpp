#include "Contour.hh"
#include "Point.hh"
#include "Log.hh"
#include "Space.hh"

#include <iostream>

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
    ComputeVolume();

}

Contour::Contour( const Contour& other )
{

    fPoint             = other.GetPoint();
    fEllipsoidMatrix   = other.GetEllipsoidMatrix();
    fEigenvectorMatrix = other.GetEigenvectorMatrix();
    fMean              = other.GetMean();
    fHeight            = other.GetHeight();
    fNSigma            = other.GetNSigma();
    fVolume            = other.GetVolume();
    fIntegral          = other.GetIntegral();
    
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

    // Compute equivalent number of sigmas from mean
    fNSigma = 0.;
    for( unsigned int i=0; i<fPoint->GetDimension(); i++ )
	fNSigma += pow( fPoint->GetRotated(i), 2. )
	    / pow( fEllipsoidMatrix->coeff(i,i), 2. );
    fNSigma = sqrt( fNSigma );

    // Compute volume of n-dimensional ellipsoid
    double n = fPoint->GetDimension();
    fVolume = pow( M_PI, 0.5*n ) / std::tgamma( 0.5*n + 1. );
    fVolume *= pow( fNSigma, n );
    for( unsigned int i=0; i<fPoint->GetDimension(); i++ )
	fVolume *= fEllipsoidMatrix->coeff(i,i);
    
    return;
}

void Contour::SetIntegral( double integral ) const
{
    fIntegral = integral;
    
    return;
}

// Operators
Contour& Contour::operator = ( Contour const& other )
{
    if( (void*)this == (void*)&other )
	return *this;
    
    fPoint             = other.GetPoint();
    fEllipsoidMatrix   = other.GetEllipsoidMatrix();
    fEigenvectorMatrix = other.GetEigenvectorMatrix();
    fMean              = other.GetMean();
    fHeight            = other.GetHeight();
    fNSigma            = other.GetNSigma();
    fVolume            = other.GetVolume();
    fIntegral          = other.GetIntegral();

    
    return *this;
}

bool Contour::operator < ( const Contour& other ) const
{
    return fHeight < other.GetHeight();
}
