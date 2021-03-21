#ifndef Variable_hh
#define Variable_hh

#include <string>
#include <limits>

class Random;

class Variable
{

private:
    std::string fName;
    double      fMin;
    double      fMax;
    std::string fUnit;
    //Random*     fRandom;
    
public:

    Variable();
    Variable( std::string name,
	       double      min=-std::numeric_limits<double>::max(),
	       double      max=+std::numeric_limits<double>::max(),
	       std::string unit="none" );
    ~Variable();

    // Getters
    std::string GetName(){ return fName; };
    double      GetMin() { return fMin;  };
    double      GetMax() { return fMax;  };
    std::string GetUnit(){ return fUnit; };

    // Other methods
    double GenerateRandom();
    
};

#endif
