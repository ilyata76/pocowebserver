#include "db/dbhandler.hpp"

PWS::PostgreSQLSession::PostgreSQLSession() {
	
	std::stringstream ss;
	ss	<< "host=" << Poco::Environment::get("POSTGRES_DB_HOST")
		<< " port=" << Poco::Environment::get("POSTGRES_PORT")
		<< " dbname=" << Poco::Environment::get("POSTGRES_DB_NAME")
		<< " user=" << Poco::Environment::get("POSTGRES_USER_NAME")
		<< " password=" << Poco::Environment::get("POSTGRES_USER_PASSWORD");
	
	connection_string = ss.str();

	Poco::Data::PostgreSQL::Connector::registerConnector();

	session = new Poco::Data::Session{ "postgresql", connection_string };

}

PWS::PostgreSQLSession::PostgreSQLSession(std::string connection_string) {

	this->connection_string = connection_string;

	Poco::Data::PostgreSQL::Connector::registerConnector();

	session = new Poco::Data::Session{ "postgresql", connection_string };
}

Poco::Data::Session * PWS::PostgreSQLSession::getSessionPtr() const {
	return session;
}

Poco::Data::Session PWS::PostgreSQLSession::getSession() const {
	return *session;
}

void PWS::PostgreSQLSession::closeSession() {
	return session->close();
}

void PWS::PostgreSQLSession::openSession() {
	return session->open();
}

void PWS::PostgreSQLSession::beginTransaction() {
	return session->begin();
}

void PWS::PostgreSQLSession::endTransaction() {
	return session->commit();
}

PWS::PostgreSQLSession::~PostgreSQLSession() {
	delete session;
}
