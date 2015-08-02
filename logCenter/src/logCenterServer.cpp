/*
 * logCenterServer.cpp
 *
 *  Created on: Jul 31, 2015
 *      Author: haf
 */

#include "logCenterServer.h"
#include <boost/bind.hpp>
#include <sstream>
#include <functional> /*hash*/
#include <algorithm>

extern boost::asio::io_service io_service;
LogCenterServer::LogCenterServer(ClientCallbackFun registerCallbackFun , LogSettingCallbackFun setting)
: socket(io_service,udp::endpoint(boost::asio::ip::address::from_string(LOG_CENTER_IP),LOG_CENTER_PORT))
{
  clientCallback = registerCallbackFun;
  settingCallback = setting;
  startReceive();

}

LogCenterServer::~LogCenterServer()
{

}

void LogCenterServer::sendClientSetting(ClientIndex clientIndex,SeverityLevel level)
{

}

void LogCenterServer::startReceive()
{
  socket.async_receive_from(
            boost::asio::buffer(recvBuffer), remoteEndpoint,
            boost::bind(&LogCenterServer::handleReceive, this,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
}

static std::istringstream& operator >>(std::istringstream& stream ,LogClient& client)
{


  return stream;
}

static std::istringstream& operator >>(std::istringstream& stream, LogClientSetting& setting )
{

  return stream;
}




void LogCenterServer::handleReceive(const boost::system::error_code& error,std::size_t size)
{
  if ((boost::asio::error::eof == error) ||
         (boost::asio::error::connection_reset == error))
  {
      // handle the disconnect.
      auto findHash = [this](const std::pair<ClientIndex,udp::endpoint>& value){return value.second == this->remoteEndpoint;};
      auto hashIt = std::find_if(clients.begin() , clients.end(), findHash);
      if(clients.end() != hashIt)
      {
        LogClient client;/*Meaningless here*/
        clientCallback(ClientConnectionStatus::client_disconnection,hashIt->first, client);
      }

  }

try{
  bool messageValid = true;
  unsigned int headerLength = sizeof(LogMessageID);
  std::istringstream is(std::string(recvBuffer.begin(), recvBuffer.begin() + headerLength));
  LogMessageID id =0;
  if( !(is >> id))
  {
    std::clog << "Invalid message!" << std::endl;
    boost::system::error_code error(boost::asio::error::invalid_argument);
    messageValid = false;
  }

  if(messageValid)
  {
    std::string archiveData(recvBuffer.begin() + headerLength, recvBuffer.end());
    std::istringstream archiveStream(archiveData);

    switch(id)
    {
        case LOG_CLIENT_SETTING_MESSAGE_ID:
        {
          LogClientSetting setting;
          archiveStream >> setting;
          settingCallback(setting);
          break;
        }
        case LOG_CLIENT_MESSAGE_ID:
        {
          LogClient client;
          archiveStream >> client;
          /*Generate hash code as ID*/
          std::hash<std::string> hasher;
          std::size_t hash = hasher(client.moduleName);
          clients[hash] = remoteEndpoint;

          clientCallback(ClientConnectionStatus::client_update,hash, client);
          break;
        }
        default:
          std::clog << "Invalid message id :" << id << std::endl;
          break;
     }
  }

  startReceive();
}
catch(...)
{
  startReceive();
}

}
