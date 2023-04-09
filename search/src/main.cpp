#include <iostream>

#include "crawler/crawler.h"
#include "pagerank/pagerank.h"
#include "databasegen/databasegen.h"

int main(void)
{
    crawl("1.html");

    std::vector<std::string> webpg_list = gen_webpg_list();
    std::vector<double> pr(webpg_list.size(), 0);

    calc_database();
}