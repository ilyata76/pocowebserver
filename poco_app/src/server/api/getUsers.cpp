#include "server/api/getusers.hpp"

PWS::APIUsersHandler::APIUsersHandler(Poco::URI uri, Poco::Logger::Ptr console_logger, PostgreSQLSession* db_session) :
	uri(uri), console_logger(console_logger), db_session(db_session) 
{	
	//
}

void PWS::APIUsersHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	
	if (request.getMethod() == "GET") {
		Poco::Path path{ uri.getPath() }; std::stringstream ss;

		std::ostream& reply = response.send();
		response.setContentType("text\r\n");

		// DB

		db_session->beginTransaction();

		auto sess = db_session->getSession();
		Poco::Data::Statement statement(sess);

		typedef Poco::Tuple<std::string, std::string> Person;
		std::vector<Person> people;

		statement << "SELECT first_name, last_name FROM test1;",
			Poco::Data::Keywords::into(people);

		statement.execute();

		db_session->endTransaction();

		// JSON replying

		Poco::JSON::Object json_users;
		Poco::JSON::Object json_current_user;
		std::vector<Poco::JSON::Object> users;

		for (const auto& x : people) {
			json_current_user.set("firstname", x.get<0>());
			json_current_user.set("secondname", x.get<1>());
			users.push_back(json_current_user);
		}

		json_users.set("count", people.size());
		json_users.set("users", users);
		json_users.stringify(reply);

		// LOG

		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::green << Poco::Net::HTTPServerResponse::HTTP_OK << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		// STATUS

		response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);

		return;
	} else {
		std::stringstream ss;
		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::red << Poco::Net::HTTPServerResponse::HTTP_BAD_REQUEST << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		response.setStatus(Poco::Net::HTTPServerResponse::HTTP_BAD_REQUEST);
	}
}

PWS::APIUsersHandler::~APIUsersHandler() {
	//
}
