/*
 * networkListener.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: haf
 */

#include "networkListener.h"

NetworkListener::NetworkListener(std::string moduleName, std::function<void(SeverityLevel)> fun):BaseLogFilterListener(moduleName,fun)
{


}

NetworkListener::~NetworkListener()
{

}

void NetworkListener::startListen()
{

}
