#pragma once

#ifndef SERVERAPPLICATION_HPP
#define SERVERAPPLICATION_HPP

	#include <server/handlers/htmlhandler.hpp>

	#include <Poco/Net/HTTPServer.h>
	#include <Poco/URI.h>	
	#include <Poco/Path.h>

	#include <Poco/Util/ServerApplication.h>
	#include <Poco/Net/HTTPServer.h>

	namespace PWS {

		class RequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
			
			public:
				RequestFactory();
				Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
		
		};

		class Server : public Poco::Util::ServerApplication {

			int main(const std::vector<std::string>& args) override;

		};

	}



#endif // !SERVERAPPLICATION_HPP
