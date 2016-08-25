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
#include "loggingDef.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

class BaseLogFilterListener;
struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\' || ch == '/';
    }
};


/** @brief Wrapper of boost log
 *  Create LogFiterListern Create LogFiterListern and  react to the log setting from log agent
 *  **/
class NLogger
{
public:
  NLogger()=delete;
  ~NLogger()=default;
  NLogger(std::string logFile,std::string moduleName,LogFilterListenType type);

  boost::shared_ptr< src::severity_logger< SeverityLevel > > getLogger(){return slg;}

private:
  /** @brief Callback to LogFiterListern to handle log level change
   *  @param level : Target log level
   *  */
  void changeLogFilter(SeverityLevel level);



  template< typename...Args >
  void log(SeverityLevel severity , Args...args);
private:
  void initLogging();

  template<typename First, typename...Rest >
    void printImpl(SeverityLevel severity,First parm1, Rest...parm);

private:
  boost::shared_ptr< src::severity_logger< SeverityLevel > > slg;
  std::shared_ptr<BaseLogFilterListener> logListener;

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
