/*
 * nLogger.h
 *
 *  Created on: Jul 23, 2015
 *      Author: haf
 */

#ifndef LOGGING_NLOGGER_H_
#define LOGGING_NLOGGER_H_

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <libgen.h>

#include <string>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

enum class SeverityLevel
{
  trace,
  debug,
  info,
  warning,
  error,
  fatal
};


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



  template< typename...Args >
  void log(SeverityLevel severity , Args...args);
private:
  void init_logging();

  template<typename First, typename...Rest >
    void printImpl(SeverityLevel severity,First parm1, Rest...parm);

private:
  boost::shared_ptr< src::severity_logger< SeverityLevel > > slg;

};

/*
template< typename...Args >
void NLogger::log(SeverityLevel severity , Args...args)
{

  BOOST_LOG_SEV((*slg), severity) << basename( std::string(__FILE__)) << ":"<< __LINE__ << " <" << severityLevelDescriptions[static_cast<int>(severity)]  << "> " ;
  printImpl(severity,args...);
}


template<typename First, typename...Rest >
void NLogger::printImpl(SeverityLevel severity, First parm1, Rest...parm)
{
  BOOST_LOG_SEV((*slg), severity) <<parm1;
  printImpl(severity,parm...);
}
*/


#endif /* LOGGING_NLOGGER_H_ */
