#include "Random.hh"
#include "Log.hh"

Random* Random::fInstance = 0;

Random::Random( int seed )
{
    fSeed = seed;
    if( fSeed == 0 )
	{
	    Log::OutWarning( "" );
	    Log::OutWarning( "Random seed set to zero!" );
	    Log::OutWarning( "" );
	}
    
    fInstance = this;
}

Random::~Random()
{
    ;
}

Random* Random::GetInstance()
{
    if( fInstance == 0 )
	{
	    Log::OutError( "Random::GetInstance(): no Random instance available. Abort." );
	    exit(1);
	}

    return fInstance;
}
