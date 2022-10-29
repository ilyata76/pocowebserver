#include "server/handlers/errorhtmlhandler.hpp"

#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/PostgreSQL/PostgreSQL.h>
#include <Poco/Data/PostgreSQL/PostgreSQLException.h>
#include <Poco/Data/PostgreSQL/SessionImpl.h>
#include <Poco/Data/PostgreSQL/Extractor.h>

#include <Poco/Data/Statement.h>

#include <Poco/Environment.h>

#include <iostream>

PWS::ErrorHTMLHandler::ErrorHTMLHandler() : uri(NULL) {
	//
}

PWS::ErrorHTMLHandler::ErrorHTMLHandler(Poco::URI uri, Poco::Logger::Ptr console_logger) : uri(uri), console_logger(console_logger) {
	//
}

void PWS::ErrorHTMLHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	std::ostream& reply = response.send();
	std::fstream file;	std::stringstream ss;

	ss << config_app_folder << "/public" << "/error.html";

	file.open(ss.str().c_str(), std::ios::in);

	Poco::StreamCopier::copyStream(file, reply);

	file.close();
	
	response.setContentType("text/html\r\n");

	ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
		<< termcolor::red << Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND << termcolor::reset << termcolor::nocolorize;
	this->console_logger->information(ss.str());


	//////////////////////////////////////

	std::stringstream connectionString;
	connectionString << "host=" << Poco::Environment::get("POSTGRES_DB_HOST")
		<< " port=" << Poco::Environment::get("POSTGRES_PORT")
		<< " dbname=" << Poco::Environment::get("POSTGRES_DB_NAME")
		<< " user=" << Poco::Environment::get("POSTGRES_USER_NAME")
		<< " password=" << Poco::Environment::get("POSTGRES_USER_PASSWORD");

	Poco::Data::PostgreSQL::Connector connector{};
	auto x = connector.createSession(connectionString.str().c_str());
	std::cout << connector.name();
	std::cout << x->isGood();

	Poco::Data::Statement st{ x->createStatementImpl() };

	struct Person { std::string fname; std::string lname; } person;

	st << "SELECT first_name, last_name FROM test1;",
		Poco::Data::Keywords::into(person.fname),
		Poco::Data::Keywords::into(person.lname),
		Poco::Data::Keywords::range(0, 1);

	st.execute();
	this->console_logger->warning(person.fname);
	std::cout << person.fname << person.lname;

	/// //////////////////////////////////////


	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND); // 404
	
	return;
}
