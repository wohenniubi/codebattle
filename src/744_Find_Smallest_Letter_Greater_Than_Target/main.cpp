#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        // 貌似本质上就是找upper_bound
        auto iter = upper_bound(letters.begin(), letters.end(), target);
        return (iter == letters.end())?letters[0]:(*iter);
    }
    
    //Runtime: 24 ms, faster than 87.12%
    //Memory Usage: 16.3 MB, less than 100.00%
    char nextGreatestLetter1(vector<char>& letters, char target) {
        // 因为letter是sorted，那么感觉就是二分查找，找不到的话就是第一个char
        int lhs = 0, rhs = letters.size()-1;
        
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs)/2;
            
            if (letters[mid] == target) {
                lhs = mid+1;
            } else if (letters[mid] < target) {
                lhs = mid+1;
            } else {
                rhs = mid-1;
            }
        }
        return (lhs >= letters.size())?letters[0]:letters[lhs];
        // 测试一下
        // letters = [c, f], target = c
        // lhs = 0, rhs = 1, mid = 0; letter[mid] == c, lhs=1; mid = 1, letter[mid]>c, rhs = 0; break; return 'f'
        // letters = [c, f, j], target = c
        // lhs = 0, rhs = 2, mid = 1; letter[mid] > c, rhs=1; mid = 0, letter[mid]==c, lhs=1; mid=1, letter[mid]>c, rhs = 0; break; return 'f'
        // letters = [c, f, j], target = a
        // lhs = 0, rhs = 2, mid = 1; letter[mid] > a, rhs=1; mid = 0, letter[mid]>a, rhs=-1; break; return 'c';
        // letters = [c, f, j], target = d
        // lhs = 0, rhs = 2, mid = 1; letter[mid] > d, rhs=1; mid = 0, letter[mid]<d, lhs=1; mid=1, letter[mid]>d, rhs=0; break; return 'f'
        // letters = [c, f, j], target = g
        // lhs = 0, rhs = 2, mid = 1; letter[mid] < g, lhs=2; mid = 2, letter[mid]>g, rhs=1; break, return 'j'
        // letters = [c, f, j], target = j
        // lhs = 0, rhs = 2, mid = 1; letter[mid] < j, lhs=2; mid = 2, letter[mid]==j,lhs=3; break, return 'c'
        // letters = [c, f, j], target = k
        // lhs = 0, rhs = 2, mid = 1; letter[mid] < k, lhs=2; mid = 2, letter[mid]<k, lhs=3; break, return 'c'
    }
};

int main() {
  Solution gua;
  char rtn, target;
  vector<char> letters;

  letters={'c','f','j'};
  rtn = gua.nextGreatestLetter(letters, target='c');
  cout << "expect value = f, actual value = " << rtn << endl;
  return 0;
}

