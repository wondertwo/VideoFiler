//
// Created by wondertwo(王尧) on 2020/6/7.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <zconf.h>
#include <memory>
#include <vector>
#include <mutex>

const std::string COLOR_BLA = "\033[30m";
const std::string COLOR_RED = "\033[31m";
const std::string COLOR_YEL = "\033[33m";
const std::string COLOR_BLU = "\033[34m";
const std::string COLOR_WHI = "\033[37m";


std::vector<std::string> SplitStr(const std::string &input, const std::string &delimiter);

std::vector<std::string> SliceVector(std::vector<std::string> &input, bool reverse_vec, size_t start_idx, size_t len);

std::string GetDirectory(); // Get current workdir

std::string CurrentDateTime(); // Get current date/time, format is YYYY-MM-DD.HH:mm:ss

int _vscprintf(const char * format, va_list list);

/* 文件日志 */
const std::string LOGGER_FILE_PATH = GetDirectory() + "resources/output.txt";

/*template<typename ostreamT = std::ostream>*/ class LOGGER {
public:
    enum LOGLevel {
        DEBUG, INFO, WARNING, ERROR
    };

protected:
    static LOGGER *sInstance;
    static LOGGER *sInstanceFile;
    static LOGGER *sInstanceColor;

    LOGLevel _minLevel;
    bool _color;
    bool _filer;
    std::ostream &_ostream;
    std::ofstream _ofouts;

    LOGGER(LOGLevel minLevel = INFO, bool color = false, std::ostream &os = std::cout);
    static char *formatInput(const char *format, va_list parameters);

    ~LOGGER() {
        std::cout << "LOGGER de-constructor called..." << std::endl;
        if (sInstanceColor) {
            delete sInstanceColor;
            sInstanceColor = NULL;
        }
        if (sInstanceFile) {
            delete sInstanceFile;
            sInstanceFile = NULL;
        }
        if (sInstance) {
            delete sInstance;
            sInstance = NULL;
        }
        if (_ofouts.is_open()) {
            _ofouts.close();
        }
    }

    virtual std::ostream &GetOutStream() {
        if (this->_filer) {
            if (!this->_ofouts.is_open()) {
                this->_ofouts.open(LOGGER_FILE_PATH, std::ios::app);
            }
            return this->_ofouts;
        }
        return this->_ostream;
    }

    template<class T> void output(const T &x) { GetOutStream() << x; }

    template<class T, class... Ts> void output(const T &x, Ts... args) {
        output(x);
        output(args...);
        GetOutStream().flush();
    }

    template<class... Ts> LOGGER &operator()(LOGLevel level, Ts... args) {
        if (level < (int) _minLevel) {
            return *this;
        }
        std::string level_prefix, color_prefix, color_endfix = COLOR_BLA, current = CurrentDateTime();
        switch (level) {
            case WARNING:
                level_prefix = "[WARNING]";
                color_prefix = COLOR_YEL;
                break;
            case ERROR:
                level_prefix = "[ERROR]";
                color_prefix = COLOR_RED;
                break;
            case DEBUG:
                level_prefix = "[DEBUG]";
                color_prefix = COLOR_BLU;
                break;
            case INFO:
                level_prefix = "[INFO]";
                color_prefix = COLOR_WHI;
                break;
            default:
                color_prefix = COLOR_BLA;
                level_prefix = "";
        }
        std::string prefix = (_color ? color_prefix : "") + current + " " + level_prefix + " ";
        output(prefix, args..., "\n", (_color ? color_endfix : ""));
        return *this; // Dont forget to return LOGGER&
    }

public:
    /**
     * 使用template<class T>实现类函数时。若是将函数声明写在.h文件，实现写在.cpp则出现"Undefined symbols for architecture x86_64"
     * 应将申明和实现都放在.h文件
     */
    template<class... Ts> LOGGER &D(Ts... args) {
        return operator()(DEBUG, args...);
    }

    template<class... Ts> LOGGER &I(Ts... args) {
        return operator()(INFO, args...);
    }

    template<class... Ts> LOGGER &W(Ts... args) {
        return operator()(WARNING, args...);
    }

    template<class... Ts> LOGGER &E(Ts... args) {
        return operator()(ERROR, args...);
    }

    // LOGGER::Get()->SetLevel(LOGGER::LOGLevel::ERROR);
    // cout << (int) LOGGER::Get()->GetLevel() << endl;
    LOGLevel GetLevel() const;
    LOGGER &SetLevel(LOGLevel level);
    static LOGGER *Get();
    static LOGGER *GetFile();
    static LOGGER *GetColor();

    LOGGER &XE(const char *format, ...);
    LOGGER &XW(const char *format, ...);
    LOGGER &XI(const char *format, ...);
    LOGGER &XD(const char *format, ...);

};


#endif
