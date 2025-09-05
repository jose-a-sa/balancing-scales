#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <string_view>

/**
 * @brief Reads lines from a CSV-formatted input stream and processes each row via callback.
 *
 * @tparam Columns   The number of columns expected in each CSV row.
 * @tparam Stream    The type of the input stream (e.g., std::istream).
 * @tparam Callable  The type of the callback function to process each row.
 *
 * @param stream         The input stream to read CSV lines from.
 * @param row_callback   A callable object that takes a std::array<std::string_view, Columns>
 *                       representing the columns of a row.
 */
template<size_t Columns, class Stream, class Callable>
void read_csv_lines(Stream& stream, Callable&& row_callback)
{
    auto not_isspace = [](char ch) { return !std::isspace(ch); };

    auto ltrim = [&](auto& s) { s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_isspace)); };
    auto rtrim = [&](auto& s) { s.erase(std::find_if(s.rbegin(), s.rend(), not_isspace).base(), s.end()); };

    std::string buffer;
    while(std::getline(stream, buffer))
    {
        ltrim(buffer);
        rtrim(buffer);
        if(buffer.empty() || buffer[0] == '#')
            continue;

        std::string_view line_view{buffer}; // to get std::string_view when calling ::substr
        size_t           start = 0;

        std::array<std::string_view, Columns> parts{};
        for(auto& part: parts)
        {
            auto const end = line_view.find(',', start);
            part           = line_view.substr(start, end - start);

            if(end == std::string_view::npos)
                break;

            start = end + 1;
        }

        row_callback(parts);
    }
}
