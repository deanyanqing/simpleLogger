/*
 * standAloneListener.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#include "standAloneListener.h"

StandAloneListener::StandAloneListener(std::string moduleName, std::function<void(SeverityLevel)> fun):BaseLogFilterListener(moduleName,fun)
{

  initSharedMem();

}

StandAloneListener::~StandAloneListener()
{

}

void StandAloneListener::startListen()
{

}

void StandAloneListener::initSharedMem()
{
  sharedMemory = std::make_shared<bip::managed_shared_memory>(boost::interprocess::create_only,getModuleName().c_str(), 1 );

  typedef std::pair<std::string, SeverityLevel> MyType;
  MyType *instance = sharedMemory->construct<MyType>
           (getModuleName())  //name of the object
           (getModuleName(), SeverityLevel::debug);
}
