/*
 * logDefine.h
 *
 *  Created on: Jul 31, 2015
 *      Author: haf
 */

#ifndef LOGGING_LOGCENTER_INCLUDE_LOGDEFINE_H_
#define LOGGING_LOGCENTER_INCLUDE_LOGDEFINE_H_

#include <string>
#include <memory>
enum class SeverityLevel
{
  trace,
  debug,
  info,
  warning,
  error,
  fatal
};

enum class ClientConnectionStatus
{
  client_update,
  client_disconnection
};

/* NOTE Assume running in the same machine */
/* network protocol between center and clients/user setting
 * Not directly use these but for your reference
 */
#define LOG_CLIENT_MESSAGE_ID 1001
struct LogClientMessage
{
  SeverityLevel level;
  ClientConnectionStatus connectionStatus;
  unsigned int clientCompentNameLength;
  char clientCompentName[1];
};

#define LOG_CLIENT_SETTING_MESSAGE_ID 1002
struct LogClientSettingMessage
{
  SeverityLevel level;
  unsigned int clientsCompentNameLength;
  char clientsCompentName[1];
};


using LogMessageID= unsigned int;
struct LogMessage
{
  LogMessageID id;
  union {
    LogClientMessage fromClient;
    LogClientSettingMessage clientSettingFromUser;
  }msg;
};

/*Internal type definition ,equivalence of the network protocol  */
using ClientIndex = unsigned int;
struct LogClient
{
  SeverityLevel filterLevel;
  std::string   moduleName;
};

struct LogClientSetting
{
  SeverityLevel filterLevel;
  std::vector<std::string> clients;
};


using ClientCallbackFun= std::function<void(ClientConnectionStatus, int,const LogClient&)>  ;
using LogSettingCallbackFun = std::function<void(LogClientSetting&)>  ;
#endif /* LOGGING_LOGCENTER_INCLUDE_LOGDEFINE_H_ */
