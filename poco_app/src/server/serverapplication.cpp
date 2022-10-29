#include "server/serverapplication.hpp"

PWS::RequestFactory::RequestFactory(Poco::Logger::Ptr console_logger) {
	this->console_logger = console_logger;
}

Poco::Net::HTTPRequestHandler* PWS::RequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
	Poco::URI uri{ request.getURI() };
	Poco::Path path{ uri.getPath() };

	bool is_error = (path.directory(0) == "error" || path.directory(0) == "error.html");

	bool is_html_file = (
		(
			path.getExtension() == "html" || path.getExtension() == ""
		) && (
			path.directory(0) != "api" && path.directory(0) != "css" && path.directory(0) != "img" && path.directory(0) != "js"
		)
	);

	bool is_image = (path.directory(0) == "img");
	bool is_css = (path.directory(0) == "css" || path.directory(0) == "scss");
	bool is_js = (path.directory(0) == "js");
	bool is_api = (path.directory(0) == "api");

	//

	std::stringstream ss;
	ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue	 << request.getURI() << termcolor::reset << "  |  " << termcolor::nocolorize;
	this->console_logger->information(ss.str());
	
	// non API

	if (request.getMethod() == "GET") {
		if (is_error) {
			return new ErrorHTMLHandler{ uri, console_logger };
		} else if (is_html_file || (path.directory(0) == "/" || path.directory(0) == "")) {
			return new HTMLHandler{ uri, console_logger };
		} else if (is_image) {
			return new IMGHandler{ uri, console_logger };
		} else if (is_css) {
			return new CSSHandler{ uri, console_logger };
		} else if (is_js) {
			return new JSHandler{ uri, console_logger };
		}
	}

	//
	// API

	// return apihandler ... getmethod ...

	//

	ss.str(""); ss << termcolor::colorize << termcolor::cyan << request.getMethod() << termcolor::reset << "  |  " << termcolor::bright_blue << request.getURI() << termcolor::reset << "  |  " 
			<< termcolor::red << "Handler was not found" << termcolor::reset << termcolor::nocolorize;
	this->console_logger->error(ss.str());

	return new ErrorHTMLHandler{ uri, console_logger }; // TODO: htmlerror
}

void PWS::Server::initialize(Poco::Util::Application& self) {

	Poco::PatternFormatter::Ptr console_pattern_formatter{ new Poco::PatternFormatter {"[PWS][%Y-%m-%d:%H%M%S][%p] \t %t"} };
	Poco::FormattingChannel::Ptr pFCConsole{ new Poco::FormattingChannel{console_pattern_formatter} };
	pFCConsole->setChannel(new Poco::ConsoleChannel{});
	pFCConsole->open();
	Poco::Logger& console_logger = Poco::Logger::create("ConsoleLogger", pFCConsole);
	this->console_logger = &console_logger;


	if (!PWS::loadEnvironment())
		throw Poco::Exception("environment error: invalid initialization");
	this->console_logger->information("Environment variables have been loaded:");

	std::stringstream ss;
	ss << "Environment variables have been loaded:" << "\n";
	ss << "\t\t\t\t\t POSTGRES_USER_NAME: " << Poco::Environment::get("POSTGRES_USER_NAME") << "\n";
	ss << "\t\t\t\t\t POSTGRES_USER_PASSWORD: " << Poco::Environment::get("POSTGRES_USER_PASSWORD") << "\n";
	ss << "\t\t\t\t\t POSTGRES_DB_NAME: " << Poco::Environment::get("POSTGRES_DB_NAME") << "\n";
	ss << "\t\t\t\t\t POSTGRES_DB_HOST: " << Poco::Environment::get("POSTGRES_DB_HOST") << "\n";
	ss << "\t\t\t\t\t POSTGRES_PORT: " << Poco::Environment::get("POSTGRES_PORT") << "\n";
	ss << "\t\t\t\t\t POCO_SERVER_PORT: " << Poco::Environment::get("POCO_SERVER_PORT");

	this->console_logger->information(ss.str().c_str());
}

int PWS::Server::main(const std::vector<std::string>& args) {
	
	this->console_logger->information("Preparing server params");

	Poco::Net::HTTPServerParams::Ptr params{ new Poco::Net::HTTPServerParams{} };
		params->setMaxQueued(50);
		params->setMaxThreads(4);

	this->console_logger->information("Reading port from config");

	auto port = std::stoi(Poco::Environment::get("POCO_SERVER_PORT"));

	std::stringstream ss;

	ss.str(""); ss << termcolor::colorize << termcolor::green << "PORT " << port << termcolor::reset << ", preparing socket" << termcolor::nocolorize;
	this->console_logger->information(ss.str());

	Poco::Net::ServerSocket socket{ static_cast<Poco::UInt16>(port) };

	this->console_logger->information("Creating fabric");

	RequestFactory::Ptr request_factory{ new RequestFactory{ this->console_logger } };

	this->console_logger->information("Creating server");

	Poco::Net::HTTPServer server{ request_factory, socket, params };

	ss.str(""); ss << termcolor::colorize << termcolor::green << "STARTING SERVER" << termcolor::reset << termcolor::nocolorize;
	this->console_logger->information(ss.str());

	server.start();

	waitForTerminationRequest();

	ss.str(""); ss << termcolor::colorize << termcolor::green << "STOPPING SERVER" << termcolor::reset << termcolor::nocolorize;
	this->console_logger->information(ss.str());

	server.stop();

	return 0;
}
