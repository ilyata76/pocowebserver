#include <server/handlers/htmlhandler.hpp>

PWS::HTMLHandler::HTMLHandler() : uri(NULL) {
	//
}

PWS::HTMLHandler::HTMLHandler(Poco::URI uri) : uri(uri) {
	// TODO: logger
}

void PWS::HTMLHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
	
	std::ostream& reply = response.send();
	std::fstream file;	std::stringstream ss;

	Poco::Path path{ this->uri.getPath() };

	ss << config_app_folder << "/public" << (path.directory(0) == "" ? "/index.html" : this->uri.getPath());

	file.open(ss.str().c_str(), std::ios::in);

	Poco::StreamCopier::copyStream(file, reply);

	file.close();
	
	response.setContentType("text/html\r\n");
	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK); // 200
	
	return;
}
