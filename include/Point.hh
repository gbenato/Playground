#ifndef Point_hh
#define Point_hh

#include <vector>

#include "eigen3/Eigen/Eigen"

#include "Log.hh"
#include "Space.hh"

class Random;

class Point
{
private:
    Space::Type          fOriginalSpaceType;
    unsigned int         fDimension;
    Eigen::VectorXd      fPhysicalCoordinates;
    Eigen::VectorXd      fRotatedCoordinates;
    //std::vector<double>* fPhysicalCoordinates;
    //std::vector<double>* fTranslatedCoordinates;
    //std::vector<double>* fRotatedCoordinates;
    Space*               fPhysicalSpace;
    double               fLikelihood;
    double               fPriorProbability;
    double               fPosteriorProbability;
    bool                 fMeasuredProbability;
    Random*              fRandom;

    void GeneratePositionInSphere();
    
public:
    Point( Space* space );
    ~Point();

    void GenerateRandomPosition();
    void GeneratePositionInEllipsoid( Eigen::MatrixXd* ellipsoidmatrix,
				      Eigen::MatrixXd* rotation,
				      Eigen::VectorXd* translation );
    //void GenerateFixedPosition( std::vector<double>* pos );
    void ComputeTransformedCoordinates( Eigen::MatrixXd* ellipsoidmatrix,
					Eigen::MatrixXd* rotation,
					Eigen::VectorXd* translation );
    
    // Operators
    Point operator + (Point &obj)
    {
	Point res(fPhysicalSpace);
	
	for( unsigned int i=0; i<fDimension; i++ )
	    res.fPhysicalCoordinates = fPhysicalCoordinates + obj.GetPhysical();
	
	return res;
    }
    /*
    Point operator + (Point &obj)
    {
	Point res(fPhysicalSpace);
	if( obj.GetDimension() != fDimension )
	    {
		Log::OutError( "Point operator +: cannot apply to points of different dimension. Abort." );
		exit(1);
	    }
	
	for( unsigned int i=0; i<fDimension; i++ )
	    res.fPhysicalCoordinates->at(i) = fPhysicalCoordinates->at(i) + obj.GetPhysical(i);
	
	return res;
    }
    */
    // Getters
    Space::Type     GetOriginalSpaceType   ()                { return fOriginalSpaceType;      };
    unsigned int    GetDimension           ()                { return fDimension;              };
    double          GetPhysical            ( unsigned int i ){ return fPhysicalCoordinates(i); };
    Eigen::VectorXd GetPhysical            ()                { return fPhysicalCoordinates;    };
    double          GetRotated             ( unsigned int i ){ return fRotatedCoordinates(i);  };
    double          GetLikelihood          ()                { return fLikelihood;             };
    double          GetPriorProbability    ()                { return fPriorProbability;       };
    double          GetPosteriorProbability()                { return fPosteriorProbability;   };
    bool            IsProbabilityMeasured  ()                { return fMeasuredProbability;    };

    // Setters
    void SetLikelihood          ( double value ){ fLikelihood           = value; };
    void SetPriorProbability    ( double value ){ fPriorProbability     = value; };
    void SetPosteriorProbability( double value ){ fPosteriorProbability = value; };
    void SetMeasuredProbability (              ){ fMeasuredProbability  = true;  };
    
};
#endif
