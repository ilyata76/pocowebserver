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

	//
}

PWS::APIMeHandler::~APIMeHandler() {
	
	//
}
