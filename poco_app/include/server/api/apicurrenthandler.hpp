#pragma once

#ifndef APICURRENTHANDLER_HPP
#define APICURRENTHANDLER_HPP

	#include <ostream>
	#include <fstream>
	#include <sstream>

	#include <Poco/Net/HTTPRequestHandler.h>
	#include <Poco/Net/HTTPServerResponse.h>
	#include <Poco/Net/HTTPServerRequest.h>
	#include <Poco/Net/HTTPRequestHandler.h>
	#include <Poco/StreamCopier.h>

	#include <Poco/URI.h>	
	#include <Poco/Path.h>

	#include <Poco/Logger.h>

	#include <termcolor/termcolor.hpp>

	#include "pws_config.h"

	namespace PWS {

		class APICurrentHandler : public Poco::Net::HTTPRequestHandler {
			private:
				Poco::Logger::Ptr console_logger;
				Poco::URI uri;
			public:
				//APICurrentHandler();
				//APICurrentHandler(Poco::URI uri);
				//APICurrentHandler(Poco::URI uri, Poco::Logger::Ptr console_logger);

				virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override = 0;

				virtual ~APICurrentHandler();
		};

	}

#endif // !APICURRENTHANDLER_HPP



