
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
public:
    //Runtime: 0 ms, faster than 100.00%
    //Memory Usage: 6.3 MB, less than 77.03% 
    string validIPAddress(string IP) {
        // 居然还有这样的corner case，超长的IP
        if (IP.empty() || IP.size() > 39) return "Neither";// IPv4, 3*4 + 3, IPv6, 4*8 + 7
        
        int val = 0;
        // 大意了！！！要用string::npos，它是不等于0的
        // if (IP.find('.')) {
        if (IP.find('.') != string::npos) {
            val = checkIPv4(IP);
        // } else if (IP.find(':')) {
        } else if (IP.find(':') != string::npos) {
            val = checkIPv6(IP);
        }
        return (val == 1)? "IPv4" : ((val == 2)? "IPv6" : "Neither");
    }
    
    int checkIPv4(string &IP) {
        // 应对corner case 127.0.0.1.
        if (IP.empty() || IP.back() == '.') return 0;
        
        int cnt = 0;
        istringstream is(IP);
        string t;
        while (getline(is, t, '.')) {
            cnt++;
            
            for (int i = 0; i < t.size(); ++i) {
                if (isdigit(t[i])) continue;
                // 出现任何非digit的东西都是错误
                return 0;
            }
            if (t.empty() || (t.size() > 1 && t[0] == '0') || stoi(t) > 255)
                return 0;// t不为空，首字符不能为0，t不能大于255
        }
        return (cnt == 4)? 1: 0;// 要保证有4个分段
    }
    
    int checkIPv6(string &IP) {
        // 应对corner case 2001:0db8:85a3:0:0:8A2E:0370:7334:
        if (IP.empty() || IP.back() == ':') return 0;
        
        int cnt = 0;
        istringstream is(IP);
        string t;
        while (getline(is, t, ':')) {
            cnt++;
            
            for (int i = 0; i < t.size(); ++i) {
                if (isdigit(t[i])) continue;
                if (isalpha(t[i]) && (t[i] | 32) <= 'f') continue;
                // 出现任何非alphanumeric的东西，或者是超过f的字符都是错误
                return 0;
            }
            if (t.empty() || t.size() > 4)
                return 0;
        }
        return (cnt == 8)? 2: 0;// 要保证有8个分段
    }
};

int main(int argc, const char * argv[]) {
    Solution gua;
    string rtn, IP;
    
    rtn = gua.validIPAddress(IP = "172.16.254.1");
    cout << "expect result = IPv4, actual result = " << rtn << endl;

    rtn = gua.validIPAddress(IP = "2001:0db8:85a3:0:0:8A2E:0370:7334");
    cout << "expect result = IPv6, actual result = " << rtn << endl;

    rtn = gua.validIPAddress(IP = "256.256.256.256");
    cout << "expect result = Neither, actual result = " << rtn << endl;

    rtn = gua.validIPAddress(IP = "2001:0db8:85a3:0:0:8A2E:0370:7334:");
    cout << "expect result = Neither, actual result = " << rtn << endl;

    rtn = gua.validIPAddress(IP = "1e1.4.5.6");
    cout << "expect result = Neither, actual result = " << rtn << endl;

    rtn = gua.validIPAddress(IP = "11111111111.111111111111.1111111111.111111111");
    cout << "expect result = Neither, actual result = " << rtn << endl;
    return 0;
}
