#ifndef RANDOM_HH
#define RANDOM_HH

#include "pcg_random.hpp"

class Random{
    
public:
    Random( int seed );
    ~Random();
    static Random* GetInstance();

    int GetSeed(){ return fSeed; };
    
private:
    static Random* fInstance;
    int fSeed;
};

#endif
