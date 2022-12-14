#pragma once

#ifndef GETUSERS_HPP
#define GETUSERS_HPP

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
	#include <Poco/Tuple.h>

	#include <Poco/JSON/Array.h>
	#include <Poco/JSON/Object.h>

	#include <termcolor/termcolor.hpp>

	#include "pws_config.h"

	#include "db/dbhandler.hpp"
	#include "server/api/apicurrenthandler.hpp"

	namespace PWS {

		class APIUsersHandler : public PWS::APICurrentHandler {
			private:
				Poco::Logger::Ptr console_logger;
				PostgreSQLSession* db_session;
				Poco::URI uri;
			public:
				APIUsersHandler(Poco::URI uri, Poco::Logger::Ptr console_logger, PostgreSQLSession* db_session);
				void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
				~APIUsersHandler();
		};

	}


#endif // !GETUSERS_HPP