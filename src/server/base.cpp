#include <server/base.hpp>

bool PWS::loadEnvironment() {
    try {

        std::stringstream ss; ss << config_app_folder << "/config.toml";

        auto data = toml::parse(ss.str().c_str());

        if (!Poco::Environment::has("POSTGRES_USER_NAME"))
            Poco::Environment::set("POSTGRES_USER_NAME", static_cast<std::string>(data["POSTGRES_USER_NAME"].as_string()));

        if (!Poco::Environment::has("POSTGRES_USER_PASSWORD"))
            Poco::Environment::set("POSTGRES_USER_PASSWORD", static_cast<std::string>(data["POSTGRES_USER_PASSWORD"].as_string()));

        if (!Poco::Environment::has("POSTGRES_DB_NAME"))
            Poco::Environment::set("POSTGRES_DB_NAME", static_cast<std::string>(data["POSTGRES_DB_NAME"].as_string()));
        
        if (!Poco::Environment::has("POSTGRES_DB_HOST"))
            Poco::Environment::set("POSTGRES_DB_HOST", static_cast<std::string>(data["POSTGRES_DB_HOST"].as_string()));

        if (!Poco::Environment::has("POSTGRES_PORT"))
            Poco::Environment::set("POSTGRES_PORT", std::to_string(data["POSTGRES_PORT"].as_integer()));
        
        if (!Poco::Environment::has("POCO_SERVER_PORT"))
            Poco::Environment::set("POCO_SERVER_PORT", std::to_string(data["POCO_SERVER_PORT"].as_integer()));

        return true;

    } catch(...) {
        return false;
    }
}