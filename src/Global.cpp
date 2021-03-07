#include "Global.hh"
#include "Log.hh"

bool Global::fUseROOT = true;

Global::Global()
{
#ifdef HAVE_ROOT
    fUseROOT = true;
#else
    fUseROOT = false;
#endif
}

Global::~Global()
{
    ;
}

void Global::Initialize()
{
#ifdef HAVE_ROOT
    fUseROOT = true;
#else
    fUseROOT = false;
#endif

    return;
}
