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
class StandAloneListener:public BaseLogFilterListener
{
public:
  StandAloneListener()=delete;
  StandAloneListener(std::string moduleName, std::function<void(SeverityLevel)>, SeverityLevel level = info);
  ~StandAloneListener();
  virtual void startListen();


private:
  /** @brief Register myself to log Agent with my client id and shm address
   *  @param clientId: Unique client id. Log agent use this to distinguish different client
   * */
  void registerMyself(const std::string& clientId);
  void listenLoop();
private:
  std::thread shmListenThread;
  std::shared_ptr<managed_shared_memory> sharedMemory;
  std::string moduleName;
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_ */
