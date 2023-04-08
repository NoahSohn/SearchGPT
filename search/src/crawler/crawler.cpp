#include "crawler.h"

#include <filesystem>

void crawl(const std::string& file)
{
    std::string file_str = read_file("html/" + file);
    auto parsed_data = parse(file_str);
    std::string begin;
    begin.append("<h1>\n");
    begin.append(parsed_data.h1);
    begin.push_back('\n');
    begin.append("<h2>\n");
    begin.append(parsed_data.h2);
    begin.push_back('\n');
    begin.append("<p>\n");
    begin.append(parsed_data.p);
    begin.push_back('\n');
    begin.append("<links>\n");
    for (auto link : parsed_data.links)
    {
        begin.append(link);
        begin.append("\n");
    }
    begin.push_back('\n');
    write_file(std::string("crawled/" + file) + ".crawltxt", begin);\

    for (auto link : parsed_data.links)
    {
        if (std::filesystem::exists(std::string("crawled/" + link) + ".crawltxt")) continue;
        crawl(link);
    }
}