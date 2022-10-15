#pragma once

#ifndef HTMLHANDLER_HPP
#define HTMLHANDLER_HPP

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

	#include <pws_config.h>

	namespace PWS {

		class HTMLHandler : public Poco::Net::HTTPRequestHandler {
			private:
				Poco::Logger::Ptr console_logger;
				Poco::URI uri;
			public:
				HTMLHandler();
				HTMLHandler(Poco::URI uri, Poco::Logger::Ptr console_logger);
				void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
		};

	}


#endif // !HTMLHANDLER_HPP