#include "Space.hh"
#include "Log.hh"

Space::Space( std::string  name,
	      Type         type,
	      unsigned int dimension )
{
    fName          = name;
    fType          = type;
    fDimension     = dimension;
    fParameterList = std::vector<Parameter>( fDimension );
    
    if( fType == Type::kTransformed &&
	fDimension == 0 )
	{
	    Log::OutError( "Space::Space(): Cannot instantiate transformed space with zero dimension. Abort." );
	    exit(1);
	}
    
    Log::OutDebug( "" );
    Log::OutDebug( "Created space " + fName );
    Log::OutDebug( "" );
}

Space::~Space()
{
    ;
}

void Space::AddParameter( std::string name,
			  double      min,
			  double      max,
			  std::string unit )
{
    for( unsigned int i=0; i<fDimension; i++ )
	if( name == fParameterList[i].GetName() )
	    {
		Log::OutError( "Space::AddParameter(): can't have two parameters with the same name. Abort." );
		exit(1);
	    }
    
    fParameterList.push_back( Parameter( name,
					 min,
					 max,
					 unit ) );
    fDimension++;

    Log::OutDebug( "Added parameter " + fParameterList.back().GetName() +
 		   "\twith index " + std::to_string( fDimension -1 ) +
		   "\tto space " + fName );

    return;
}


void Space::AddParameter( Parameter& parameter )
{
    fParameterList.push_back( parameter );
    fDimension++;

    Log::OutDebug( "Added parameter " + fParameterList.back().GetName() +
		   "\twith index " + std::to_string( fDimension -1 ) +
		   "\tto space " + fName );
    
    return;
}

std::vector<double>* Space::GenerateRandomPosition()
{
    std::vector<double>* pos = new std::vector<double>( fDimension );
    for( unsigned int i=0; i<fDimension; i++ )
	    pos->at(i) = fParameterList[i].GenerateRandom();

    return pos;
}
