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
#include "loggingConstantDef.h"
#include "nLogger.h"


class NLogger;
extern NLogger* gLogger;


std::string basename( std::string const& pathname );

/* @brief Write the log
 * usage : NLOG(SeverityLevel::trace) << "" << ""
 */

#define NLOG(severityLevel)   \
    BOOST_LOG_SEV( *(gLogger->getLogger()), severityLevel) \
  << basename( std::string(__FILE__)) << ":"<< __LINE__ << "<" << severityLevelDescriptions[static_cast<int>(severityLevel)]  << "> "

#define FATAL_LOG() \
    BOOST_LOG_SEV( *(gLogger->getLogger()), SeverityLevel::fatal) \
    << basename( std::string(__FILE__)) << ":"<< __LINE__  << "<" << severityLevelDescriptions[static_cast<int>(SeverityLevel::fatal)]  << "> "



extern const std::vector<std::string> severityLevelDescriptions ;

#endif /* HAF_LOGGING_LOGGINGDEF_H_ */
