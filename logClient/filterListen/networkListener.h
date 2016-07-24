/*
 * networkListener.h
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCLIENT_FILTERLISTEN_NETWORKLISTENER_H_
#define LOGGING_LOGCLIENT_FILTERLISTEN_NETWORKLISTENER_H_
#include "baseLogFilterListener.h"
class NetworkListener: public BaseLogFilterListener {
public:
	NetworkListener(std::string moduleName, std::function<void(SeverityLevel)>);
	NetworkListener() = delete;
	~NetworkListener();

	void startListen();
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_NETWORKLISTENER_H_ */
