#ifndef RANDOM_HH
#define RANDOM_HH

//#include "pcg_random.hpp"

#include <random>

class Random{
    
public:
    Random( unsigned seed );
    ~Random();
    static Random* GetInstance();

    unsigned GetSeed(){ return fSeed; };
    double   GetUniform( double min=0.,
			 double max=1. );
    double   GetGaussian( double mean=0.,
			  double sigma=1.,
			  double min=-std::numeric_limits<double>::max(),
			  double max=+std::numeric_limits<double>::max() );
    
private:
    static Random* fInstance;
    unsigned       fSeed;
    
    std::mt19937                     fMT;
    std::uniform_real_distribution<> fUniform;
    std::normal_distribution<>       fGaussian;
};

#endif
