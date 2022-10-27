#include <iostream>

#include "server/serverapplication.hpp"
#include "server/base.hpp"

int main(int argc, char** argv) {

	try {
		PWS::Server app;
		return app.run(argc, argv);

	} catch (Poco::Exception& exc) { 
		std::cerr << exc.displayText() << std::endl;
		return Poco::Util::Application::EXIT_SOFTWARE;
	} catch (std::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
}