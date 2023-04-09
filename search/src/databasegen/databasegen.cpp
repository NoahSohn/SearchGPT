#include "databasegen.h"

#include "util.h"
#include "pagerank/pagerank.h"

#include <sstream>

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

std::vector<std::string> get_words(const std::string& filepath)
{
    auto csv = read_file("resources/syncategorematic.csv");
    std::string crawler_file = read_file(filepath);

    crawler_file.erase(crawler_file.find("<links>"));
    
    std::vector<std::string> rval;
    rval.push_back("");

    // Get words 
    for (size_t i = 0; i < crawler_file.size(); i++)
    {   
        if (crawler_file[i] == ' ') 
        {
            if (csv.find(rval.back()) != std::string::npos) rval.back() = "";
            else rval.push_back("");
            continue;
        }
        if (std::string(ALPHABET).find(crawler_file[i]) != std::string::npos) 
        {
            rval.back().push_back(crawler_file[i]);
        }
    }

    return rval;
}

std::string tf_calc_line(const std::string& doc, const std::vector<std::string>& words)
{
    std::unordered_map<std::string, size_t> unique_words;
    for (auto word : words)
    {
        if (word == "") continue;
        unique_words[word] += words.size();
    }

    std::stringstream sstream;
    sstream << doc << ",";
    
    for (auto pair : unique_words)
    {
        sstream << pair.first << "," << pair.second << ",";
    }

    return sstream.str();
}

void calc_database()
{
    std::string tf;
    std::vector<std::string> webpg = gen_webpg_list();

    std::unordered_map<std::string, std::vector<std::string>> words_to_doc;
    for (auto page : webpg)
    {
        words_to_doc[page] = get_words("crawled/" + page + ".crawltxt");
        tf.append(tf_calc_line(page, words_to_doc[page]));
        tf.append("\n\n");
    }

    std::string idf_str;
    std::unordered_map<std::string, size_t> idf;
    for (auto doc : words_to_doc)
    {
        for (auto word : doc.second)
        {
            if (word == "") continue;
            idf[word] += webpg.size();
        }
    }

    std::stringstream sstream;

    for (auto pair : idf)
    {
        sstream << pair.first << "," << pair.second << ",";
    }

    std::vector<double> pr(webpg.size());
    pagerank(gen_adj_graph(webpg), pr);

    std::stringstream prstr;
    for (size_t i = 0; i < webpg.size(); i++)
    {
        prstr << webpg[i] << "," << pr[i] << ",";
    }

    write_file("datasets/tf.csv", tf);
    write_file("datasets/idf.csv", sstream.str());
    write_file("datasets/pr.csv", prstr.str());
}