
#include <iostream>
#include <zconf.h>
#include <vector>
#include <string>
#include "moretools.h"

using namespace std;

struct President { /* explains the different between vector#emplace_back and vector#push_back */
    std::string name;
    std::string country;
    int year;

    President(std::string p_name, std::string p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
        std::cout << "I am being constructed.\n";
    }

    President(const President &other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year) {
        std::cout << "I am being copy constructed.\n";
    }

    President(President &&other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year) {
        std::cout << "I am being moved.\n";
    }

    President &operator=(const President &other);
};

void AmericaElection_TrumpWithBiden() { /* test the different between vector#emplace_back and vector#push_back */
    std::vector<President> elections;
    std::cout << "emplace_back:" << endl;
    elections.emplace_back("Nelson Mandela", "South Africa", 1994); //没有类的创建

    std::vector<President> reElections;
    std::cout << "push_back:" << endl;
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "contents:" << endl;
    for (const President &president: elections) {
        std::cout << president.name << " was elected president of " << president.country << " in " << president.year
                  << endl;
    }
    for (President const &president: reElections) {
        std::cout << president.name << " was re-elected president of " << president.country << " in " << president.year
                  << endl;
    }
}

class MyStrTransfer { /*转移语义以及转移构造函数和转移复制运算符*/
private:
    char *_data;
    size_t _len;

    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }

public:
    MyStrTransfer &operator = (MyStrTransfer &&str)  noexcept {  /* move operator */
        std::cout << "Move Assignment is called! source: " << str._data << std::endl;
        if (this != &str) {
            _len = str._len;
            _data = str._data;
            str._len = 0;
            str._data = nullptr;
        }
        return *this;
    }

    MyStrTransfer(MyStrTransfer &&str) {  /* move constructor */
        std::cout << "Move Constructor is called! source: " << str._data << std::endl;
        _len = str._len;
        _data = str._data;
        str._len = 0;
        str._data = nullptr;
    }

    MyStrTransfer &operator=(const MyStrTransfer &str) {
        if (this != &str) {
            _len = str._len;
            _init_data(str._data);
        }
        std::cout << "Copy Assignment is called! Source: " << str._data << std::endl;
        return *this;
    }

    MyStrTransfer(const MyStrTransfer &str) {
        _len = str._len;
        _init_data(str._data);
        std::cout << "Copy Constructor is called! Source: " << str._data << std::endl;
    }

    MyStrTransfer(const char *p) {
        _len = strlen(p);
        _init_data(p);
    }

    MyStrTransfer() {
        _data = nullptr;
        _len = 0;
    }

    virtual ~MyStrTransfer() {
        if (_data) free(_data);
    }
};

/**
 * MyString(“Hello”)/MyString(“World”) 都是临时对象（也就是右值）。虽然它们是临时的，但程序仍然调用了拷贝构造和拷贝赋值（没有意义的资源申请和释放操作）
 * 如果能够直接使用临时对象已经申请的资源，既能节省资源，又能节省资源申请和释放的时间。正是定义转移语义的目的。
 * 编译器区分了左值和右值，对右值调用了转移构造函数和转移赋值操作符。
 * 有了右值引用和转移语义，我们在设计和实现类时，对于需要动态申请大量资源的类，应该设计转移构造函数和转移赋值函数，以提高应用程序的效率。
 * https://blog.csdn.net/xiaolewennofollow/article/details/52559306
 */
void testMyStrTransfer() {
    // 1.
    MyStrTransfer transfer = MyStrTransfer("Hello");
    // 2.
    transfer = MyStrTransfer("World");

    std::vector<MyStrTransfer> vec;
    vec.emplace_back("Homie");
    // 3.
    vec.push_back(MyStrTransfer("Blood"));
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

/*
 * ---------------------------------------------------------------------------------
 * https://github.com/fmtlib/fmt
 */
int main(int argc, const char **argv) {
    string path = GetDirectory() + "resources/videofiler.mp4";
    string info = "hello world, video path:%s";
    // 一般用法，支持字符串格式化，推荐使用
    LOG::GET()->E(path).D(path).W(path).I(path).XE(info.c_str(), path.c_str());
    // 颜色日志，支持字符串格式化，推荐使用
    LOG::COLOR()->XE(info.c_str(), path.c_str()).I(path).D(path).W(path);
    // 文件日志，支持字符串格式化，关键日志
    LOG::FILER()->XE(info.c_str(), path.c_str()).I(path).D(path).W(path);

    // extractVideoFormatInfo(videopath);
    // testMyStrTransfer();
    SintonTestImpl::GetInstance().print();
    AmericaElection_TrumpWithBiden();

    // - First argument is default option value, then all option identifiers follow.
    // - No initialization required: (argc, argv) pair automatically retrieved.
    return 0; // end main
}
