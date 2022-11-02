#pragma once

#ifndef DBHANDLER_HPP
#define DBHANDLER_HPP

	#include <iostream>
	#include <string>
	#include <sstream>

	#include <Poco/Data/PostgreSQL/Connector.h>
	#include <Poco/Data/PostgreSQL/PostgreSQL.h>
	#include <Poco/Data/PostgreSQL/PostgreSQLException.h>
	#include <Poco/Data/PostgreSQL/SessionImpl.h>
	#include <Poco/Data/Session.h>
	#include <Poco/Data/PostgreSQL/Extractor.h>
	#include <Poco/Data/Statement.h>
	#include <Poco/Environment.h>

	namespace PWS {
		
		class PostgreSQLSession {

			private:
				std::string connection_string;
				Poco::Data::Session* session;

			public:
				PostgreSQLSession();
				PostgreSQLSession(std::string connectionString);

				Poco::Data::Session * getSessionPtr() const;
				Poco::Data::Session getSession() const;
				
				void closeSession();
				void openSession();
				void beginTransaction();
				void endTransaction();

				~PostgreSQLSession();

		};

	}
#endif // !DBHANDLER_HPP