#include "logCenterControler.h"

boost::asio::io_service io_service;
/* @brief Init the system and keep it running
 */
int main()
{


  io_service.run();

  return 0;
}
