
enum class Error {
    OK,
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


const map<Error, string> message = {
    {Error::YEAR_IS_TOO_SMALL,"year is too small"},
    {Error::YEAR_IS_TOO_BIG,"year is too big"},
    {Error::MONTH_IS_TOO_SMALL,"month is too small"},
    {Error::MONTH_IS_TOO_BIG,"month is too big"},
    {Error::DAY_IS_TOO_SMALL,"day is too small"},
    {Error::DAY_IS_TOO_BIG,"day is too big"},
    {Error::HOUR_IS_TOO_SMALL,"hour is too small"},
    {Error::HOUR_IS_TOO_BIG,"year is too big"},
    {Error::MINUTE_IS_TOO_SMALL,"minute is too small"},
    {Error::MINUTE_IS_TOO_BIG,"minute is too big"},
    {Error::SECOND_IS_TOO_SMALL,"second is too small"},
    {Error::SECOND_IS_TOO_BIG,"second is too big"},
};

Error CheckDateTimeError(const DateTime& dt) {
    if (dt.year < 1) {
        return Error::YEAR_IS_TOO_SMALL;
    }
    if (dt.year > 9999) {
        return Error::YEAR_IS_TOO_BIG;
    }

    if (dt.month < 1) {
        return Error::MONTH_IS_TOO_SMALL;
    }
    if (dt.month > 12) {
        return Error::MONTH_IS_TOO_BIG;
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < 1) {
        return Error::DAY_IS_TOO_SMALL;
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        return Error::DAY_IS_TOO_BIG;
    }

    if (dt.hour < 0) {
        return Error::HOUR_IS_TOO_SMALL;
    }
    if (dt.hour > 23) {
        return Error::HOUR_IS_TOO_BIG;
    }

    if (dt.minute < 0) {
        return Error::MINUTE_IS_TOO_SMALL;
    }
    if (dt.minute > 59) {
        return Error::MINUTE_IS_TOO_BIG;
    }

    if (dt.second < 0) {
        return Error::SECOND_IS_TOO_SMALL;
    }
    if (dt.second > 59) {
        return Error::SECOND_IS_TOO_BIG;
    }
    return Error::OK;
}

void CheckDateTimeValidity(const DateTime& dt) {
    auto error = CheckDateTimeError(dt);
    if (error != Error::OK) {
        throw domain_error(message.at(error));
    }
}