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
namespace bip = boost::interprocess;
/*
 * @class StandAloneListener
 * @brief StandAlone log filter listen on shared_memory
 * Use 1 byte to indicate which log level to filter
 * */
class StandAloneListener:public BaseLogFilterListener
{
public:
  StandAloneListener()=delete;
  StandAloneListener(std::string moduleName, std::function<void(SeverityLevel)>);
  ~StandAloneListener();
  void startListen();

private:
  void initSharedMem();
  void listenLoop();
private:
  std::shared_ptr< bip::managed_shared_memory>  sharedMemory;
  std::thread shmListenThread;
};

#endif /* LOGGING_LOGCLIENT_FILTERLISTEN_STANDALONELISTENER_H_ */
