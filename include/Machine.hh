#ifndef Machine_hh
#define Machine_hh

#include <vector>
#include <set>

#include "eigen3/Eigen/Eigen"

#ifdef HAVE_ROOT
#include "TH2D.h"
#include "TArrow.h"
#endif

class Model;
class Space;
class Point;
class Contour;

class Machine
{

private:
    Model*             fModel;
    Space*             fPhysicalSpace;
    unsigned int       fDimension;
    std::vector<Point> fPointList;
    unsigned int       fNPoints;
    Eigen::MatrixXd    fCovarianceMatrix;

    Eigen::VectorXd fWeightedMean;
    Eigen::MatrixXd fX;// Matrix of all mean-subtracted tested points
    Eigen::MatrixXd fX_T;// Transpose of fX
    Eigen::MatrixXd fW;// Unitary matrix with weights
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> fEigenSolver;

    std::vector<Point> fSpherePointList;
    unsigned int       fNSpherePoints;
    Eigen::MatrixXd    fEllipsoidMatrix;
    Eigen::MatrixXd    fEigenVectorMatrix;
    
    std::set<Contour> fContourList;
    
    void ComputeWeightedMean();
    void ComputeContourIntegrals();
    
public:
    Machine( Model* model );
    ~Machine();

    void GeneratePhysicalPoints( unsigned int n );
    void MeasureProbabilities();
    void ComputeCovarianceMatrix();
    void DiagonalizeCovarianceMatrix();
    void GeneratePointsInEllipsoid( unsigned int n );
    void UpdateContours();
    
#ifdef HAVE_ROOT
    TH2D* GetPhysicalPointsHisto();
    TArrow* GetPrincipalComponent( unsigned int i );
    TH2D* GetSpherePointsHisto();
#endif
};

#endif
