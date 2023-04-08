#include "parse.h"

#include <iostream>

size_t open_greater_ct;

std::string parse_text(const std::string& parse, size_t location, const char* end);

parsed_page parse(const std::string& file)
{
    std::vector<size_t> all_h1_occurences;
    for (size_t i = 0; ; )
    {
        i = file.find("<h1>", i);
        if (i == std::string::npos || i > file.size()) break;
        i += 4;
        all_h1_occurences.push_back(i);
    }

    std::vector<size_t> all_h2_occurences;
    for (size_t i = 0; ; )
    {
        i = file.find("<h2>", i);
        if (i == std::string::npos || i > file.size()) break;
        i += 4;
        all_h2_occurences.push_back(i);
    }

    std::vector<size_t> all_p_occurences;
    for (size_t i = 0; ; )
    {
        i = file.find("<p>", i);
        if (i == std::string::npos || i > file.size()) break;
        i += 3;
        all_p_occurences.push_back(i);
    }

    std::vector<size_t> all_href_occurences;
    for (size_t i = 0; ; )
    {
        i = file.find("<a href=\"", i);
        if (i == std::string::npos || i > file.size()) break;
        i += 9;
        all_href_occurences.push_back(i);
    }

    parsed_page rval;

    all_h1_occurences.shrink_to_fit();
    for (auto x : all_h1_occurences)
    {
        rval.h1.append(parse_text(file, x, "</h1>"));
        rval.h1.push_back(' ');
    }

    all_h2_occurences.shrink_to_fit();
    for (auto x : all_h2_occurences)
    {
        rval.h2.append(parse_text(file, x, "</h2>"));
        rval.h2.push_back(' ');
    }

    all_p_occurences.shrink_to_fit();
    for (auto x : all_p_occurences)
    {
        rval.p.append(parse_text(file, x, "</p>"));
        rval.p.push_back(' ');
    }

    all_href_occurences.shrink_to_fit();
    for (auto x : all_href_occurences)
    {
        size_t end_st = file.find('"', x);
        std::string output = file.substr(x, end_st - x);
        rval.links.push_back(output);
    }
    
    return rval;
}

std::string parse_text(const std::string& parse, size_t location, const char* end)
{
    size_t end_st = parse.find(end, location);
    std::string check_for_greater = parse.substr(location, end_st - location);
    std::string output;
    for (size_t i = 0; i < check_for_greater.size(); i++)
    {
        if (check_for_greater[i] == '<') 
        {
            size_t greater_ct = 1;
            for (; ; i++)
            {
                if (greater_ct == 0) break;
                if (i > check_for_greater.size()) break;
                if (check_for_greater[i] == '<') greater_ct++;
                if (check_for_greater[i] == '>') greater_ct--;
            }
            continue;
        }

        output.push_back(check_for_greater[i]);
    }   
    return output;
}