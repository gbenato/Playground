#include "Log.hh"
#include "Random.hh"
#include "Variable.hh"

Variable::Variable()
{

    fName = "";
    fMin  = 0.;
    fMax  = 0.;
    fUnit = "none";

    fPriorSet  = false;
    fPriorType = PriorType::kNone;
    fMean      = 0.;
    fStdDev    = 0.;

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
    
    fPriorSet  = false;
    fPriorType = PriorType::kNone;
    fMean      = 0.;
    fStdDev    = 0.;

    fRandom = Random::GetInstance();

}

Variable::~Variable()
{
    ;
}

void Variable::SetPrior( PriorType priortype,
			  double    mean,
			  double    stddev )
{
    if( fPriorSet )
	{
	    Log::OutError( "Prior for variable " + fName + " already set. Abort." );
	    
	    exit(1);
	}

    fPriorType = priortype;
    fMean      = mean;
    fStdDev    = stddev;

    Log::OutDebug( "" );
    Log::OutDebug( "Set prior for variable: " + fName );
    if( fPriorType == PriorType::kFlat )
	Log::OutDebug( "            prior type: Flat" );
    else if( fPriorType == PriorType::kGaussian )
	Log::OutDebug( "            prior type: Gaussian" );
    else if( fPriorType == PriorType::kPoisson )
	Log::OutDebug( "            prior type: Poisson" );
    else if( fPriorType == PriorType::kEnlargedPoisson )
	Log::OutDebug( "            prior type: EnlargedPoisson" );
    else if( fPriorType == PriorType::kBinomial )
	Log::OutDebug( "            prior type: Binomial" );
    Log::OutDebug( "                  mean: " + std::to_string( fMean ) );
    Log::OutDebug( "    standard deviation: " + std::to_string( fStdDev ) );
    Log::OutDebug( "" );
    
    fPriorSet = true;
    return;
}

double Variable::GenerateRandom()
{
    return fRandom->GetUniform( fMin, fMax );
}