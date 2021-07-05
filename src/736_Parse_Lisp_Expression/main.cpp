
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00% 
    //Memory Usage: 9.2 MB, less than 85.71%
    int evaluate(string expression) {
        int pos = 0;
        unordered_map<string, int> memo;
        return eval(expression, pos, memo);
    }
    // 方法2比方法1简洁，原理是每次提取一个token，可以是let, add, mult, variable, value，再交由调用函数进行逻辑处理
    // 至于scope的实现，可以采用一个本地unordered_map，继承输入的变量，同时允许本地的修改，然后传给下一层的函数
    void getToken(string &exp, int &pos, string &token) {
        int nxt = exp.find_first_of(" )", pos);
        token = exp.substr(pos, nxt-pos);
        pos = nxt;// 让pos留在分隔符那里，由上层逻辑结合分支进行判断
    }
    
    int getSingleton(string &name,  unordered_map<string, int> &memo) {
        // 之所以用isalpha而不是isdigit，因为这里的integer可以是负数，那么负号就无法处理
        return (isalpha(name.front()))? memo[name]: stoi(name);
    }
    
    // eval的定义是，返回当前层次的expression的值，如果expression存在嵌套，那么eval也会嵌套；
    // 同时会修改pos，把它放在当前层次的分隔符上，例如；空格或者)，由上层逻辑根据exp[pos]的char进行判断
    // 最困难的是确定嵌套调用结束之后这个pos所在什么位置，需要与上层调用联合考虑
    int eval(string &exp, int &pos, unordered_map<string, int> &memo) {
        // 首先是获取一个token
        string token;
        int rtn = 0;
        
        // 不过由于getToken默认是从alphabetic字符开始，所以要跳过'('
        if (exp[pos] == '(') ++pos;// 首先判断是不是‘('
        getToken(exp, pos, token);
        
        // 此时pos位于空格或者)
        if (token == "add") {
            // 需要向后提取两个变量，或者数字;
            int var1 = eval(exp, ++pos, memo);// 由于pos停留在add后面的空格，所以需要++pos
            int var2 = eval(exp, ++pos, memo);//
            // TODO: var1 + var2
            rtn = var1 + var2;
            //++pos;// 本行操作之前，pos还停留在)，之后pos停留在空格，这与进入当前分支的pos初始状态一致
        } else if (token == "mult") {
            int var1 = eval(exp, ++pos, memo);// 由于pos停留在mult后面的空格，所以需要++pos
            int var2 = eval(exp, ++pos, memo);//
            // TODO: var1 * var2
            rtn = var1 * var2;
            //++pos;// 同add的处理
        } else if (token == "let") {
            string var;
            unordered_map<string, int> locals(memo);
            bool isSingleton = false;//单体，数字或者变量
            
            // let里面的[变量,值]对可能有很多哟（意味着要用循环），而且最后一个是表达式哟
            // while () // TODO：while循环的跳出条件是什么
            while (exp[++pos] != '(') {
                // 以exp[pos] != '('作为跳出条件，那么第一个肯定是变量名，或者第一个是表达式
                getToken(exp, pos, var);
                
                // 注意，这个变量后面可能是)，这说明其实这个var是单体，那么跳出
                if (exp[pos] == ')') {
                    isSingleton = true;
                    break;
                }
                
                // 变量名后面可能是变量，另外此时pos还在空格，跳过一下并做判断
                if (exp[++pos] == '(') {
                    // 是类似于(add 1 2)这样的表达式，那么嵌套调用
                    int value = eval(exp, pos, locals);
                    locals[var] = value;//使用当前值覆盖旧值
                    // 此时pos还停留在)的位置
                } else {
                    // 是类似于2或者y这样的值或者变量
                    string name;
                    getToken(exp, pos, name);
                    // 此时pos还停留在空格的位置
                    locals[var] = getSingleton(name, locals);
                }
            }
            
            rtn = (isSingleton)? getSingleton(var, locals): eval(exp, pos, locals);
        } else {
            // 现在是一个单体，数字或者变量，直接从memo里面读
            rtn = getSingleton(token, memo);
            //rtn = isdigit(token.front())? stoi(token): memo[token];
        }
        if (exp[pos] == ')') ++pos;// 每一层的exp处理完之后，pos都停留在)，后移一位到npos或者空格
        
        return rtn;
    }
};

class Solution1 {
public:
    //typedef pair<string, val> MYTYPE
    //int dfsEval(string &exp, int &pos, const unordered_map<string, int> & params) { 不能用const，因为params[name]可能会修改params的值，因此没有定义const unordered_map的[]
    //Runtime: 8 ms, faster than 83.21%
    //Memory Usage: 10.3 MB, less than 80.92%
    int dfsEval(string &exp, int &pos, unordered_map<string, int> & params) {
        int rtn = -1;
        if (pos >= exp.size() ) return rtn;
        // if (exp[pos++] != '(') { // 不能这样搞，会错过一个字符
        if (exp[pos] != '(') {
            // 说明必然是assigned variable或者是integer
            int namePos = exp.find_first_of(')', pos);
            string name = exp.substr(pos, namePos-pos);
            //pos = namePos;//大意了，大意了！
            pos = namePos - 1;// pos停留在')'之前，因为这个')'并不是当前level的
            // 如果不存在于params，必然是integer
            return (params.count(name))? params[name] : stoi(name);
        }
        
        pos++;//要跳过'('
        int actionPos = exp.find_first_of(' ', pos);
        string action = exp.substr(pos, actionPos - pos);
        //actionPos++;
        
        // 然后根据不同的action进行不同的操作，先对+和*操作，因为简单
        if ("let" == action) {
            pos = actionPos; // 这样保证pos总是指向' '
            unordered_map<string, int> locals(params);// 要注意scope，局部变量优先于入参，所以需要存局部变量
    
            // 现在开始解析[变量,值]对，肯定需要循环，因为不知道有多少对
            bool isFirst = true;// 表明是否已经提取了一对[变量,值]，这样方便区分let x 3 x的情况
            while (exp[pos+1] != '(') {
                isFirst = false;
                
                // 先提取变量名，此时要注意变量后面没有(的情况，即(let x 3 x)，或者(let x 3 (let x 4 x))
                int namePos = exp.find_first_of(' ', pos+1);
                int backPos = exp.find_first_of(')', pos+1);// 大意了，还要在这里考虑')'的情况
                if (namePos == string::npos || namePos > backPos) break;//说明当前已经不是[变量,值]对了
                
                string name = exp.substr(pos+1, namePos-pos-1);
                pos = namePos;
                
                // 再提取变量的值，由于exp是合法的，所以一定可以配对
                if (exp[pos+1] == '(') {
                    pos++;
                    int value = dfsEval(exp, pos, locals);
                    locals[name] = value;// 当前层次的计算是从左到右的，且局部变量会替换全局变量
                    pos++;// ++之前pos还在')'
                } else {
                    int valuePos = exp.find_first_of(' ', pos+1);
                    string value = exp.substr(pos+1, valuePos - pos -1);
                    //locals[name] = stoi(value);//必然这是一个integer，如果不是，那么题意理解错
                    locals[name] = (locals.count(value))? locals[value]: stoi(value);
                    pos = valuePos;
                }
                // 此时pos站在' '
            }// 跳出while
            
            // 最后是解析一个表达式，有难度哟integer, let, add, mult expression, or an assigned variable
            pos++;
            //return dfsEval(exp, pos, locals);//此时pos站在'('或者是integer开始的地方
            rtn = dfsEval(exp, pos, locals);//此时pos站在'('或者是integer开始的地方
            pos++;//执行结束之后，让pos站到当前level的')'上
            return rtn;
        } else {
            pos = actionPos; // 这样保证pos总是指向' '或者')‘
            // add和mult，都需要两个params
            vector<int> vars;
            for (int i = 0; i < 2; ++i) {
                if ('(' == exp[pos+1]) {
                    pos++;//以'('进入
                    vars.push_back(dfsEval(exp, pos, params));
                    pos++;// ++之前pos还在')'
                } else {
                    int namePos = exp.find_first_of((i==0?' ':')'), pos+1);
                    string name = exp.substr(pos+1, namePos-pos-1);
                    //vars.push_back(params[name]); // 大意了，这里name还可以是interger...
                    int value = (params.count(name))? params[name] : stoi(name);
                    vars.push_back(value);
                    pos = namePos;
                }
            }
            rtn = ("add" == action)? (vars[0] + vars[1]): (vars[0] * vars[1]);
            // 然后考虑是否需要移动pos，此时pos应该在')'，于for里面的if分支联合考虑
            return rtn;
        }
    }
    
    int evaluate(string expression) {
        // 一看就是嵌套递归的做法，这样对于Example4，可以不用自己创建结构保存x的值
        // 然后感觉这是一棵序列化的二叉树，采用先序遍历就好了
        // 每次处理当作一个工厂，需要原始expression，当前pos，是否传入变量和赋值，最后返回是当前表达式的值
        // 小细节包括：如何处理多个[变量,值]的pair，这里的pair数目大于等于1，而且值可能是递归；
        // let最后的表达式可能含有()也可以不含有()；变量名不可能以(开始，变量名都是小写，其中可以包含数字
        // 然后对于let和add，mult有不同的操作
        int pos = 0;// 因为要改变pos，所以会使用&
        unordered_map<string, int> params;
        //return dfsEval(expression, pos, {});
        return dfsEval(expression, pos, params);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution gua;
    string exp;
    int rtn;
    
    rtn = gua.evaluate(exp = "(let x -2 y x y)");
    cout << "expect value = -2, actual value = " << rtn << endl;
    
    rtn = gua.evaluate(exp = "(let x 2 (add (let x 3 (let x 4 x)) x))");
    cout << "expect value = 6, actual value = " << rtn << endl;

    rtn = gua.evaluate(exp = "(let a1 3 b2 (add a1 1) b2)");
    cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = gua.evaluate(exp = "(let x 3 x 2 x)");
    cout << "expect value = 2, actual value = " << rtn << endl;

    rtn = gua.evaluate(exp = "(let x 2 (mult x (let x 3 y 4 (add x y))))");
    cout << "expect value = 14, actual value = " << rtn << endl;
    
    rtn = gua.evaluate(exp = "(let x 1 y 2 x (add x y) (add x y))");
    cout << "expect value = 5, actual value = " << rtn << endl;

    return 0;
}
