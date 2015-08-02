/*
 * logCenterControler.h
 *
 *  Created on: Jul 31, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCENTER_LOGCENTERCONTROLER_H_
#define LOGGING_LOGCENTER_LOGCENTERCONTROLER_H_

#include <map>
#include <string>
#include <memory>
#include "logCenterServer.h"
#include "logDefine.h"

/* @class LogCenterControler
 * @brief Main controler react to the setting from user
 */
class LogCenterControler
{
public:
  LogCenterControler();
  ~LogCenterControler();

private:
  /* @brief Maintain the setting of alive logClient
   * @param status Represetn the client connection status
   * @param index  ID of the client
   * @param client Detail client setting
   * */
  void logConnectionHandler(ClientConnectionStatus status, ClientIndex index,const LogClient& client);

  /* @brief Handle the setting from user.If necessary notify  the client to update its setting
   * @param client New setting from user
   */
  void clientLogUpdateHandler(LogClient& client);
private:
  std::map<ClientIndex, LogClient> clients;
  std::shared_ptr<LogCenterServer>  logServer;
};

#endif /* LOGGING_LOGCENTER_LOGCENTERCONTROLER_H_ */
