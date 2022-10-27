#include "server/handlers/errorhtmlhandler.hpp"

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

	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND); // 404
	
	return;
}
