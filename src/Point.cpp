#include "Point.hh"
#include "Random.hh"

#include <iostream>

Point::Point( Space* space )
{
    if( space->GetType() == Space::Type::kPhysical )
	{
	    fOriginalSpaceType = Space::Type::kPhysical;
	    fPhysicalSpace     = space;
	}
    else if( space->GetType() == Space::Type::kTransformed )
	fOriginalSpaceType = Space::Type::kTransformed;
    fDimension = space->GetDimension();

    fPhysicalCoordinates   = Eigen::VectorXd(fDimension);
    fRotatedCoordinates    = Eigen::VectorXd(fDimension);

    fLikelihood           = 0.;
    fPriorProbability     = 0.;
    fPosteriorProbability = 0.;
    fMeasuredProbability  = false;
    
    fRandom = Random::GetInstance();    
}

Point::~Point()
{
    ;
}

void Point::GenerateRandomPosition()
{
    if( fOriginalSpaceType == Space::Type::kTransformed )
	{
	    Log::OutDebug( "Point::GenerateRandomPosition(): can't generate random position for transformed coordinates. Abort." );
	    exit(1);
	}

    fPhysicalCoordinates = fPhysicalSpace->GenerateRandomPosition();


    //Log::OutDebug( "Point coordinates in physical space:" );
    //for( unsigned int i=0; i<fDimension; i++ )
    //	Log::OutDebug( "\t" + std::to_string( fPhysicalCoordinates(i) ) );
    
    return;
}

void Point::GeneratePositionInSphere()
{
    fRotatedCoordinates = Eigen::VectorXd(fDimension);
    for( unsigned int i=0; i<fDimension; i++ )
	fRotatedCoordinates(i) = fRandom->GetGaussian();
    fRotatedCoordinates.normalize();

    //double v = fRandom->GetUniform( pow(0.5, fDimension), pow(1., fDimension) );
    double v = fRandom->GetUniform( pow(1., fDimension), pow(2., fDimension) );
    double r = pow( v, 1./fDimension );
    fRotatedCoordinates *= r;
    
    return;
}

void Point::GeneratePositionInEllipsoid( Eigen::MatrixXd* ellipsoidmatrix,
					 Eigen::MatrixXd* rotation,
					 Eigen::VectorXd* translation )
{
    GeneratePositionInSphere();

    fRotatedCoordinates  = (*ellipsoidmatrix) * fRotatedCoordinates;
    fPhysicalCoordinates = (*rotation) * fRotatedCoordinates + (*translation);
    fOriginalSpaceType   = Space::kTransformed;
    
    return;
}

void Point::ComputeTransformedCoordinates( Eigen::MatrixXd* ellipsoidmatrix,
					   Eigen::MatrixXd* rotation,
					   Eigen::VectorXd* translation )
{
    fRotatedCoordinates = (rotation->inverse()) * ( fPhysicalCoordinates - (*translation) );
    //fRotatedCoordinates = (rotation->inverse()) * fPhysicalCoordinates;
    return;
}

/*
void Point::GenerateFixedPosition( std::vector<double>* pos )
{
    fPhysicalCoordinates = new std::vector<double>(fDimension);
    for( unsigned int i=0; i<fDimension; i++ )
	fPhysicalCoordinates->at(i) = pos->at(i);
    
    return;
}
*/
