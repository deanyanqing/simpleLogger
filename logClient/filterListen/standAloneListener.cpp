/*
 * standAloneListener.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#include "standAloneListener.h"
#include <boost/interprocess/sync/named_mutex.hpp>
#include <mutex>

/**  Shared memory that log client register to log agent.
 *  Client will write register information such like client id (Actually it also
 *      the shared memory name to receive the log setting)
 * */
const static std::string REGISTER_LOG_SHM("RegisterLogClientShm");
const static char* NAME_OF_STRING_IN_SHM = "StringOfShm";
const static char* MUTEX_REGISTER_LOG_SHM = "MutexForRegisterLogShm";
const static uint SHARED_MEMORY_SIZE = 1024;
const static char* LOG_LEVEL_NAME = "LogLevel";
const static std::string REGISTER_PREFIX = "Register ";
const static std::string UNREGISTER_PREFIX = "Unregister ";


//@todo Replace with mutex from client later
static std::mutex log_register_shm_mutex;

StandAloneListener::StandAloneListener(std::string moduleName,
		std::function<void(SeverityLevel)> fun, SeverityLevel level) :
		myShmConditonVar { open_or_create,
				std::string(moduleName + "cnd").c_str() }, myShmMutex(
				open_or_create, std::string(moduleName + "mutex").c_str()), BaseLogFilterListener(
				moduleName, fun) {
	currentLogSetting = static_cast<uint>(level);
	shared_memory_object::remove(moduleName.c_str());
	sharedMemory = std::make_shared<managed_shared_memory>(create_only,
			moduleName.c_str(), SHARED_MEMORY_SIZE);
	uint* logLevel = sharedMemory->find_or_construct<uint>(LOG_LEVEL_NAME)(
			static_cast<uint>(level));
	myShmConditonVar.notify_all();
	running = true;
	shmListenThread = std::make_shared<std::thread>(
			&StandAloneListener::startListen, this);
	startListen();
}

static inline bool writeData2shm(const std::string& content) {
	managed_shared_memory* shmPtr = nullptr;
	//Check the shared memory whether created or not
	try {
		managed_shared_memory register_shm(open_only, REGISTER_LOG_SHM.c_str());
		shmPtr = &register_shm;
	} catch (...) {
		return false;
	};

	//shm_mutex is mutex between process,but within same process, shm_mutex is mutex between threads within same process
	named_mutex shm_mutex(open_only, MUTEX_REGISTER_LOG_SHM);
	shm_mutex.lock();
	log_register_shm_mutex.lock();

	std::pair<std::string *, std::size_t> ret = shmPtr->find<std::string>(
			NAME_OF_STRING_IN_SHM);

	*(ret.first) = content;
	log_register_shm_mutex.unlock();
	shm_mutex.unlock();
	return true;

}

void StandAloneListener::startListen() {
	registerMyself();
	while (running) {
		scoped_lock<named_mutex> lock { myShmMutex };
		myShmConditonVar.wait(lock);
		if (false == running) {
			break;
		} else {
			std::pair<unsigned int*, long unsigned int> logLevel = sharedMemory->find<uint>(LOG_LEVEL_NAME);
			if (currentLogSetting != *(logLevel.first)) {
				currentLogSetting = *(logLevel.first);
				filterCallback(static_cast<SeverityLevel>(currentLogSetting));
			}
		}
	}

}

const static int MAX_TRY_NUMBER = 10;
void StandAloneListener::registerMyself() {
	std::string content(REGISTER_PREFIX + moduleName);

	int count = 0;
	while (count < MAX_TRY_NUMBER) {
		if (true == writeData2shm(content)) {
			break;
		} else {
			count++;
			//Adding reminder log for start log agent
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

StandAloneListener::~StandAloneListener()
{
	//Unregister myself in log agent,here we don't need to double confirm the content wrote success
	std::string content(UNREGISTER_PREFIX+moduleName);
	writeData2shm(content);
	//release my shared memory objec
	shared_memory_object::remove(moduleName.c_str());
	running = false;
	myShmConditonVar.notify_all();
	shmListenThread->join();

}



