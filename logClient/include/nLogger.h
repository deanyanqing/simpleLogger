/*
 * nLogger.h
 *
 *  Created on: Jul 23, 2015
 *      Author: haf
 */

#ifndef LOGGING_NLOGGER_H_
#define LOGGING_NLOGGER_H_


#include <string>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <libgen.h>
#include "loggingDef.h"
namespace haf_logging
{

class NLogger;
extern NLogger* gLogger;

std::string basename( std::string const& pathname );

#define NLOG(severityLevel)   \
    BOOST_LOG_SEV( *(gLogger->getLogger()), severityLevel) \
  << basename( std::string(__FILE__)) << ":"<< __LINE__  << " " <<  __func__  << "[" << severityLevelDescriptions[static_cast<int>(severityLevel)]  << "] "

#define FATAL_LOG() \
    BOOST_LOG_SEV( *(gLogger->getLogger()), SeverityLevel::fatal) \
    << basename( std::string(__FILE__)) << ":"<< __LINE__  << " " <<  __func__  << "[" << severityLevelDescriptions[static_cast<int>(SeverityLevel::fatal)]  << "] "


struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\' || ch == '/';
    }
};



class NLogger
{
public:
  NLogger()=delete;
  ~NLogger()=default;
  NLogger(std::string logFile,std::string moduleName);

  boost::shared_ptr< src::severity_logger< SeverityLevel > > getLogger(){return slg;}
  void changeLogFilter(SeverityLevel level);
private:
  void init_logging();


private:
  boost::shared_ptr< src::severity_logger< SeverityLevel > > slg;

};

} /* namespace haf_logging */

#endif /* LOGGING_NLOGGER_H_ */
