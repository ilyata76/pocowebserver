#include <server/serverapplication.hpp>

PWS::RequestFactory::RequestFactory(Poco::Logger::Ptr console_logger) {
	this->console_logger = console_logger;
}

Poco::Net::HTTPRequestHandler* PWS::RequestFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
	Poco::URI uri{ request.getURI() };
	Poco::Path path{ uri.getPath() };

	bool is_html_file = (
		(
			path.getExtension() == "html" || path.getExtension() == ""
		) && (
			path.directory(0) != "api" && path.directory(0) != "css" && path.directory(0) != "img" && path.directory(0) != "js"
		)
	);

	this->console_logger->information(request.getMethod() + "  |  " + request.getURI() + "  |  ");
	if (is_html_file || (path.directory(0) == "/" || path.directory(0) == "")) {
		this->console_logger->information("creating html handler");
		return new HTMLHandler{ uri, console_logger };
	}

	this->console_logger->error("handler was not found");
	return nullptr; // TODO: htmlerror
}

int PWS::Server::main(const std::vector<std::string>& args) {
	// creating console logger

	Poco::PatternFormatter::Ptr console_pattern_formatter{ new Poco::PatternFormatter {"[PWS][%Y-%m-%d:%H%M%S][%p] %t"} };
	Poco::FormattingChannel::Ptr pFCConsole{ new Poco::FormattingChannel{console_pattern_formatter} };
	pFCConsole->setChannel(new Poco::ConsoleChannel{});
	pFCConsole->open();
	Poco::Logger& console_logger = Poco::Logger::create("ConsoleLogger", pFCConsole);

	//
	
	console_logger.information("Preparing server params");

	Poco::Net::HTTPServerParams::Ptr params{ new Poco::Net::HTTPServerParams{} };
		params->setMaxQueued(50);
		params->setMaxThreads(4);

	console_logger.information("Reading port from config");

	std::stringstream ss; ss << config_app_folder << "/config.toml";
		auto data = toml::parse(ss.str().c_str());
		auto port = static_cast<int>(data["PORT"].as_integer());


	ss.str(""); ss << termcolor::colorize << termcolor::green << "PORT " << port << termcolor::reset << ", preparing socket" << termcolor::nocolorize;
	console_logger.information(ss.str());

	Poco::Net::ServerSocket socket{ static_cast<Poco::UInt16>(port) };

	console_logger.information("Creating fabric");

	RequestFactory::Ptr request_factory{ new RequestFactory{ &console_logger } };

	console_logger.information("Creating server");

	Poco::Net::HTTPServer server{ request_factory, socket, params };

	ss.str(""); ss << termcolor::colorize << termcolor::green << "STARTING SERVER" << termcolor::reset << termcolor::nocolorize;
	console_logger.information(ss.str());

	server.start();

	waitForTerminationRequest();

	ss.str(""); ss << termcolor::colorize << termcolor::green << "STOPPING SERVER" << termcolor::reset << termcolor::nocolorize;
	console_logger.information(ss.str());

	server.stop();

	return 0;
}
