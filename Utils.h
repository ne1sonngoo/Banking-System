#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

inline std::string currentTimestamp()
{
    std::time_t now = std::time(nullptr);
    std::tm *lt = std::localtime(&now);

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", lt);
    return buffer;
}

inline std::string formatMoney(double amount)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << amount;
    return out.str();
}

#endif
