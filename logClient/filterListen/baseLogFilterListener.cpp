/*
 * baseLogFilterListener.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#include "baseLogFilterListener.h"

BaseLogFilterListener::BaseLogFilterListener(std::string moduleName,
        std::function<void(SeverityLevel)> fun) :
        moduleName(moduleName)
{
    filterCallback = fun;
}

BaseLogFilterListener::~BaseLogFilterListener()
{

}

