enum class Error {
    YEAR_IS_TOO_SMALL,
    YEAR_IS_TOO_BIG,
    MONTH_IS_TOO_SMALL,
    MONTH_IS_TOO_BIG,
    DAY_IS_TOO_SMALL,
    DAY_IS_TOO_BIG,
    HOUR_IS_TOO_SMALL,
    HOUR_IS_TOO_BIG,
    MINUTE_IS_TOO_SMALL,
    MINUTE_IS_TOO_BIG,
    SECOND_IS_TOO_SMALL,
    SECOND_IS_TOO_BIG,
};


std::array<std::string_view> message = {
    {"year is too small"},
    {"year is too big"},
    {"month is too small"},
    {"month is too big"},
    {"day is too small"},
    {"day is too big"},
    {"hour is too small"},
    {"year is too big"},
    {"minute is too small"},
    {"minute is too big"},
    {"second is too small"},
    {"second is too big"},
};

vector<Error> CheckDateTimeError(const DateTime& dt) {
    std::vector<Error> errors;
    if (dt.year < 1) {
        errors.push_back(Error::YEAR_IS_TOO_SMALL);
    }
    if (dt.year > 9999) {
        errors.push_back(Error::YEAR_IS_TOO_BIG);
    }

    if (dt.month < 1) {
        errors.push_back(Error::MONTH_IS_TOO_SMALL);
    }
    if (dt.month > 12) {
        errors.push_back(Error::MONTH_IS_TOO_BIG);
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < 1) {
        errors.push_back(Error::DAY_IS_TOO_SMALL);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        errors.push_back(Error::DAY_IS_TOO_BIG);
    }

    if (dt.hour < 0) {
        errors.push_back(Error::HOUR_IS_TOO_SMALL);
    }
    if (dt.hour > 23) {
        errors.push_back(Error::HOUR_IS_TOO_BIG);
    }

    if (dt.minute < 0) {
        errors.push_back(Error::MINUTE_IS_TOO_SMALL);
    }
    if (dt.minute > 59) {
        errors.push_back(Error::MINUTE_IS_TOO_BIG);
    }

    if (dt.second < 0) {
        errors.push_back(Error::SECOND_IS_TOO_SMALL);
    }
    if (dt.second > 59) {
        errors.push_back(Error::SECOND_IS_TOO_BIG);
    }
    return errors;
}

void CheckDateTimeValidity(const DateTime& dt) {
    auto errors = CheckDateTimeError(dt);
    if (!errors.empty()) {
        for (const auto& error : errors) {
            throw domain_error(message[static_cast<size_t>(errors.front())]);
        }
    }
}