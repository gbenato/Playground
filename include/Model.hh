#ifndef Model_hh
#define Model_hh

class Space;
class Point;

class Model
{
    
protected:
    Space* fPhysicalSpace;
    
public:
    Model();
    ~Model();
    
    virtual void   Initialize()                      = 0;
    virtual double MeasureLikelihood( Point* point ) = 0;
    virtual double MeasurePrior( Point* point );

    Space* GetPhysicalSpace(){ return fPhysicalSpace; };
};

#endif
