#pragma once

#ifndef SERVERAPPLICATION_HPP
#define SERVERAPPLICATION_HPP

	#include <Poco/Net/HTTPServer.h>
	#include <Poco/URI.h>	
	#include <Poco/Path.h>

	#include <Poco/Util/ServerApplication.h>
	#include <Poco/Net/HTTPServer.h>

	#include <Poco/Logger.h>
	#include <Poco/PatternFormatter.h>
	#include <Poco/FormattingChannel.h>
	#include <Poco/ConsoleChannel.h>
	#include <Poco/FileChannel.h>

	#include <toml/toml.hpp>

	#include <server/handlers/htmlhandler.hpp>

	namespace PWS {

		class RequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
				
				Poco::Logger::Ptr console_logger;
			
			public:
				
				RequestFactory(Poco::Logger::Ptr console_logger);

				Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
		
		};

		class Server : public Poco::Util::ServerApplication {

			int main(const std::vector<std::string>& args) override;

		};

	}



#endif // !SERVERAPPLICATION_HPP
