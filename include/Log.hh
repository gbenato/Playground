#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>

class Log
{

 public:
    enum LogLevel{
	kNothing, // Print nothing
	kError,   // Print only errors
	kWarning, // Print only warnings and errors
	kSummary, // Print only results summary, warnings, and errors
	kDebug    // Print everything, including debug info
    };

    Log();
    Log( Log::LogLevel loglevel );
    ~Log();

    static void OpenLog( Log::LogLevel loglevel=Log::kSummary );

    static void OpenLog( int loglevel );

    static void SetLogLevel( Log::LogLevel loglevel );

    static void Out( Log::LogLevel loglevel,
		     const std::string& message );

    static void Out( const std::string& message )
    {
	Out( Log::fLogLevel, message );
    }

    static void OutError(const std::string& message)
    {
	Out( kError, message );
    };

    static void OutWarning(const std::string& message)
    {
	Out( kWarning, message );
    };

    static void OutSummary(const std::string& message)
    {
	Out( kSummary, message );
    };

    static void OutDebug(const std::string& message)
    {
	Out( kDebug, message );
    };

    static std::string ToString(Log::LogLevel);

 private:
    static Log::LogLevel fLogLevel;

};

#endif
