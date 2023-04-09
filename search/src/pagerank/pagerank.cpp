#include "pagerank.h"

#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include "util.h"

std::vector<std::string> gen_webpg_list()
{
    std::vector<std::string> list_files;
    for (const auto& entry : std::filesystem::directory_iterator("html/")) {
 
        // Converting the path to const char * in the
        // subsequent lines
        std::filesystem::path outfilename = entry.path();
        list_files.push_back(outfilename.filename().string());
    }
    return list_files;
}

std::unordered_map<std::pair<size_t, size_t>, bool, hash_pair> gen_adj_graph(const std::vector<std::string>& list_pages)
{
    std::unordered_map<std::string, size_t> reverse_list_pages;
    for (size_t i = 0; i < list_pages.size(); i++)
    {
        reverse_list_pages[list_pages[i]] = i;
    }
    std::unordered_map<std::pair<size_t, size_t>, bool, hash_pair> rval;
    for (auto page : list_pages)
    {
        std::string page_file = read_file("crawled/" + page + ".crawltxt");
        size_t i = page_file.find("<links>");
        i = page_file.find("\n", i);
        for (size_t j = i; i != std::string::npos; i = j)
        {
            j = page_file.find("\n", i + 1);
            std::string link = page_file.substr(i + 1, j - i - 1);
            if (reverse_list_pages.contains(link))
            {
                rval[{reverse_list_pages[page], reverse_list_pages[link]}] = 1;
            }
        }
    }

    return rval;
}

std::vector<double> pagerank()
{
    const double d = 0.85; // damping factor
    const double eps = 1e-6; // convergence threshold

    auto list_pages = gen_webpg_list();
    std::unordered_map<std::string, size_t> reverse_list_pages;
    for (size_t i = 0; i < list_pages.size(); i++)
    {
        reverse_list_pages[list_pages[i]] = i;
    }
    size_t num_pages = list_pages.size();
    auto adj_matrix = gen_adj_graph(list_pages);
    std::vector<double> pr;

    // initialize PageRank values
    for (size_t i = 0; i < num_pages; i++) 
    {
        pr[i] = 1.0 / num_pages;
    }

    // iterate until convergence
    while (true) 
    {
        double maxDiff = 0.0;

        // calculate new PageRank values
        std::vector<double> new_PR;
        for (int i = 0; i < num_pages; i++) 
        {
            for (int j = 0; j < num_pages; j++) 
            {
                if (adj_matrix.contains({i, j})) 
                {
                    new_PR[i] += pr[j] * adj_matrix[{i,j}];
                }
            }

            new_PR[i] = d * new_PR[i] + (1 - d) / num_pages;
        }

        // calculate maximum difference
        for (int i = 0; i < num_pages; i++) 
        {
            maxDiff = std::max(maxDiff, abs(pr[i] - new_PR[i]));
        }

        // update PageRank values
        pr = new_PR;

        // check convergence
        if (maxDiff < eps) break;
    }

    std::cout << "here" << std::endl;

    return pr;
}