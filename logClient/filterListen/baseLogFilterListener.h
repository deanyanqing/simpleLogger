/*
 * baseLogFilterListener.h
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCLIENT_FILTERLISTEN_BASELOGFILTERLISTENER_H_
#define LOGGING_LOGCLIENT_FILTERLISTEN_BASELOGFILTERLISTENER_H_

#include "nLogger.h"
#include <functional>
class BaseLogFilterListener
{
public:
  BaseLogFilterListener(std::string moduleName, std::function<void(SeverityLevel)>);
  BaseLogFilterListener()=delete;
  virtual ~BaseLogFilterListener();

  virtual void statListen()=0;

protected:
  void doFilter(std::string& module ,SeverityLevel);
  bool isTarget(std::string& );
private:
  std::function<void(SeverityLevel)> filterCallback;
  std::string moduleName;
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_BASELOGFILTERLISTENER_H_ */
