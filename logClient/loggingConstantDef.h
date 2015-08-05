/*
 * loggingConstantDef.h
 *
 *  Created on: Aug 5, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGGINGCONSTANTDEF_H_
#define LOGGING_LOGGINGCONSTANTDEF_H_

enum class SeverityLevel
{
  trace,
  debug,
  info,
  warning,
  error,
  fatal
};

/*The default log file name*/
#define DEFAUNT_FILE ".haflog"

#endif /* LOGGING_LOGGINGCONSTANTDEF_H_ */
