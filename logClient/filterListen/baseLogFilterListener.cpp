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
  if(0 == moduleName.compare(module))
  {
    filterCallback(level);
  }

}


