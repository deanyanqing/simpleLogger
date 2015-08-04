/*
 * baseLogFilterListener.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#include "baseLogFilterListener.h"

BaseLogFilterListener::BaseLogFilterListener( std::string moduleName,std::function<void(SeverityLevel)> fun)
{

  filterCallback = fun;
}

BaseLogFilterListener::~BaseLogFilterListener()
{

}

void BaseLogFilterListener::doFilter(std::string& module,SeverityLevel level)
{

  filterCallback(level);
}

bool BaseLogFilterListener::isTarget(std::string& module )
{
  return 0 == moduleName.compare(module);
}
