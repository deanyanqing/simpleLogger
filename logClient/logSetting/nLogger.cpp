/*
 * nLogger.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: haf
 */

#include <memory>
#include <fstream>
#include <functional>
#include <boost/phoenix/bind.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "nLogger.h"
#include "loggingDef.h"
#include "standAloneListener.h"
#include "networkListener.h"
std::string basename(std::string const& pathname) {
	return std::string(
			std::find_if(pathname.rbegin(), pathname.rend(),
					MatchPathSeparator()).base(), pathname.end());
}

NLogger::NLogger(std::string logFile, std::string moduleName,
		LogFilterListenType type) {
	std::function<void(SeverityLevel)> callback = std::bind(
			&NLogger::changeLogFilter, this, std::placeholders::_1);

	switch (type) {
	case LogFilterListenType::LOG_FILTER_NETWORK:
		logListener = std::make_shared<NetworkListener>(moduleName,
				callback);
		break;
	case LogFilterListenType::LOG_FILTER_STANDALONE:
		logListener = std::make_shared<StandAloneListener>(moduleName,
				callback);
		break;
	default:
		logListener = std::make_shared<StandAloneListener>(moduleName,
				callback);
		break;
	}

	initLogging();
}

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", SeverityLevel)

thread_local static SeverityLevel filter = SeverityLevel::warning;
static bool myFilter(
		logging::value_ref<SeverityLevel, tag::severity> const& level) {
	return level >= filter;
}

void NLogger::initLogging() {
	boost::shared_ptr<logging::core> core = logging::core::get();

	boost::shared_ptr<sinks::text_ostream_backend> backend = boost::make_shared<
			sinks::text_ostream_backend>();

	/*NOTE null_deleter location changed in 1.56*/
	backend->add_stream(
			boost::shared_ptr<std::ostream>(&std::clog,
					boost::serialization::null_deleter()));
	backend->add_stream(
			boost::shared_ptr<std::ostream>(new std::ofstream(DEFAUNT_FILE)));

	// Enable auto-flushing after each log record written
	backend->auto_flush(true);

	// Wrap it into the frontend and register in the core.
	// The backend requires synchronization in the frontend.
	typedef sinks::synchronous_sink<sinks::text_ostream_backend> sink_t;
	boost::shared_ptr<sink_t> sink = boost::make_shared<sink_t>(backend);

	namespace phoenix = boost::phoenix;
	sink->set_filter(phoenix::bind(&myFilter, severity.or_none()));

	core->add_sink(sink);

	slg = boost::make_shared<src::severity_logger<SeverityLevel> >();

	// Add attributes
	logging::add_common_attributes();
}

void NLogger::changeLogFilter(SeverityLevel level) {
	filter = level;
}

