#ifndef GLOBAL_HH
#define GLOBAL_HH

class Global
{
private:
    static bool fUseROOT;

public:
    
    Global();
    ~Global();
    static void Initialize();

    static bool UseROOT(){ return fUseROOT; };

};

#endif
