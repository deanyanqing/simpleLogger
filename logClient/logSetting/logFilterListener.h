/*
 * logFilterListener.h
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCLIENT_FILTERLISTEN_LOGFILTERLISTENER_H_
#define LOGGING_LOGCLIENT_FILTERLISTEN_LOGFILTERLISTENER_H_
#include <memory>
#include <vector>
#include "baseLogFilterListener.h"

class LogFilterListener
{
public:
  LogFilterListener();
  ~LogFilterListener();


private:
std::vector<std::shared_ptr<BaseLogFilterListener> > filterListeners;
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_LOGFILTERLISTENER_H_ */
