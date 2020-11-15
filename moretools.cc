//
// Created by papeplus(王尧) on 2020/6/8. 日志工具
//

#include "moretools.h"

LOG *LOG::sInstanceColor = nullptr;
LOG *LOG::sInstanceFiler = nullptr;
LOG *LOG::sInstance = nullptr;

LOG::LOG(LOGLevel minLevel, bool color, std::ostream &os) :
        _minLevel(minLevel), _color(color), _filer(false), _ostream(os),
        _ofouts(LOGGER_FILE_PATH, std::ios::app) {
}

/*
 * 获取日志打印实例，将日志信息输出到控制台，并附着日志等级颜色，大多数场景下推荐使用此方式
 */
LOG *LOG::COLOR() {
    if (!sInstanceColor) sInstanceColor = new LOG(DEBUG, true);
    return sInstanceColor;
}

/*
 * 获取日志打印实例，将日志输出到日志文件中，一些比较关键的日志建议才使用文件输出，方便回溯
 */
LOG *LOG::FILER() {
    if (!sInstanceFiler) {
        sInstanceFiler = new LOG(DEBUG, false);
        sInstanceFiler->_color = false;
        sInstanceFiler->_filer = true;
    }
    return sInstanceFiler;
}

LOG *LOG::GET() {
    if (!sInstance) sInstance = new LOG(DEBUG, false);
    return sInstance;
}

LOG::LOGLevel LOG::GetLevel() const {
    return this->_minLevel;
}

LOG &LOG::SetLevel(LOGLevel level) {
    this->_minLevel = level;
    return *this;
}

char *LOG::formatInput(const char *format, va_list parameters) {
    //  Return the number of characters in the string referenced the list of arguments.
    // _vscprintf doesn't count terminating '\0' (that's why +1)
    int nLen = vscprintf(format, parameters) + 1;
    char *sInfo = new char[nLen];
    // vsprintf_s(sMessage, nLength, format, args);
    vsprintf(sInfo, format, parameters);
    // std::cout << sInfo << std::endl;
    return sInfo;
}

LOG &LOG::XD(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOG &instanc = operator()(DEBUG, sInfo);
    delete[] sInfo;
    return instanc;
}

LOG &LOG::XI(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOG &instanc = operator()(INFO, sInfo);
    delete[] sInfo;
    return instanc;
}

LOG &LOG::XW(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOG &instanc = operator()(WARNING, sInfo);
    delete[] sInfo;
    return instanc;
}

LOG &LOG::XE(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);
    char *sInfo = formatInput(format, parameters);
    va_end(parameters);
    LOG &instanc = operator()(ERROR, sInfo);
    delete[] sInfo;
    return instanc;
}


std::string CurrentDateTime() { // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    time_t now = time(nullptr);
    tm tstruct{};
    char buf[80];
    localtime_r(&now, &tstruct);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

int vscprintf(const char * format, va_list list) {
    int retVal;
    va_list vaList;
    va_copy(vaList, list);
    retVal = vsnprintf(nullptr, 0, format, vaList);
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
