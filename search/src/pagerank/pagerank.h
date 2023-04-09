#pragma once

#include <unordered_map>
#include <string>
#include <vector>

// A hash function used to hash a pair of any kind
struct hash_pair 
{
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
 
        if (hash1 != hash2) 
        {
            return hash1 ^ hash2;             
        }
         
        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

std::unordered_map<std::pair<size_t, size_t>, bool, hash_pair> gen_adj_graph();
std::vector<std::string> gen_webpg_list();
std::vector<double> pagerank();