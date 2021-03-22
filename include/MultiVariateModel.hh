#ifndef MultiVariateModel_hh
#define MultiVariateModel_hh

#include "Model.hh"

class Random;
class Point;

class MultiVariateModel : public Model
{

private:
    unsigned int fDimension;
    double*      fMean;
    double*      fSigma;
    Random*      fRandom;

public:
    MultiVariateModel( unsigned int dimension=2 );
    ~MultiVariateModel();
    
    void   Initialize();
    double MeasureLikelihood( Point* point );
    //double MeasurePrior();

};

#endif
