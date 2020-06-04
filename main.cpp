
#include <iostream>
#include "video_format_parser.h"
#include <stdio.h>
#include <zconf.h>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @param input
 * @param delimiter
 * @return
 */
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
    return 0; // end main
}
