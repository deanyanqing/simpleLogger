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


/*The default log file name*/
#define DEFAUNT_FILE ".haflog"

enum class LogFilterListenType {
	LOG_FILTER_STANDALONE, LOG_FILTER_NETWORK
};
enum class SeverityLevel {
	trace, debug, info, warning, error, fatal
};
static const std::vector<std::string> severityLevelDescriptions = { "trace",
		"debug", "info", "warning", "error", "fatal" };

std::string basename( std::string const& pathname );

/* @brief Write the log
 * usage : NLOG(SeverityLevel::trace) << "" << ""
 */
#define NLOG(logger,severityLevel)   \
    BOOST_LOG_SEV( *(logger), severityLevel) \
  << basename( std::string(__FILE__)) << ":"<< __LINE__ << "<" << severityLevelDescriptions[static_cast<int>(severityLevel)]  << "> "

#define FATAL_LOG(logger) \
    BOOST_LOG_SEV( *(logger), SeverityLevel::fatal) \
    << basename( std::string(__FILE__)) << ":"<< __LINE__  << "<" << severityLevelDescriptions[static_cast<int>(SeverityLevel::fatal)]  << "> "

/***
 * define other log level macro
 *
 * */



#endif /* HAF_LOGGING_LOGGINGDEF_H_ */
