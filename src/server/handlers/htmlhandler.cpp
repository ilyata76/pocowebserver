#include <server/handlers/htmlhandler.hpp>

PWS::HTMLHandler::HTMLHandler() : uri(NULL) {
	//
}

PWS::HTMLHandler::HTMLHandler(Poco::URI uri, Poco::Logger::Ptr console_logger) : uri(uri), console_logger(console_logger) {
	//
}

void PWS::HTMLHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	
	std::ostream& reply = response.send();
	std::fstream file;	std::stringstream ss;

	Poco::Path path{ this->uri.getPath() };

	ss << config_app_folder << "/public" << (path.directory(0) == "" ? "/index.html" : this->uri.getPath());

	this->console_logger->information("Path: " + ss.str());

	file.open(ss.str().c_str(), std::ios::in);

	Poco::StreamCopier::copyStream(file, reply);

	file.close();
	
	response.setContentType("text/html\r\n");

	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK); // 200
	
	this->console_logger->information("Response: " + response.getStatus());

	return;
}
