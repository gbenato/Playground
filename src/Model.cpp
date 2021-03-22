#include "Log.hh"
#include "Model.hh"
#include "Space.hh"

Model::Model()
{
    fPhysicalSpace = new Space( "PhysicalSpace" );
}

Model::~Model()
{
    ;
}

double Model::MeasurePrior( Point* point )
{
    return 1.;
}
