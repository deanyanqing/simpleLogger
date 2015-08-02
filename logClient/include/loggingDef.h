/*
 * loggingDef.h
 *
 *  Created on: Jul 23, 2015
 *      Author: haf
 */

#ifndef HAF_LOGGING_LOGGINGDEF_H_
#define HAF_LOGGING_LOGGINGDEF_H_

#include <string>
#include <vector>

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>

#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace haf_logging
{

enum class LoggerType
{
  LOCAL_LOGER,
  REMOTE_LOGER
};

enum class SeverityLevel
{
  trace,
  debug,
  info,
  warning,
  error,
  fatal
};

/**/
extern const std::vector<std::string> severityLevelDescriptions ;

} /* namespace haf_logging */
#endif /* HAF_LOGGING_LOGGINGDEF_H_ */
