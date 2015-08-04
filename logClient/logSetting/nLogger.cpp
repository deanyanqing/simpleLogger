/*
 * nLogger.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: haf
 */



#include <memory>
#include <fstream>
#include <boost/phoenix/bind.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "nLogger.h"
#include "loggingDef.h"

NLogger* gLogger = new  NLogger("","");



std::string basename( std::string const& pathname )
{
    return std::string(
        std::find_if( pathname.rbegin(), pathname.rend(),MatchPathSeparator() ).base(),pathname.end() );
}



NLogger::NLogger(std::string logFile,std::string moduleName)
{
  init_logging();
}

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", SeverityLevel)

static SeverityLevel filter = SeverityLevel::warning;
static bool my_filter(logging::value_ref< SeverityLevel, tag::severity > const& level)
       {
          return level >= filter ;
       }


void NLogger::init_logging()
{
  boost::shared_ptr< logging::core > core = logging::core::get();

  boost::shared_ptr< sinks::text_ostream_backend > backend  =
          boost::make_shared< sinks::text_ostream_backend >();

  /*NOTE null_deleter location changed in 1.56*/
      backend->add_stream(
          boost::shared_ptr< std::ostream >(&std::clog, boost::serialization::null_deleter()));
      backend->add_stream(
          boost::shared_ptr< std::ostream >(new std::ofstream(DEFAUNT_FILE)));

      // Enable auto-flushing after each log record written
      backend->auto_flush(true);

      // Wrap it into the frontend and register in the core.
      // The backend requires synchronization in the frontend.
      typedef sinks::synchronous_sink< sinks::text_ostream_backend > sink_t;
        boost::shared_ptr< sink_t > sink= boost::make_shared<sink_t>(backend);


      namespace phoenix = boost::phoenix;
         sink->set_filter(phoenix::bind(&my_filter, severity.or_none()));

      core->add_sink(sink);

  slg = boost::make_shared< src::severity_logger< SeverityLevel > >();

  // Add attributes
  logging::add_common_attributes();
}

void NLogger::changeLogFilter(SeverityLevel level)
{
  filter = level;
}





