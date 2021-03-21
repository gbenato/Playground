#ifndef Parameter_hh
#define Parameter_hh

#include "Variable.hh"

class Parameter: public Variable
{
    
private:
    Random*     fRandom;

public:
    Parameter();
    Parameter( std::string name,
	       double      min=-std::numeric_limits<double>::max(),
	       double      max=+std::numeric_limits<double>::max(),
	       std::string unit="none" );
    ~Parameter();
    
    double GenerateRandom();
};

#endif
