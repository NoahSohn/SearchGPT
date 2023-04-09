#include <iostream>

#include "crawler/crawler.h"
#include "pagerank/pagerank.h"

int main(void)
{
    std::vector<std::string> webpg_list = gen_webpg_list();
    std::vector<double> pr(webpg_list.size(), 0);

    pagerank(gen_adj_graph(webpg_list), pr);
    for (size_t i = 0; i < pr.size(); i++)
    {
        std::cout << webpg_list[i] << ", " << pr[i] << std::endl;
    }

    
}