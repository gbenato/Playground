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

    static constexpr double epsilon = 1.e-20;
};

#endif
