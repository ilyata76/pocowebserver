#include "server/api/getusers.hpp"

PWS::APIUsersHandler::APIUsersHandler(Poco::URI uri, Poco::Logger::Ptr console_logger, PostgreSQLSession* db_session) :
	uri(uri), console_logger(console_logger), db_session(db_session) 
{	
	//
}

void PWS::APIUsersHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	Poco::Path path{ uri.getPath() }; std::stringstream ss;
	
	std::ostream& reply = response.send();
	response.setContentType("text\r\n");

	db_session->beginTransaction();

	auto sess = db_session->getSession();
	Poco::Data::Statement statement(sess);

	typedef Poco::Tuple<std::string, std::string> Person;
	std::vector<Person> people;

	statement << "SELECT first_name, last_name FROM test1;",
		Poco::Data::Keywords::into(people);

	statement.execute();

	for (const auto& x : people) {
		reply << x.get<0>() << " " << x.get<1>() << "\n";
	}

	db_session->endTransaction();
	
	ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
		<< termcolor::green << Poco::Net::HTTPServerResponse::HTTP_OK << termcolor::reset << termcolor::nocolorize;
	this->console_logger->information(ss.str());

	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
}

PWS::APIUsersHandler::~APIUsersHandler() {
	//
}
