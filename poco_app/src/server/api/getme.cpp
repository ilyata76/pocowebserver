#include "server/api/getme.hpp"

PWS::APIMeHandler::APIMeHandler(
	Poco::URI uri, 
	Poco::Logger::Ptr console_logger, 
	PostgreSQLSession* db_session
) : uri(uri), console_logger(console_logger), db_session(db_session) {
	
	//
}

void PWS::APIMeHandler::handleRequest(
	Poco::Net::HTTPServerRequest& request, 
	Poco::Net::HTTPServerResponse& response
) {

	if (request.getMethod() == "GET") {

		std::string scheme;
		std::string auth_info;
		
		request.getCredentials(scheme, auth_info);
		
		if (scheme == "Bearer") {

			try {

				std::ostream& reply = response.send();

				std::string jwt{ auth_info };

				Poco::JWT::Signer signer{ Poco::Environment::get("JWT_SECRET_WORD") };

				Poco::JWT::Token token{ signer.verify(jwt) };

				token.payload().stringify(reply);

				std::stringstream ss;
				ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
					<< termcolor::green << Poco::Net::HTTPServerResponse::HTTP_OK << termcolor::reset << termcolor::nocolorize;
				this->console_logger->information(ss.str());

				response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);

				return;
			} catch(Poco::JWT::JWTException& e) {
				console_logger->error(e.what());

				response.setStatus(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
			}
		} else {

			std::ostream& reply = response.send();

			Poco::JSON::Object json;

			json.set("error", "Unauthorized");
			
			json.stringify(reply);

			std::stringstream ss;
			ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
				<< termcolor::red << Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED << termcolor::reset << termcolor::nocolorize;
			this->console_logger->information(ss.str());

			response.setStatus(Poco::Net::HTTPServerResponse::HTTP_UNAUTHORIZED);
		}

	} else {

		std::stringstream ss;
		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::red << Poco::Net::HTTPServerResponse::HTTP_BAD_REQUEST << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		response.setStatus(Poco::Net::HTTPServerResponse::HTTP_BAD_REQUEST);
		return;
	}
}

PWS::APIMeHandler::~APIMeHandler() {
	
	//
}
