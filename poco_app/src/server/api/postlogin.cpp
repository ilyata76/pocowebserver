#include "server/api/postlogin.hpp"

PWS::APILoginHandler::APILoginHandler(
	Poco::URI uri, 
	Poco::Logger::Ptr console_logger, 
	PostgreSQLSession* db_session
) : uri(uri), console_logger(console_logger), db_session(db_session) {
	
	//
}

void PWS::APILoginHandler::handleRequest(
	Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response
) {

	if (request.getMethod() == "POST") {
		Poco::Net::HTMLForm form{ request };

		auto fname = form.get("firstname", "default_first_name");
		auto sname = form.get("secondname", "default_second_name");

		std::ostream& reply = response.send();

		Poco::JWT::Token token{};
		token.setType("JWT");
		token.payload().set("firstname", fname);
		token.payload().set("secondname", sname);
		token.setAlgorithm("HS256");

		Poco::JWT::Signer signer{ Poco::Environment::get("JWT_SECRET_WORD") };

		std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);

		Poco::JSON::Object json;

		json.set("token", jwt);

		json.stringify(reply);

		std::stringstream ss;
		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::green << Poco::Net::HTTPServerResponse::HTTP_OK << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		response.setContentType("application/json");
		response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);

		return;

	} else {

		std::stringstream ss;
		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::red << Poco::Net::HTTPServerResponse::HTTP_BAD_REQUEST << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		response.setStatus(Poco::Net::HTTPServerResponse::HTTP_BAD_REQUEST);
		return;
	}
}

PWS::APILoginHandler::~APILoginHandler() {
	
	//
}
