#include <functional>

#include "Random.hh"
#include "Log.hh"

Random* Random::fInstance = 0;

Random::Random( unsigned seed )
{
    fSeed = seed;
    if( fSeed == 0 )
	{
	    Log::OutWarning( "" );
	    Log::OutWarning( "Random seed set to zero!" );
	    Log::OutWarning( "" );
	}
    
    fMT       = std::mt19937( fSeed );
    fUniform  = std::uniform_real_distribution<>( 0., 1. );
    fGaussian = std::normal_distribution<>( 0., 1. );
    
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

double Random::GetUniform( double min,
			   double max )
{
    return min + (max-min) * fUniform( fMT );
}

double Random::GetGaussian( double mean,
			    double sigma,
			    double min,
			    double max )
{
    double value;
    do{
	value = mean + fGaussian( fMT ) * sigma;
    }
    while( value < min || value > max );

    return value;
}
