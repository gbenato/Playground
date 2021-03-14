#include "Space.hh"
#include "Log.hh"

Space::Space( std::string  name,
	      Type         type,
	      unsigned int dimension )
{
    fName         = name;
    fType         = type;
    fDimension    = dimension;
    fVariableList = std::vector<Variable>( fDimension );
    
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

void Space::AddVariable( std::string name,
			 double      min,
			 double      max,
			 std::string unit )
{
    for( unsigned int i=0; i<fDimension; i++ )
	if( name == fVariableList[i].GetName() )
	    {
		Log::OutError( "Space::AddVariable(): can't have two variables with the same name. Abort." );
		exit(1);
	    }
    
    fVariableList.push_back( Variable( name,
				       min,
				       max,
				       unit ) );
    fDimension ++;

    Log::OutDebug( "Added variable " + fVariableList.back().GetName() +
		   "\twith index " + std::to_string( fDimension -1 ) +
		   "\tto space " + fName );
    
    return;
}


void Space::AddVariable( Variable& variable )
{
    fVariableList.push_back( variable );
    fDimension ++;

    Log::OutDebug( "Added variable " + fVariableList.back().GetName() +
		   "\twith index " + std::to_string( fDimension -1 ) +
		   "\tto space " + fName );
    
    return;
}

std::vector<double>* Space::GenerateRandomPosition()
{
    std::vector<double>* pos = new std::vector<double>( fDimension );
    for( unsigned int i=0; i<fDimension; i++ )
	pos->at(i) = fVariableList[i].GenerateRandom();
    
    return pos;
}
