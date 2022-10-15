#include <iostream>
#include <server/serverapplication.hpp>

#include <termcolor/termcolor.hpp>


int main(int argc, char** argv) {

	try {
		std::stringstream ss;
		ss << termcolor::colorize << termcolor::red << "abobus!\n";
		std::cout << ss.str();
		PWS::Server app;
		return app.run(argc, argv);



	} catch (Poco::Exception& exc) { // exc от поки
		std::cerr << exc.displayText() << std::endl;
		return Poco::Util::Application::EXIT_SOFTWARE;
	} catch (std::exception& exc) { // exc от стандартной библиотеки
		std::cerr << exc.what() << std::endl;
		return 1;
	}
}