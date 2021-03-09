#include "Log.hh"
#include "Random.hh"
#include "Variable.hh"

Variable::Variable()
{

    fName = "";
    fMin  = 0.;
    fMax  = 0.;
    fUnit = "none";

    fRandom = Random::GetInstance();

}

Variable::Variable( std::string name,
		      double      min,
		      double      max,
		      std::string unit )
{
    fName     = name;
    fMin      = min;
    fMax      = max;
    fUnit     = unit;

    Log::OutDebug( "" );
    Log::OutDebug( "Created variable: " + fName );
    Log::OutDebug( "           range: [" +
		   std::to_string(fMin) + "," +
		   std::to_string(fMax) + "] " + fUnit );
    Log::OutDebug( "" );

    fRandom = Random::GetInstance();

}

Variable::~Variable()
{
    ;
}

double Variable::GenerateRandom()
{
    return fRandom->GetUniform( fMin, fMax );
}
