#include "Point.hh"
#include "Log.hh"

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

    fPhysicalCoordinates    = new std::vector<double>(fDimension);
    fTranslatedCoordinates  = new std::vector<double>(fDimension);
    fRotatedCoordinates     = new std::vector<double>(fDimension);

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


    Log::OutDebug( "Point coordinates in physical space:" );
    for( unsigned int i=0; i<fDimension; i++ )
	Log::OutDebug( "\t" + std::to_string( fPhysicalCoordinates->at(i) ) );
    
    return;
}
