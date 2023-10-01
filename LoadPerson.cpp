struct PersonParametrs {
    int min_age_;
    int max_age_; 
    string_view name_filter_;

    PersonParametrs& SetMinAge(int min_age) {
        this->min_age_ = min_age;
        return *this;
    }

    PersonParametrs& SetMaxnAge(int max_age) {
        this->max_age_ = max_age;
        return *this;
    }

    PersonParametrs& SetNameFilter(string_view name_filter) {
        this->name_filter_ = name_filter;
        return *this;
    }
};

struct DbParametrs {
    string_view db_name_;
    int db_connection_timeout_;
    bool db_allow_exceptions_;
    DBLogLevel db_log_level_;

    DbParametrs& SetDbName(string_view db_name) {
        this->db_name_ = db_name;
        return *this;
    }

    DbParametrs& SetDbTimeout (int db_connection_timeout) {
        this->db_connection_timeout_ = db_connection_timeout;
        return *this;
    }

    DbParametrs& SetDbExceptions(bool db_allow_exceptions) {
        this->db_allow_exceptions_ = db_allow_exceptions;
        return *this;
    }

    DbParametrs& SetDbExceptions(DBLogLevel db_log_level) {
        this->db_log_level_ = db_log_level;
        return *this;
    }
};

vector<Person> LoadPersons(DbParametrs db_param, PersonParametrs person_param) {

    DBConnector connector(db_param.db_allow_exceptions_, db_param.db_log_level_);

    DBHandler db;

    if ((db_param.db_name_).starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_param.db_name_, db_param.db_connection_timeout_);
    }
    else {
        db = connector.Connect(db_param.db_name_, db_param.db_connection_timeout_);
    }
    if (!db_param.db_allow_exceptions_ && !db.IsOK()) {
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