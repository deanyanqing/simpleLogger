/*
 * main.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: haf
 */

#include "loggingDef.h"
#include <iostream>

void test()
{
  //NLOG(SeverityLevel::info ) << "it is info";
   //NLOG(SeverityLevel::trace ) << "it is trace";
   //NLOG(SeverityLevel::warning ) << "it is warning";
   //NLOG(SeverityLevel::error ) << "it is error";

}
int main()
{
  //gLogger->changeLogFilter(SeverityLevel::trace);
  std::cout << "Original log is " << std::endl;
  test();
  std::cout << "Input 0 stands <warning>, 1 stands <error>" << std::endl;
  int input;
  std::cin >> input;
 if(0 == input )
 {
   //gLogger->changeLogFilter(SeverityLevel::trace);
 }
 else
 {
   //gLogger->changeLogFilter(SeverityLevel::error);
 }

 test();


  return 0;
}


