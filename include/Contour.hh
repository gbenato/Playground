#ifndef Contour_hh
#define Contour_hh

#include "eigen3/Eigen/Eigen"

class Point;

class Contour
{
    
private:
    Point*           fPoint;
    Eigen::MatrixXd* fEllipsoidMatrix;
    Eigen::MatrixXd* fEigenvectorMatrix;
    Eigen::VectorXd* fMean;
    double           fVolume;
    double           fNSigma;
    double           fHeight;
    double           fIntegral;// Volume of n-dim ellipsoid times contour height
    bool             fIntegralComputed;

    void ComputeVolume();
    
public:
    Contour( Point*           point,
	     Eigen::MatrixXd* ellipsoidmatrix,
	     Eigen::MatrixXd* eigenvectormatrix,
	     Eigen::VectorXd* mean );
    Contour( const Contour& other );
    ~Contour();

    // Operators
    Contour& operator = ( Contour const& other );
    bool     operator < ( const Contour& other ) const;
    
    void ComputeIntegral();

    // Getters
    Point*           GetPoint            () const { return fPoint;             };
    Eigen::MatrixXd* GetEllipsoidMatrix  () const { return fEllipsoidMatrix;   };
    Eigen::MatrixXd* GetEigenvectorMatrix() const { return fEigenvectorMatrix; };
    Eigen::VectorXd* GetMean             () const { return fMean;              };
    double           GetHeight           () const { return fHeight;            };
    double           GetNSigma           () const { return fNSigma;            };
    double           GetVolume           () const { return fVolume;            };
    double           GetIntegral         () const { return fIntegral;          };
    bool             IsIntegralComputed  () const { return fIntegralComputed;  };
    
};

#endif
