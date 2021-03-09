#ifndef Parameter_hh
#define Parameter_hh

#include <string>
#include <limits>

class Random;

class Parameter
{

public:
    enum PriorType{ kNone, kFlat, kGaussian, kPoisson, kEnlargedPoisson, kBinomial };
    
private:
    std::string fName;
    double      fMin;
    double      fMax;
    std::string fUnit;
    bool        fPriorSet;
    PriorType   fPriorType;
    double      fMean;
    double      fStdDev;
    Random*     fRandom;
    
public:

    Parameter();
    Parameter( std::string name,
	       double      min=-std::numeric_limits<double>::max(),
	       double      max=+std::numeric_limits<double>::max(),
	       std::string unit="none" );
    ~Parameter();

    // Setters
    void SetPrior( PriorType priortype,
		   double    mean=0.,
		   double    stddev=0. );
    
    // Getters
    std::string GetName(){ return fName; };
    double      GetMin() { return fMin;  };
    double      GetMax() { return fMax;  };
    std::string GetUnit(){ return fUnit; };

    // Other methods
    double GenerateRandom();
    
};

#endif
