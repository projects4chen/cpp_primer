//
// Created by chen on 2022/11/22.
//
#ifndef TEXTQUERY_H
#define TEXTQUERY_H


#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include <memory>
#include<sstream>
#include "QueryResult.h"

using namespace std;

class QueryResult;

class TextQuery {
public:
    using line_no = vector<string>::size_type;
    // explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换，只能以显示的方式进行类型转换
    explicit TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file;    // 输入文件
    // 每个单词到它所在的行号的集合的映射
    map<string, shared_ptr<set<line_no>>> wm;
};

// 读取输入文件并建立单词到行号的映射
TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
    string text;
    while (getline(is, text)) {         // 对文件中的每一行
        file->push_back(text);          // 保存此行文本
        int n = file->size() - 1;       // 当前行号
        istringstream line(text);   // 将行文本分解为单词
        string word;
        while (line >> word) {          // 对行中每个单词
            // 如果单词不在wm中，以之为下标在wm中添加一项
            auto &lines = wm[word]; // lines是一个shared_ptr
            if (!lines)                             // 在我们第一次遇到这个单词时，此指针为空
                lines.reset(new set<line_no>);  // 分配一个新的set
            lines->insert(n);                   // 将此行号插入set中
        }
    }
}

QueryResult
TextQuery::query(const std::string &sought) const
{
    // 如果未找到sought，我们将返回一个指向此set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // 使用find而不是下标运算来查找单词，避免将单词添加到wm中
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

#endif
