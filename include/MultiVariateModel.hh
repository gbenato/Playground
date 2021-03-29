#ifndef MultiVariateModel_hh
#define MultiVariateModel_hh

#include "Model.hh"

#include "eigen3/Eigen/Eigen"

class Random;
class Point;

class MultiVariateModel : public Model
{

private:
    unsigned int fDimension;
    Random*      fRandom;
    Eigen::Matrix2d fRotation;
    Eigen::Matrix2d fInverseRotation;
    Eigen::Vector2d fMean;
    Eigen::Vector2d fRotatedMean;
    Eigen::Vector2d fSigma;
    Eigen::Vector2d fRotatedSigma;

public:
    MultiVariateModel( unsigned int dimension=2 );
    ~MultiVariateModel();
    
    void   Initialize();
    double MeasureLikelihood( Point* point );
    //double MeasurePrior();

};

#endif
