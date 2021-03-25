#include "Global.hh"
#include "Log.hh"
#include "MultiVariateModel.hh"
#include "Random.hh"
#include "Space.hh"
#include "Point.hh"
#include "Machine.hh"

#ifdef HAVE_ROOT
#include "TApplication.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TArrow.h"
#endif


int main()
{

    int verbosity = 4;
    Log::OpenLog( verbosity );

    Global::Initialize();

    unsigned seed = 4;
    Random rdm(seed);
    
    MultiVariateModel* model = new MultiVariateModel();
    /*
    Space*             space = model->GetPhysicalSpace();
    for( int i=0; i<100; i++ )
	{
	    Point point( space );
	    point.GenerateRandomPosition();
	    Log::OutDebug( "Likelihood: " + std::to_string( model->MeasureLikelihood( &point ) ) );
	}
    */
    Machine* machine = new Machine( model );
    machine->GeneratePhysicalPoints( 100 * model->GetPhysicalSpace()->GetDimension() );
    machine->MeasureProbabilities();
    machine->ComputeCovarianceMatrix();
    machine->DiagonalizeCovarianceMatrix();
    machine->GeneratePointsInEllipsoid( 100000 );

#ifdef HAVE_ROOT
    TH2D* histo = machine->GetPhysicalPointsHisto();
    TArrow* pc0 = machine->GetPrincipalComponent(0);
    TArrow* pc1 = machine->GetPrincipalComponent(1);
    pc1->SetLineColor(2);

    TH2* sphere = machine->GetSpherePointsHisto();
    
    int   mickey = 0;
    char* mouse[10];
    TApplication *app = new TApplication( "App", &mickey, mouse );
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    TCanvas* can = new TCanvas("can","can",800,800);
    can->Divide(2,1);

    can->cd(1);
    can->SetLogz();
    histo->Draw("col");
    pc0->Draw("SAME");
    pc1->Draw("SAME");

    can->cd(2);
    sphere->Draw("col");
    
    app->Run(kTRUE);
#endif
    
    Log::OutSummary( "Everything done." );
    
    return 0;
}
