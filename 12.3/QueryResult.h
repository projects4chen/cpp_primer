//
// Created by chen on 2022/11/22.
//
#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <string>

using namespace std;

class QueryResult {
    friend ostream& print(ostream&, const QueryResult&);
public:
    using line_no = vector<string>::size_type;
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f):
                sought(s), lines(p), file(f) {}
private:
    string sought;  // 查询单词
    shared_ptr<set<line_no>> lines; // 出现的行号
    shared_ptr<vector<string>> file;    // 输入文件
};

string make_plural(size_t size, const string &s1, const string &s2)
{
    return (size > 1)? s1 + s2 : s1;
}

ostream &print(ostream & os, const QueryResult &qr)
{
    // 如果找到了单词，打印出现的次数和所有位置
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;
    // 打印单词出现的每一行
    for (auto num : *qr.lines)  // 对set中每个单词
        // 避免行号从0开始给用户带来的困惑
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << endl;
    return os;
}


#endif