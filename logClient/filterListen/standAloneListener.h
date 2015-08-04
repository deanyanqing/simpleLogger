/*
 * standAloneListener.h
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_
#define LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_
#include "baseLogFilterListener.h"
class StandAloneListener:public BaseLogFilterListener
{
public:
  StandAloneListener();
  ~StandAloneListener();
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_ */
