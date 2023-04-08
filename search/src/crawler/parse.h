#pragma once

#include <vector>
#include <string>

// Turns a html file into a list of text and a list of links
struct parsed_page
{
    // All of the text in the html file (p, h1, h2)
    std::string h1;
    std::string h2;
    std::string p;

    // All of the links in the html file 
    std::vector<std::string> links;
};

parsed_page parse(const std::string& file);