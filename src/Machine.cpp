#include "Machine.hh"
#include "Log.hh"
#include "Model.hh"
#include "Space.hh"
#include "Point.hh"
#include "Global.hh"

#include <iostream>
#include <iomanip>

Machine::Machine( Model* model )
{
    fModel         = model;
    fPhysicalSpace = fModel->GetPhysicalSpace();
    fDimension     = fPhysicalSpace->GetDimension();
    fNPoints       = 0;
}

Machine::~Machine()
{
    ;
}

void Machine::GeneratePhysicalPoints( unsigned int n )
{
    if( n < fDimension )
	{
	    Log::OutError( "Machine::GeneratePhysicalPoints(): n must be >= dimension. Abort." );
	    exit(1);
	}

    for( unsigned int i=0; i<n; i++ )
	{
	    fPointList.push_back( Point( fPhysicalSpace ) );
	    fPointList.back().GenerateRandomPosition();
	}
    fNPoints = fPointList.size();
    
    return;
}

void Machine::MeasureProbabilities()
{
    for( unsigned int i=0; i<fNPoints; i++ )
	if( fPointList[i].GetPosteriorProbability() < Global::epsilon )
	    {
		fPointList[i].SetLikelihood          ( fModel->MeasureLikelihood(&fPointList[i]) );
		fPointList[i].SetPriorProbability    ( fModel->MeasurePrior(&fPointList[i])      );
		fPointList[i].SetPosteriorProbability( fPointList[i].GetLikelihood() *
						       fPointList[i].GetPriorProbability()       );
	    }

    return;
}

void Machine::ComputeWeightedMean()
{

    fW = Eigen::MatrixXd( fNPoints, fNPoints );
    for( unsigned int i=0; i<fNPoints; i++ )
	fW(i,i) = fPointList[i].GetPosteriorProbability();

    fWeightedMean = Eigen::VectorXd(fDimension);
    for( unsigned int i=0; i<fDimension; i++ )
	fWeightedMean(i) = 0.;
    for( unsigned int i=0; i<fNPoints; i++ )
	fWeightedMean += fPointList[i].GetPhysical() * fPointList[i].GetPosteriorProbability();
    fWeightedMean /= fW.trace();

    return;
}

void Machine::ComputeCovarianceMatrix()
{
    ComputeWeightedMean();

    fX = Eigen::MatrixXd( fDimension, fNPoints );
    for( unsigned int i=0; i<fNPoints; i++ )
	fX.col(i) = fPointList[i].GetPhysical() - fWeightedMean;
    
    fX_T               = fX.transpose();
    fCovarianceMatrix  = fX * fW * fX_T;
    fCovarianceMatrix /= fW.trace();
    
    return;
}

void Machine::DiagonalizeCovarianceMatrix()
{

    fEigenSolver = Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd>(fCovarianceMatrix);

    if( fEigenSolver.info() != Eigen::Success )
	    Log::OutWarning( "Machine::DiagonalizeCovarianceMatrix(): diagonalization failed." );

    std::cout << fEigenSolver.eigenvalues()  << std::endl;
    std::cout << fEigenSolver.eigenvectors() << std::endl;
    
    return;
}

void Machine::GeneratePointsInEllipsoid( unsigned int n )
{
    Eigen::MatrixXd ellipsoidmatrix = Eigen::MatrixXd::Constant( fDimension, fDimension, 0. );
    for( unsigned int i=0; i<fDimension; i++ )
	//ellipsoidmatrix(i,i) = pow( fEigenSolver.eigenvalues()(i), 2. );
	ellipsoidmatrix(i,i) = fEigenSolver.eigenvalues()(i);

    Eigen::MatrixXd eigenvectors = fEigenSolver.eigenvectors();
    
     for( unsigned int i=0; i<n; i++ )
	{
	    fSpherePointList.push_back( Point( fPhysicalSpace ) );
	    fSpherePointList.back().GeneratePositionInEllipsoid( &ellipsoidmatrix,
								 &eigenvectors,
								 &fWeightedMean );
	}
    fNSpherePoints = fSpherePointList.size();   
    return;
}

#ifdef HAVE_ROOT
TH2D* Machine::GetPhysicalPointsHisto()
{
    TH2D* histo = new TH2D( "histo", "histo",
			    100, fPhysicalSpace->GetMinRange(0), fPhysicalSpace->GetMaxRange(0),
			    100, fPhysicalSpace->GetMinRange(1), fPhysicalSpace->GetMaxRange(1));
    
    for( unsigned int i=0; i<fNPoints; i++ )
	histo->Fill( fPointList[i].GetPhysical(0),
		     fPointList[i].GetPhysical(1),
		     fPointList[i].GetPosteriorProbability() );
    return histo;
}

TArrow* Machine::GetPrincipalComponent( unsigned int i )
{
    TArrow* pc = new TArrow( fWeightedMean(0),
			     fWeightedMean(1),
			     fWeightedMean(0) + fEigenSolver.eigenvectors().col(i)(0),
			     fWeightedMean(1) + fEigenSolver.eigenvectors().col(i)(1) );
    return pc;
}

TH2D* Machine::GetSpherePointsHisto()
{
    TH2D* histo = new TH2D( "sphere", "sphere",
			    1000, fPhysicalSpace->GetMinRange(0), fPhysicalSpace->GetMaxRange(0),
			    1000, fPhysicalSpace->GetMinRange(1), fPhysicalSpace->GetMaxRange(1) );


    for( unsigned int i=0; i<fNSpherePoints; i++ )
	histo->Fill( fSpherePointList[i].GetPhysical(0),
		     fSpherePointList[i].GetPhysical(1) );

    return histo;
}
#endif
