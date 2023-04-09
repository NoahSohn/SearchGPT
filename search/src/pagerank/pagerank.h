#pragma once

#include <unordered_map>
#include <string>
#include <vector>

std::vector<std::string> gen_webpg_list();
std::vector<std::vector<size_t>> gen_adj_graph(const std::vector<std::string>& webpg_list);
void pagerank(const std::vector<std::vector<size_t>>& adj_graph, std::vector<double>& output);