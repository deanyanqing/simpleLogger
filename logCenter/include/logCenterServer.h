/*
 * logCenterServer.h
 *
 *  Created on: Jul 31, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCENTER_INCLUDE_LOGCENTERSERVER_H_
#define LOGGING_LOGCENTER_INCLUDE_LOGCENTERSERVER_H_

#include <thread>
#include <map>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "logDefine.h"

/*Socket constant setting */
#define LOG_CENTER_IP           "127.0.0.1"
#define LOG_CENTER_PORT          80901

using boost::asio::ip::udp;
/* @class LogCenterServer
 * @brief Work as socket server, invoke the corresponding callback from LogCenterControler
 */
class LogCenterServer
{
public:
  LogCenterServer(ClientCallbackFun,LogSettingCallbackFun);
  ~LogCenterServer();
  LogCenterServer()=delete;
  void init();

  /* @brief Send the setting from the user to client application
   * @param index Id of client application
   * @param level The expected log filter level
   * */
  void sendClientSetting(ClientIndex index ,SeverityLevel level);
private:

  /* @brief Check client application connection status */
  void connectionStatusCheck();

  inline void startReceive();
  void handleReceive(const boost::system::error_code& error,std::size_t size);

private:
  ClientCallbackFun clientCallback;
  LogSettingCallbackFun settingCallback;
  std::map<ClientIndex,udp::endpoint>  clients;

  /*boost socket*/
  udp::socket socket;
  udp::endpoint remoteEndpoint;
  boost::array<char, 1> recvBuffer;

};


#endif /* LOGGING_LOGCENTER_INCLUDE_LOGCENTERSERVER_H_ */
