/*
 * standAloneListener.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#include "standAloneListener.h"


/**  Shared memory that log client register to log agent.
 *  Client will write register information such like client id (Actually it also
 *      the shared memory name to receive the log setting)
 * */
const static std::string register_log_shm("Register_log_client_shm");

const static uint SHARED_MEMORY_SIZE = 256;
const static char* LOG_LEVEL_NAME = "LogLevel";

StandAloneListener::StandAloneListener(std::string moduleName, std::function<void(SeverityLevel)> fun,SeverityLevel level)
:BaseLogFilterListener(moduleName,fun)
{
	shared_memory_object::remove(moduleName.c_str());
	sharedMemory = std::make_shared<managed_shared_memory>(create_only,moduleName.c_str(), SHARED_MEMORY_SIZE);
	uint* logLevel = sharedMemory->find_or_construct<uint>(LOG_LEVEL_NAME)(static_cast<uint>(level));

	startListen();
}

StandAloneListener::~StandAloneListener()
{
	//Unregister myself in log agent
}

void StandAloneListener::startListen()
{

}

void StandAloneListener::registerMyself(const std::string& clientID)
{
	managed_shared_memory register_shm(open_only, register_log_shm.c_str(), 1);
	mapped_region region(register_shm, read_only);
	char *mem = static_cast<char*>(region.get_address());


}
