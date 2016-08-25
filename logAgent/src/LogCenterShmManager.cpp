/*
 * LogCenterShmServer.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: qiwei
 */

#include "LogCenterShmManager.h"

#include <boost/interprocess/sync/named_mutex.hpp>
#include <mutex>
#include <chrono>
#include <regex>
#include <utility>

const static std::string REGISTER_LOG_SHM("RegisterLogClientShm");
const static char* NAME_OF_STRING_IN_SHM = "StringOfShm";
const static char* MUTEX_REGISTER_LOG_SHM = "MutexForRegisterLogShm";
const static uint SHARED_MEMORY_SIZE = 1024;
const static char* LOG_LEVEL_NAME = "LogLevel";
const static char* MUTEX_POSTFIX ="mutex";
const static char* COND_VAR_POSTFIX = "cnd";
const static uint CHECK_INTERVAL = 10;

///todo :Name rule follow boost/std, underscore is consistent

LogCenterShmManager::LogCenterShmManager() :
        myShmMutex(open_or_create,
                std::string(MUTEX_REGISTER_LOG_SHM + MUTEX_POSTFIX).c_str())
{
    sharedMemory = std::make_shared<managed_shared_memory>(create_only,
            REGISTER_LOG_SHM.c_str(), SHARED_MEMORY_SIZE);

    std::pair<std::string *, std::size_t> ret = sharedMemory->find_or_construct<
            std::string>(NAME_OF_STRING_IN_SHM)(static_cast<std::string>(""));
    running = true;
    shmListenThread = std::make_shared<std::thread>(
            &LogCenterShmManager::shmRegisterListernProc, this);
}

LogCenterShmManager::~LogCenterShmManager()
{
    running = false;
    shmListenThread->join();
}

static inline bool readClientLogSetting(std::string clientName, LogLevel log)
{
    bool res = true;
    int logLevel = 0;
    std::string mutexName = clientName + MUTEX_POSTFIX;
    try
    {
        managed_shared_memory register_shm(open_only, clientName.c_str());

        named_mutex shm_mutex(open_only, mutexName.c_str());
        shm_mutex.lock();

        uint* logLevel = register_shm.find<int>(LOG_LEVEL_NAME);
        if (logLevel)
        {
            log = *logLevel;
        }
        else
        {
            res = false;
        }

        shm_mutex.unlock();

    } catch (...)
    {
        res = false;
    }
    return res;
}

static inline bool writeLogLevel(std::string client, LogLevel level)
{
    bool res = true;
    int logLevel = 0;
    std::string mutexName = client + MUTEX_POSTFIX;
    std::string condVarName = client + COND_VAR_POSTFIX;
    try
    {
        managed_shared_memory register_shm(open_only, client.c_str());

        named_mutex shm_mutex(open_only, mutexName.c_str());
        named_condition shmCondVar(open_only, condVarName.c_str());
        shm_mutex.lock();

        uint* logLevel = register_shm.find<int>(LOG_LEVEL_NAME);

        if (logLevel)
        {
            logLevel = level;
            //Actually should be only one thread waiting
            shmCondVar.notify_all();
        }
        else
        {
            res = false;
        }

        shm_mutex.unlock();

    } catch (...)
    {
        res = false;
    }
    return res;
}

/** No condition variable for register shared memory.Shared Memory server will check the memory by timer*/
void LogCenterShmManager::shmRegisterListernProc()
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(CHECK_INTERVAL));
        std::string clientName;
        myShmMutex.lock();
        std::pair<std::string *, std::size_t> ret = sharedMemory->find<
                std::string>(NAME_OF_STRING_IN_SHM);
        clients = *(ret.first);
        myShmMutex.unlock();

        std::regex ws_re("\\s+");
        std::vector<std::string> result
        { std::sregex_token_iterator(clientName.begin(), clientName.end(),
                ws_re, -1),
        { } };

        /// Only save newly added client ,ignore the saved clients
        for (auto it = result.rbegin(); it != result.rend(); it++)
        {
            if (clients.end() == clients.find(*it))
            {
                int log;
                if (readClientLogSetting(*it, log))
                {
                    clients.insert(std::make_pair(*it, log));
                }
                else
                {
                    //none
                }

            }
            else
            {
                break;
            }
        }
    }
}

bool LogCenterShmManager::handleLogUpdate(std::string& client, LogLevel level)
{
    bool res = true;
    if (clients.end() != clients.find(client))
    {
        if (clients[client] != level)
        {
            //Update log status only when success to notify to client
            if (writeLogLevel(client, level))
            {
                clients[client] = level;
            }
            else
            {
                res = false;
            }
        }
    }
    else
    {
        res = false;
    }
    return res;
}
