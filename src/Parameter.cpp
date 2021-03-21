#include "Log.hh"
#include "Random.hh"
#include "Parameter.hh"

Parameter::Parameter():
    Variable()
{
    fRandom = Random::GetInstance();
}

Parameter::Parameter( std::string name,
		      double      min,
		      double      max,
		      std::string unit ):
    Variable( name,
	      min,
	      max,
	      unit )
{
    fRandom = Random::GetInstance();
}

Parameter::~Parameter()
{
    ;
}

double Parameter::GenerateRandom()
{
    Log::OutDebug( "Range for parameter " + GetName() + ": "
		   + std::to_string(GetMin()) + "\t" + std::to_string(GetMax()));
    return fRandom->GetUniform( GetMin(), GetMax() );
}
