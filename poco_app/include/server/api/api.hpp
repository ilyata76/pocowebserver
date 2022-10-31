	//PWS::PostgreSQLSession postgres_session{};
	//
	//auto x = postgres_session.getSession();
	//
	//Poco::Data::Statement statement(x);
	//
	//struct Person { std::string fname; std::string lname; } person;
	//statement << "SELECT first_name, last_name FROM test1;",
	//Poco::Data::Keywords::into(person.fname),
	//Poco::Data::Keywords::into(person.lname),
	//Poco::Data::Keywords::range(0, 1);
	//
	//statement.execute();
	//
	//std::cout << person.fname;