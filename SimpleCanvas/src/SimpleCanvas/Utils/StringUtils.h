#pragma once

namespace sc
{
// returns vector with strings splitted by delimiter
std::vector<std::string> splitString(std::string const& str, char delimiter)
{
    std::vector<std::string> result;
    result.reserve(str.size());

    std::string piece;
    for (char c : str)
    {
        if (c == delimiter)
        {
            result.push_back(piece);
            piece.clear();
            continue;
        }
        piece += c;
    }

    if (!piece.empty())
        result.push_back(piece);
    return result;
}
} // namespace sc