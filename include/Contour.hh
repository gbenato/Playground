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
    double           fArea;// This is actually the volume of the n-dimensional ellipsoid
    double           fNSigma;
    double           fHeight;
    double           fVolume;// This is the area (volume of n-dim ellipsoid) times its height
    bool             fVolumeComputed;

    void ComputeArea();
    
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
    
    void ComputeVolume();

    // Getters
    Point*           GetPoint            () const { return fPoint;             };
    Eigen::MatrixXd* GetEllipsoidMatrix  () const { return fEllipsoidMatrix;   };
    Eigen::MatrixXd* GetEigenvectorMatrix() const { return fEigenvectorMatrix; };
    Eigen::VectorXd* GetMean             () const { return fMean;              };
    double           GetHeight           () const { return fHeight;            };
    double           GetNSigma           () const { return fNSigma;            };
    double           GetArea             () const { return fArea;              };
    double           GetVolume           () const { return fVolume;            };
    bool             IsVolumeComputed    () const { return fVolumeComputed;    };
    
};

#endif
