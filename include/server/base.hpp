#pragma once

#ifndef USEFUL_FUNCTIONS_HPP
#define USEFUL_FUNCTIONS_HPP

	#include <string>
	#include <sstream>
	#include <iostream>

	#include <Poco/Net/HTTPServerResponse.h>
	#include <Poco/Net/HTTPServerRequest.h>
	#include <Poco/Net/HTTPRequestHandler.h>
	
	#include <Poco/Environment.h>
	
	#include <termcolor/termcolor.hpp>
	#include <toml/toml.hpp>

	#include "pws_config.h"

	namespace PWS {
		bool loadEnvironment();
	}

#endif // !USEFUL_FUNCTIONS_HPP
