#include "pagerank.h"

#include <unordered_map>
#include <filesystem>

#include "util.h"

const double damping_factor = 0.85; // damping factor
const int iterations = 100; // number of iterations

std::vector<std::string> gen_webpg_list()
{
    std::vector<std::string> rval;

    for (const auto& entry : std::filesystem::directory_iterator("html/"))
    {
        std::filesystem::path outfilename = entry.path().filename();
        rval.push_back(outfilename.string());
    }

    return rval;
}

std::vector<std::vector<size_t>> gen_adj_graph(const std::vector<std::string>& webpg_list)
{
    std::unordered_map<std::string, size_t> rv_webpg_list;
    for (size_t i = 0; i < webpg_list.size(); i++)
    {
        rv_webpg_list[webpg_list[i]] = i;
    }

    std::vector<std::vector<size_t>> adj_list(webpg_list.size(), std::vector<size_t>(webpg_list.size(), 0));

    for (auto x : webpg_list)
    {
        std::string file = read_file("crawled/" + x + ".crawltxt");
        size_t loc = file.find("<links>");
        loc = file.find("\n", loc);
        for (size_t end_loc = loc; end_loc != std::string::npos; loc = end_loc)
        {
            end_loc = file.find("\n", loc + 1);
            std::string link = file.substr(loc + 1, end_loc - loc - 1);
            if (rv_webpg_list.contains(link)) 
            {
                adj_list[rv_webpg_list[x]][rv_webpg_list[link]] = 1;
            }
        }
    }

    return adj_list;
}

void pagerank(const std::vector<std::vector<size_t>>& adj_graph, std::vector<double>& pr)
{
    int n = adj_graph.size();

    // initialize pagerank values to 1/n
    for (int i = 0; i < n; i++) {
        pr[i] = 1.0 / n;
    }


    // perform iterations
    for (int k = 0; k < iterations; k++) 
    {
        std::vector<double> new_pr(n, 0.0);
        for (int i = 0; i < n; i++) {
            // Calculate parents (incoming links)
            double prc = 0;
            for (size_t j = 0; j < n; j++)
            {
                if (adj_graph[j][i] == 1)
                {
                    size_t num_child = 0;
                    for (size_t k = 0; k < n; k++)
                    {
                        if (adj_graph[j][k] == 1) num_child++;
                    }

                    prc = prc + pr[j] / num_child;
                }
            }
            new_pr[i] = (1 - damping_factor) / n + damping_factor * prc;
        }
        pr = new_pr;
    }
}