/*
 * main.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: haf
 */

#include "nLogger.h"
#include <iostream>
using namespace haf_logging;
int main()
{


  std::cout << "Input 0 stands <trace>, 1 stands <error>" << std::endl;
  int input;
  std::cin >> input;
 if(0 == input )
 {
   gLogger->changeLogFilter(SeverityLevel::trace);
 }
 else
 {
   gLogger->changeLogFilter(SeverityLevel::error);
 }


  NLOG(SeverityLevel::info ) << "it is info";
  NLOG(SeverityLevel::trace ) << "it is trace";
  NLOG(SeverityLevel::warning ) << "it is warning";
  NLOG(SeverityLevel::error ) << "it is error";


  return 0;
}


