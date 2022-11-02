#include "server/api/api.hpp"

PWS::APIHandlerFabric::APIHandlerFabric() {
	//
}

PWS::APIHandlerFabric::APIHandlerFabric(Poco::URI uri) : uri(uri) {
	//
}

PWS::APIHandlerFabric::APIHandlerFabric(Poco::URI uri, Poco::Logger::Ptr console_logger, PostgreSQLSession* db_session)
	: uri(uri), console_logger(console_logger), db_session(db_session) {
	//
}

PWS::APICurrentHandler* PWS::APIHandlerFabric::createHandler(Poco::URI uri) {
	Poco::Path path{ uri.getPath() };

	if (path.directory(1) == "users") {
		return new APIUsersHandler{ uri, console_logger, db_session };
	}

	return nullptr; // TODO: ErrorHandler
}

PWS::APIHandlerFabric::~APIHandlerFabric() {
	//
}
