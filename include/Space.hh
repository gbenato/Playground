#ifndef Space_hh
#define Space_hh

#include <vector>

#include "Variable.hh"

class Space
{

public:
    enum Type{ kPhysical, kTransformed };
    
private:
    std::string           fName;
    Type                  fType;
    unsigned int          fDimension;
    std::vector<Variable> fVariableList;
    
    
public:
    Space( std::string  name,
	   Type         type=kPhysical,
	   unsigned int dimension=0 );
    ~Space();

    void AddVariable( std::string name,
		      double      min=-std::numeric_limits<double>::max(),
		      double      max=+std::numeric_limits<double>::max(),
		      std::string unit="none" );
    
    void AddVariable( Variable& variable );

    std::vector<double>* GenerateRandomPosition();

    // Getters
    Type         GetType()     { return fType;      };
    unsigned int GetDimension(){ return fDimension; };
};

#endif
