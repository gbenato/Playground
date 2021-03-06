#include "Log.hh"

#include <iostream>

Log::LogLevel Log::fLogLevel = Log::kSummary;

Log::Log()
{
    fLogLevel = Log::kSummary;
}

Log::Log( Log::LogLevel loglevel )
{
    fLogLevel = loglevel;
}

Log::~Log()
{
    ;
}

void Log::OpenLog( Log::LogLevel loglevel )
{

    Log::SetLogLevel( loglevel );
    
    return;
}

void Log::OpenLog( int loglevel )
{
    Log::SetLogLevel( static_cast<LogLevel>(loglevel) );

    return;
}

void Log::SetLogLevel( Log::LogLevel loglevel )
{

    fLogLevel = loglevel;

    return;
}

void Log::Out( Log::LogLevel loglevel, const std::string& message )
{

    if( Log::fLogLevel >= loglevel ){

	if( loglevel == Log::LogLevel::kError )
	    std::cout << "\033[1;31m";
	else if( loglevel == Log::LogLevel::kWarning )
	    std::cout << "\033[1;34m";
	else if( loglevel == Log::LogLevel::kDebug )
	    std::cout << "\033[32m";

	std::cout << Log::ToString(loglevel) << message;
	std::cout << "\033[0m"<< std::endl;
    }

}


std::string Log::ToString( Log::LogLevel loglevel )
{

    switch (loglevel) {
    case kDebug:
	return "Debug   : ";
    case kSummary:
	return "Summary : ";
    case kWarning:
	return "Warning : ";
    case kError:
	return "Error   : ";
    default:
	return "";
    }
}
