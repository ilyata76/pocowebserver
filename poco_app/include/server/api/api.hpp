	//PWS::PostgreSQLSession postgres_session{};
	//
	//auto x = postgres_session.getSession();
	//
	//Poco::Data::Statement statement(x);
	//
	//struct Person { std::string fname; std::string lname; } person;
	//statement << "SELECT first_name, last_name FROM test1;",
	//Poco::Data::Keywords::into(person.fname),
	//Poco::Data::Keywords::into(person.lname),
	//Poco::Data::Keywords::range(0, 1);
	//
	//statement.execute();
	//
	//std::cout << person.fname;


#pragma once

#ifndef API_HPP
#define API_HPP

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
	#include "server/api/apicurrenthandler.hpp"
	#include "server/api/getusers.hpp"
	#include "server/api/getme.hpp"
	#include "server/api/postlogin.hpp"

	namespace PWS {

		class APIHandlerFabric {
			private:
				Poco::Logger::Ptr console_logger;
				Poco::URI uri;
				PostgreSQLSession* db_session;
			public:
				APIHandlerFabric();
				APIHandlerFabric(Poco::URI uri);
				APIHandlerFabric(Poco::URI uri, Poco::Logger::Ptr console_logger, PostgreSQLSession* db_session);

				PWS::APICurrentHandler* createHandler(Poco::URI uri);

				~APIHandlerFabric();
		};

	}

#endif // !API_HPP
