#pragma once

#include <vector>
#include <string>

std::string load_csv(const std::string& filepath);

// Gets the text from .crawltxt file, filters words, and filters out csv
std::vector<std::string> get_words(const std::string& filepath);

// Calculates the tf from a docs words
std::string tf_calc_line(const std::string& doc, const std::vector<std::string>& words);

// The main function that calculates the database for all files
void calc_database();