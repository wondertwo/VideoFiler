
#include <iostream>
#include "video_format_parser.h"
#include <stdio.h>
#include <zconf.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct President { /* explains the different between vector#emplace_back and vector#push_back */
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(const President& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being copy constructed.\n";
    }
    President(President&& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other);
};

void testPresidentElections() { /* test the different between vector#emplace_back and vector#push_back */
    std::vector<President> elections;
    std::cout << "emplace_back:" << endl;
    elections.emplace_back("Nelson Mandela", "South Africa", 1994); //没有类的创建

    std::vector<President> reElections;
    std::cout << "push_back:" << endl;
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "contents:" << endl;
    for (const President &president: elections) {
        std::cout << president.name << " was elected president of " << president.country << " in " << president.year << endl;
    }
    for (President const& president: reElections) {
        std::cout << president.name << " was re-elected president of " << president.country << " in " << president.year << endl;
    }
}

vector<string> split_str(const string &input, const string &delimiter) {
    char *input_c = new char[strlen(input.c_str()) + 1];
    strcpy(input_c, input.c_str());

    vector<string> result;
    char *slice = strtok(input_c, delimiter.c_str());
    while (slice != nullptr) {
        result.emplace_back(slice);
        slice = strtok(nullptr, delimiter.c_str());
    }
    delete[] input_c;
    return result;
}

vector<string> slice_vector(vector<string> &input, bool reverse_vec, size_t start_idx, size_t len) {
    if (input.empty()) return input;
    if (reverse_vec) reverse(input.begin(), input.end());

    size_t end_idx = min(start_idx + len, input.size());
    vector<string> result_vec;

    for (size_t i = start_idx; i < end_idx; ++i) {
        result_vec.push_back(input[i]);
    }
    return result_vec;
}

string join_str_vector(const vector<string> &str_vector, const string &delimiter, int start_idx, int len) {
    /*for (auto iter = str_vector.begin(); iter != str_vector.end(); iter++) {
        cout << (*iter) << endl;
    }*/

    /*for (vector<string>::iterator iter = str_vector.begin(); iter != str_vector.end(); iter++) {
        cout << *iter << endl;
    }*/

    if (str_vector.empty() || start_idx >= str_vector.size()) {
        return nullptr;
    }

    for (const auto &iter : str_vector) {
        cout << iter << endl;
    }

    // int sat = static_cast<int>(reverse ? str_vector.size() - 1 : 0);
    // int end = static_cast<int>(reverse ? -1 : str_vector.size());

    int end_idx = max(start_idx, static_cast<int>(str_vector.size()));
    string result_str;
    for (int i = start_idx; i < end_idx; ++i) {
        result_str += str_vector[i];
    }
    return result_str;
}

//======================================================================================================
int main() {
    char *current_dir = getcwd(nullptr, 0);
    cout << "hello, world! current work dir:" << current_dir << endl;

    vector<string> dirs = split_str(string(current_dir), "/");
    for (const auto &iter : dirs) cout << iter << "," << ends;

    dirs = slice_vector(dirs, false, 0, dirs.size() - 1);
    string videopath = "/";
    for (const auto &item : dirs) videopath += item + "/";
    videopath += "resources/videofiler.mp4";
    cout << "video path:" << videopath << endl;

    extractVideoFormatInfo(videopath);
    testPresidentElections();
    return 0; // end main
}
