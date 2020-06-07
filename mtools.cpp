//
// Created by wondertwo(王尧) on 2020/6/7.
//

#include "mtools.h"

LOGGER *LOGGER::sInstanceColor = NULL;
LOGGER *LOGGER::sInstanceFile = NULL;
LOGGER *LOGGER::sInstance = NULL;

LOGGER::LOGGER(LOGLevel minLevel, bool color, std::ostream &os) :
        _minLevel(minLevel), _color(color), _filer(false), _ostream(os),
        _ofouts(LOGGER_FILE_PATH, std::ios::app) {
}

LOGGER *LOGGER::GetColor() {
    if (!sInstanceColor) sInstanceColor = new LOGGER(DEBUG, true);
    return sInstanceColor;
}

LOGGER *LOGGER::GetFile() {
    if (!sInstanceFile) {
        sInstanceFile = new LOGGER(DEBUG, false);
        sInstanceFile->_color = false;
        sInstanceFile->_filer = true;
    }
    return sInstanceFile;
}

LOGGER *LOGGER::Get() {
    if (!sInstance) sInstance = new LOGGER(DEBUG, false);
    return sInstance;
}

LOGGER::LOGLevel LOGGER::GetLevel() const {
    return this->_minLevel;
}

LOGGER &LOGGER::SetLevel(LOGLevel level) {
    this->_minLevel = level;
    return *this;
}

char *LOGGER::formatInput(const char *format, va_list parameters) {
    //  Return the number of characters in the string referenced the list of arguments.
    // _vscprintf doesn't count terminating '\0' (that's why +1)
    int nLen = _vscprintf(format, parameters) + 1;
    char *sInfo = new char[nLen];
    // vsprintf_s(sMessage, nLength, format, args);
    vsprintf(sInfo, format, parameters);
    // std::cout << sInfo << std::endl;
    return sInfo;
}

LOGGER &LOGGER::XD(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOGGER &instanc = operator()(DEBUG, sInfo);
    delete[] sInfo;
    return instanc;
}

LOGGER &LOGGER::XI(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOGGER &instanc = operator()(INFO, sInfo);
    delete[] sInfo;
    return instanc;
}

LOGGER &LOGGER::XW(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOGGER &instanc = operator()(WARNING, sInfo);
    delete[] sInfo;
    return instanc;
}

LOGGER &LOGGER::XE(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOGGER &instanc = operator()(ERROR, sInfo);
    delete[] sInfo;
    return instanc;
}


std::string CurrentDateTime() { // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    time_t now = time(NULL);
    tm tstruct{};
    char buf[80];
    localtime_r(&now, &tstruct);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

int _vscprintf(const char * format, va_list list) {
    int retVal;
    va_list vaList;
    va_copy(vaList, list);
    retVal = vsnprintf(NULL, 0, format, vaList);
    va_end(vaList);
    return retVal;
}

std::vector<std::string> SplitStr(const std::string &input, const std::string &delimiter) {
    char *input_c = new char[strlen(input.c_str()) + 1];
    strcpy(input_c, input.c_str());

    std::vector<std::string> result;
    char *slice = strtok(input_c, delimiter.c_str());
    while (slice != nullptr) {
        result.emplace_back(slice);
        slice = strtok(nullptr, delimiter.c_str());
    }
    delete[] input_c;
    return result;
}

std::vector<std::string> SliceVector(std::vector<std::string> &input, bool reverse_vec, size_t start_idx, size_t len) {
    if (input.empty()) return input;
    if (reverse_vec) reverse(input.begin(), input.end());

    size_t end_idx = std::min(start_idx + len, input.size());
    std::vector<std::string> result_vec;

    for (size_t i = start_idx; i < end_idx; ++i) {
        result_vec.push_back(input[i]);
    }
    return result_vec;
}

std::string GetDirectory() { /* take project root dir */
    std::vector<std::string> dirs = SplitStr(std::string(getcwd(nullptr, 0)), "/");
    dirs = SliceVector(dirs, false, 0, dirs.size() - 1);
    std::string project_dir = "/";
    for (const auto &item : dirs) project_dir += item + "/";
    // std::cout << "current work dir:" << project_dir << std::endl;
    return project_dir;
}
