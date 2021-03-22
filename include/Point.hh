#ifndef Point_hh
#define Point_hh

#include <vector>

#include "Space.hh"

class Point
{
private:
    Space::Type          fOriginalSpaceType;
    unsigned int         fDimension;
    std::vector<double>* fPhysicalCoordinates;
    std::vector<double>* fTranslatedCoordinates;
    std::vector<double>* fRotatedCoordinates;
    Space*               fPhysicalSpace;
    
public:
    Point( Space* space );
    ~Point();

    void GenerateRandomPosition();
    
    unsigned int GetDimension(){ return fDimension; };

    double GetPhysical( unsigned int i ){ return fPhysicalCoordinates->at(i); };
};
#endif
