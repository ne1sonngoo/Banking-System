#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>

inline std::string formatMoney(double amount)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << amount;
    return out.str();
}

#endif
