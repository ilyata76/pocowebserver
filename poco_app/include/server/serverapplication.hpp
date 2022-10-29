#pragma once

#ifndef SERVERAPPLICATION_HPP
#define SERVERAPPLICATION_HPP

	#include <iostream>

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

	#include <termcolor/termcolor.hpp>

	#include <Poco/Data/PostgreSQL/Connector.h>
	#include <Poco/Data/PostgreSQL/PostgreSQL.h>
	#include <Poco/Data/PostgreSQL/PostgreSQLException.h>
	#include <Poco/Data/PostgreSQL/SessionImpl.h>
	#include <Poco/Data/PostgreSQL/Extractor.h>

	#include <Poco/Data/Statement.h>

	#include <Poco/Environment.h>

	#include "server/handlers/htmlhandler.hpp"
	#include "server/handlers/errorhtmlhandler.hpp"
	#include "server/handlers/imghandler.hpp"
	#include "server/handlers/csshandler.hpp"
	#include "server/handlers/jshandler.hpp"

	#include "server/base.hpp"

	namespace PWS {

		class RequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
				
				Poco::Logger::Ptr console_logger;
			
			public:
				
				RequestFactory(Poco::Logger::Ptr console_logger);

				Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
		
		};

		class Server : public Poco::Util::ServerApplication {

			Poco::Logger::Ptr console_logger;

			void initialize(Poco::Util::Application& self) override;

			int main(const std::vector<std::string>& args) override;

		};

	}



#endif // !SERVERAPPLICATION_HPP
