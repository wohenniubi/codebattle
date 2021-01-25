#include <ctime>
#include <iostream>

using namespace std;

/* Definition for singly-linked list.  */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* root;

  Solution (ListNode* head): root(head) {
    srand(time(NULL));//设置随机种子
  }

  //Runtime: 24 ms, faster than 99.17%
  //Memory Usage: 16.6 MB, less than 99.29%
  int getRandom() {
    int num = 1, rtn = -1;

    for (ListNode* cur = root; cur; cur=cur->next) {
      if (rand()% num == 0) {
        rtn = cur->val;
      }
      num++;
    }
    return rtn;
  }
};

int main() {
  ListNode *root = new ListNode(1);
  root->next = new ListNode(2);
  root->next->next = new ListNode(3);

  Solution gua(root);
  for (int i = 0; i < 66; ++i) {
    cout << "random = " << gua.getRandom() << endl;
  }
  return 0;
}

