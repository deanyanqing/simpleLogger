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

/*
 * @brief Listen on the setting from the user and invoke the callback
 * */
class BaseLogFilterListener
{
public:
  BaseLogFilterListener(std::string moduleName, std::function<void(SeverityLevel)>);
  BaseLogFilterListener()=delete;
  virtual ~BaseLogFilterListener();

  virtual void startListen()=0;
  inline void setGetServerityFun(std::function<SeverityLevel()> fun){getServerityLevel = fun;}

protected:
  void doFilter(std::string& module ,SeverityLevel);
  inline std::string& getModuleName(){return moduleName;}

private:
  std::function<void(SeverityLevel)> filterCallback;
  std::function<SeverityLevel()> getServerityLevel;
  std::string moduleName;
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_BASELOGFILTERLISTENER_H_ */
