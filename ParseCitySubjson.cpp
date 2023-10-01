struct ParseCityParam {
    vector<City>& cities_; 
    const Json& json_;
    const string& country_name_;
    const string& country_iso_code_;
    const string& country_phone_code_;
    const string& country_time_zone_; 
    const vector<Language>& languages_;
    ParseCityParam& SetVectorCities(vector<City>& cities) {
        this->cities_ = cities;
        return *this;
    }
    ParseCityParam& SetJson(const Json& json) {
        this->json_ = json;
        return *this;
    }
    ParseCityParam& SetCountryName(const string& name) {
        this->country_name_ = name;
        return *this;
    }

    ParseCityParam& SetCountryIsoCode(const string& code) {
        this->country_iso_code_ = code;
        return *this;
    }
    ParseCityParam& SetCountryPhoneCode(const string& phone) {
        this->country_phone_code_ = phone;
        return *this;
    }

    ParseCityParam& SetCountryTime(const string& time) {
        this->country_time_zone_ = time;
        return *this;
    }

    ParseCityParam& SetVectorLanguage(const vector<Language>& languages) {
        this->languages_ = languages;
        return *this;
    }
};

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
void ParseCitySubjson(ParseCityParam parametrs) {
    for (const auto& city_json : (parametrs.json_).AsList()) {
        const auto& city_obj = city_json.AsObject();
        (parametrs.cities_).push_back({ city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          parametrs.country_phone_code_ + city_obj["phone_code"s].AsString(), parametrs.country_name_, parametrs.country_iso_code_,
                          parametrs.country_time_zone_, parametrs.languages_ });
    }
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
            });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCityParam parametrs;
        ParseCitySubjson(parametrs.SetVectorCities(cities).SetJson(country_obj["cities"s]).SetCountryName(country.name).SetCountryIsoCode(country.iso_code).SetCountryPhoneCode(country.phone_code).
            SetCountryTime(country.time_zone).SetVectorLanguage(country.languages));
    }
}