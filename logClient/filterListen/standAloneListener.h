/*
 * standAloneListener.h
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_
#define LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_
#include "baseLogFilterListener.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <memory>
#include <thread>
using namespace boost::interprocess;
/*
 * @class StandAloneListener
 * @brief Register myself to log Agent and receive the log setting from log Agent. Execute the callback after receiving log setting.
 *        Maintain its' shm to receive the log setting.
 *   Register   string: Register moduleName
 *   Unregister string: Unregister moduleName
 * */
class StandAloneListener: public BaseLogFilterListener {
public:
	StandAloneListener() = delete;
	/**@brief Constructor of stand alone lister
	 * @param moduleName: Use as unique id for current log client
	 * @param callback:
	 * @param level: Initialize  the log level
	 * */
	StandAloneListener(std::string moduleName,
			std::function<void(SeverityLevel)> callback, SeverityLevel level =
					SeverityLevel::info);

  ~StandAloneListener();
  virtual void startListen();

private:
	/** @brief Register myself to log Agent with module name.Module name should be unique
	 * */
	void registerMyself();
private:
	std::shared_ptr<std::thread> shmListenThread;
	std::shared_ptr<managed_shared_memory> sharedMemory;
	named_condition myShmConditonVar;
	named_mutex myShmMutex;
	bool running;

	uint currentLogSetting;

};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_ */
