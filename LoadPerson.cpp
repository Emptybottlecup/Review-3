struct PersonParametrs {
    int min_age_;
    int max_age_; 
    string_view name_filter_;

    PersonParametrs& SetMinAge(int min_age) {
        this->min_age_ = min_age;
        return *this;
    }

    PersonParametrs& SetMaxAge(int max_age) {
        this->max_age_ = max_age;
        return *this;
    }

    PersonParametrs& SetNameFilter(string_view name_filter) {
        this->name_filter_ = name_filter;
        return *this;
    }
};

struct DbParametrs {
    string_view name_;
    int connection_timeout_;
    bool allow_exceptions_;
    DBLogLevel log_level_;

    DbParametrs& SetName(string_view name) {
        this-> name_ = name;
        return *this;
    }

    DbParametrs& SetTimeout (int connection_timeout) {
        this->connection_timeout_ = connection_timeout;
        return *this;
    }

    DbParametrs& SetExceptions(bool allow_exceptions) {
        this->allow_exceptions_ = allow_exceptions;
        return *this;
    }

    DbParametrs& SetLogLevel(DBLogLevel log_level) {
        this->log_level_ = log_level;
        return *this;
    }
};

void DbConnection(DBHandler& db, DbParametrs& db_param) {
    DBConnector connector(db_param.allow_exceptions_, db_param.log_level_);

    if ((db_param.name_).starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_param.name_, db_param.connection_timeout_);
    }
    else {
        db = connector.Connect(db_param.name_, db_param.connection_timeout_);
    }
}

vector<Person> LoadPersons(DbParametrs db_param, PersonParametrs person_param) {

    DBHandler db;

    DbConnection(db, db_param);
    
    if (!db_param.allow_exceptions_ && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << person_param.min_age_ << " and "s << person_param.max_age_ << " "s
        << "and Name like '%"s << db.Quote(person_param.name_filter_) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;

    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}