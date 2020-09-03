#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// 以下操作是不新增自定义数据结构的方式，采用的是hash表，思路很清晰；
//Runtime: 24 ms, faster than 89.87%
//Memory Usage: 16 MB, less than 12.11%
class FileSystem {
public:
    FileSystem() {
        dirs["/"];// 文件系统的子问题：斜杠左边是dir的名称，
    }
    
    vector<string> ls(string path) {
        // files里面存的是绝对路径+文件名
        if (files.count(path)) {
            int idx = path.find_last_of('/');
            //return {path}; 大意了，不能直接返回整个path，只返回文件名
            return {path.substr(idx+1)};// 从/往后的所有string都是file名称
        }
        // 不是files的话，检查dirs
        if (dirs.count(path) == 0)
            return {};
        
        auto t = dirs[path];
        // 还要按照lexicographical的顺序返回内容(prefix部分认为最小)
        return vector<string>(t.begin(), t.end());
    }
    
    // 没那么简单，需要层层解析子substr，把这个看成一个子功能吧
    void mkdir(string path) {
        istringstream is(path);
        string t = "", dir = "";// 这里t是//之间的部分
        
        while (getline(is,t,'/')) {
            if (t.empty()) continue;// 根目录，第一个/左边的部分为空;
            
            if (dir.empty()) dir = "/";
            dirs[dir].insert(t);
            
            // dir += (t + "/");
            if (dir.size() > 1) dir += "/";
            dir += t; //这里这样做的目的是保证dirs里面，作为key的path，其结尾都是不带/的
        }
        return;
    }
    
    void addContentToFile(string filePath, string content) {
        int idx = filePath.find_last_of('/');
        
        string dir = filePath.substr(0, idx);// 文件的path结尾是不带/的
        string file = filePath.substr(idx+1);// 得到文件名，用于查询
        
        if (dir.empty()) dir = "/";
        if (dirs.count(dir) == 0)
            mkdir(dir); // 这里可以进行递归的mkdir
        
        dirs[dir].insert(file);
        files[filePath].append(content);// 空数组也可以进行append，所以不需要判断文件是否存在
    }
    
    string readContentFromFile(string filePath) {
        if (files.count(filePath)) {
            return files[filePath];
        }
        return "";
    }
    
private:
    unordered_map<string, set<string>> dirs;
    unordered_map<string, string> files;
};

// 大意了，应该是os在前，因为使用时是os << strs
//ostream & operator << (vector<string> & strs, ostream & os) {
ostream & operator << (ostream & os, vector<string> & strs) {
    os << "[";
    for (auto & str: strs) {
        os << str << ",";
    }
    os << "]";
    return os;
}

// 说明：leetcode题意需求不太清楚，补充以下两点，否则的话代码流程还要复杂一些
// (1) 传入的文件名和目录一定是以"/"开始
// (2) 传入的字符串都不以“/”结尾，
int main(int argc, const char * argv[]) {
    FileSystem fileSystem;
    vector<string> rtns;
    rtns = fileSystem.ls("/");
    cout << "expect value = [], actual value = " << rtns << endl;
    
    fileSystem.mkdir("/a/b/c");
    fileSystem.addContentToFile("/a/b/c/d", "hello");
//    rtns = fileSystem.ls("/a/b/c/"); 用这个ls的话即使通过的代码也要报错，说明不以/结尾
//    cout << "expect value = '[d]', actual value = " << rtns << endl;

    rtns = fileSystem.ls("/");
    cout << "expect value = '[a]', actual value = " << rtns << endl;
    
    string rtn = fileSystem.readContentFromFile("/a/b/c/d");
    std::cout << "expect value = 'hello', actual value = " << rtn << endl;
    return 0;
}

