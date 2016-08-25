/*
 * LogCenterShmServer.h
 *
 *  Created on: Jul 28, 2016
 *      Author: qiwei
 */

#ifndef LOGAGENT_INCLUDE_LOGCENTERSHMMANAGER_H_
#define LOGAGENT_INCLUDE_LOGCENTERSHMMANAGER_H_

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <memory>
#include <thread>
#include <string>
#include <map>
using namespace boost::interprocess;

typedef int LogLevel;

class BaseLogProcessManager
{
public:
    virtual bool handleLogUpdate(std::string&, LogLevel)=0;
};
/**@brief Act as shared memory server. Handle updating  level request from command line.
 * Dispatch the request to the real log competent
 **/
class LogCenterShmManager
{
public:
    LogCenterShmManager();
    virtual ~LogCenterShmManager();

    virtual bool handleLogUpdate(std::string&, LogLevel);
    virtual LogLevel getlogLevel(std::string&);
private:
    /**@brief Handler the client register request. Check the shared memory periodical
     * */
    void shmRegisterListernProc();

private:
    std::shared_ptr<managed_shared_memory> sharedMemory;
    named_mutex myShmMutex;
    std::shared_ptr<std::thread> shmListenThread;
    bool running;

    std::map<std::string, int> clients;
};

#endif /* LOGAGENT_INCLUDE_LOGCENTERSHMMANAGER_H_ */
