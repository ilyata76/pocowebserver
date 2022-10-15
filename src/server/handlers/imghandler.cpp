#include <server/handlers/imghandler.hpp>

PWS::IMGHandler::IMGHandler() : uri(NULL) {
	//
}

PWS::IMGHandler::IMGHandler(Poco::URI uri, Poco::Logger::Ptr console_logger) : uri(uri), console_logger(console_logger) {
	//
}

void PWS::IMGHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	std::stringstream ss; std::fstream file;

	Poco::Path path{ uri.getPath() };

	ss << config_app_folder << "/public" << this->uri.getPath(); // this->uri.getPath() вернёт /img/abob.jpg
	file.open(ss.str().c_str(), std::ios::in | std::ios::binary);

	if (file.is_open()) {
		std::ostream& reply = response.send();

		Poco::StreamCopier::copyStream(file, reply);

		file.close();
	
		if (path.getExtension() == "jpg")
			response.setContentType("image/jpeg\r\n");
		else if (path.getExtension() == "png")
			response.setContentType("image/png\r\n");

		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::green << Poco::Net::HTTPServerResponse::HTTP_OK << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK); // 200
	} else {
		file.close();

		ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  "
			<< termcolor::red << Poco::Net::HTTPServerResponse::HTTP_MOVED_PERMANENTLY << termcolor::reset << termcolor::nocolorize;
		this->console_logger->information(ss.str());

		response.redirect("/error", Poco::Net::HTTPServerResponse::HTTP_MOVED_PERMANENTLY);
	}
}
