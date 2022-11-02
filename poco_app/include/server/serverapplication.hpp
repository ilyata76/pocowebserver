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

	#include <Poco/Environment.h>

	#include <toml/toml.hpp>

	#include <termcolor/termcolor.hpp>

	#include "server/handlers/htmlhandler.hpp"
	#include "server/handlers/errorhtmlhandler.hpp"
	#include "server/handlers/imghandler.hpp"
	#include "server/handlers/csshandler.hpp"
	#include "server/handlers/jshandler.hpp"

	#include "server/base.hpp"
	#include "server/api/api.hpp"

	#include "db/dbhandler.hpp"

	namespace PWS {

		class RequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
				
				Poco::Logger::Ptr console_logger;
				PWS::PostgreSQLSession* database_session;
			
			public:
				
				RequestFactory(Poco::Logger::Ptr console_logger, PWS::PostgreSQLSession* database_session);

				Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
		
		};

		class Server : public Poco::Util::ServerApplication {

			Poco::Logger::Ptr console_logger;
			PWS::PostgreSQLSession* database_session;

			void initialize(Poco::Util::Application& self) override;
			void uninitialize() override;

			int main(const std::vector<std::string>& args) override;

		};

	}



#endif // !SERVERAPPLICATION_HPP
