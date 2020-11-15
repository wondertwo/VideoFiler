//
// Created by papeplus(王尧) on 2020/6/8. 日志工具
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

const std::string COLOR_BLA     = "\033[30m";
const std::string COLOR_RED     = "\033[31m";
const std::string COLOR_YEL     = "\033[33m";
const std::string COLOR_BLU     = "\033[34m";
const std::string COLOR_WHI     = "\033[37m";
const std::string COLOR_RESET   = "\033[0m";


std::vector<std::string> SplitStr(const std::string &input, const std::string &delimiter);

std::vector<std::string> SliceVector(std::vector<std::string> &input, bool reverse_vec, size_t start_idx, size_t len);

std::string GetDirectory(); // Get current workdir

std::string CurrentDateTime(); // Get current date/time, format is YYYY-MM-DD.HH:mm:ss

int vscprintf(const char * format, va_list list);

/*
 * 文件日志
 */
const std::string LOGGER_FILE_PATH = GetDirectory() + "resources/output.txt";


/*
 * 单例模板
 */
template<typename T> class SintonBase {
public:
    static T &GetInstance() {
        static T t;
        return t;
    }

protected:
    ~SintonBase() {};
    SintonBase() {};

private:
    SintonBase &operator=(const SintonBase &) = delete;
    SintonBase(const SintonBase &) = delete;
};

class SintonTestImpl : public SintonBase<SintonTestImpl> { /*单例实现类示例*/
public:
    void print() {
        std::cout << "Hello, this is SintonTestImpl." << std::endl;
    }
};


/*
 * template<typename ostreamT = std::ostream>
 * ref: https://github.com/gabime/spdlog
 */
class LOG {
public:
    enum LOGLevel {
        DEBUG, INFO, WARNING, ERROR
    };

protected:
    static LOG *sInstance;
    static LOG *sInstanceFiler;
    static LOG *sInstanceColor;

    LOGLevel _minLevel;
    bool _color;
    bool _filer;
    std::ostream &_ostream;
    std::ofstream _ofouts;

    explicit LOG(LOGLevel minLevel = INFO, bool color = false, std::ostream &os = std::cout);
    static char *formatInput(const char *format, va_list parameters);

    ~LOG() {
        std::cout << "LOG de-constructor called..." << std::endl;
        if (sInstanceColor) {
            delete sInstanceColor;
            sInstanceColor = nullptr;
        }
        if (sInstanceFiler) {
            delete sInstanceFiler;
            sInstanceFiler = nullptr;
        }
        if (sInstance) {
            delete sInstance;
            sInstance = nullptr;
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

    template<class T, class... X> void output(const T &t, X... xs) {
        output(t);
        output(xs...);
        GetOutStream().flush();
    }

    template<class... T> LOG &operator()(LOGLevel level, T... ts) {
        if (level < (int) _minLevel) {
            return *this;
        }
        std::string level_prefix, color_prefix, color_endfix = COLOR_RESET, current = CurrentDateTime();
        switch (level) {
            case WARNING:
                level_prefix = "[W]";
                color_prefix = COLOR_YEL;
                break;
            case ERROR:
                level_prefix = "[E]";
                color_prefix = COLOR_RED;
                break;
            case DEBUG:
                level_prefix = "[D]";
                color_prefix = COLOR_BLU;
                break;
            case INFO:
                level_prefix = "[I]";
                color_prefix = COLOR_WHI;
                break;
            default:
                color_prefix = COLOR_BLA;
                level_prefix = "";
        }
        std::string prefix = (_color ? color_prefix : "") + current + " " + level_prefix + " ";
        output(prefix, ts..., "\n", (_color ? color_endfix : ""));
        return *this; // Dont forget to return LOG&
    }

public:
    /**
     * 使用template<class T>实现类函数时。若是将函数声明写在.h文件，实现写在.cpp则出现"Undefined symbols for architecture x86_64"
     * 应将申明和实现都放在.h文件
     */
    template<class... Ts> LOG &D(Ts... args) {
        return operator()(DEBUG, args...);
    }

    template<class... Ts> LOG &I(Ts... args) {
        return operator()(INFO, args...);
    }

    template<class... Ts> LOG &W(Ts... args) {
        return operator()(WARNING, args...);
    }

    template<class... Ts> LOG &E(Ts... args) {
        return operator()(ERROR, args...);
    }

    // LOG::Get()->SetLevel(LOG::LOGLevel::ERROR);
    // cout << (int) LOG::Get()->GetLevel() << endl;
    LOGLevel GetLevel() const;
    LOG &SetLevel(LOGLevel level);
    static LOG *GET();
    static LOG *FILER();
    static LOG *COLOR();

    LOG &XE(const char *format, ...);
    LOG &XW(const char *format, ...);
    LOG &XI(const char *format, ...);
    LOG &XD(const char *format, ...);

};


#endif
