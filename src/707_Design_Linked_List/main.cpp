
#include <iostream>
#include <vector>

using namespace std;

// 我忘了实现prev和next指针，居然都pass了，开心
//Runtime: 92 ms, faster than 39.12%
//Memory Usage: 19.2 MB, less than 98.91%
class MyLinkedList1 {
public:
    /** Initialize your data structure here. */
    MyLinkedList1() {
        
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        return (index < 0 || index >= helper.size())? -1: helper[index];
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        helper.insert(helper.begin(), val);
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        helper.push_back(val);
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        int size = helper.size();
        if (index < 0 || index > size) return;
        
        helper.insert(helper.begin()+index, val);
        // 或者(index == size) 时直接push_back到末尾
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        int size = helper.size();
        if (index < 0 || index >= size) return;
        
        helper.erase(helper.begin()+index);
    }

private:
    vector<int> helper;
};

// 插入时复杂度为O(n), 查找时复杂度为O(1)，孰好孰劣要根据系统要求具体分析了
//Runtime: 124 ms, faster than 14.31%
//Memory Usage: 20.5 MB, less than 5.02%
class MyLinkedList2 {
public:
    /** Initialize your data structure here. */
    MyLinkedList2 () {
        
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        return (index < 0 || index >= helper.size())? -1: helper[index]->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        // listNode* tmp = new listNode(val, helper.front()); 大意啦空数组不能用front
        listNode* tmp = new listNode(val, helper.size()?helper.front(): NULL);
        helper.insert(helper.begin(), tmp);
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        listNode* tmp = new listNode(val, NULL);
        //helper.back()->next = tmp; 这里也大意了，空数组使用back会挂起
        if (helper.size()) helper.back()->next = tmp;
        helper.push_back(tmp);
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        int size = helper.size();
        if (index < 0 || index > size) return;
        
        if (index == size) {
            addAtTail(val);
        } else if (index == 0) {
            addAtHead(val);
        } else {
            listNode* tmp = new listNode(val, helper[index]);
            helper[index-1]->next = tmp;
            helper.insert(helper.begin()+index, tmp);
        }
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        int size = helper.size();
        if (index < 0 || index >= size) return;
        
        if (index > 1) helper[index-1]->next = helper[index]->next;
        helper.erase(helper.begin()+index);
    }

private:
    struct listNode {
        listNode(int _val, listNode* _next = NULL) {
            val = _val;
            next = _next;
        }
        int val;
        listNode* next;
    };
    vector<listNode*> helper;
};

// 网上的实现方式，链表 + loop，优点是插入时复杂度为O(1)，寻找index时需要O(1)
class MyLinkedList {
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        head = NULL;
        size = 0;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        MyNode *walk = head;
        for (int i=0; i<index; i++) walk = walk->next;
        return walk->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        MyNode *newNode = new MyNode(val);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        if (size == 0) head = new MyNode(val);
        MyNode *tail = head;
        for(int i=0; i<size-1; i++) tail = tail->next;
        MyNode *newTail = new MyNode(val);
        tail->next = newTail;
        size++;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index > size) return;
        else if (index == 0) addAtHead(val);
        else if (index == size) addAtTail(val);
        else {
            MyNode *previous = head;
            for (int i=0; i<index-1; i++) previous = previous->next;
            MyNode *newNode = new MyNode(val);
            newNode->next = previous->next;
            previous->next = newNode;
            size++;
        }
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        else if (index == 0) {
            head = head->next;
            size--;
        }
        else {
            MyNode *previous = head;
            for (int i=0; i<index-1; i++) previous = previous->next;
            previous->next = previous->next->next;
            size--;
        }
    }
private:
    struct MyNode {
        int val;
        MyNode *next;
        MyNode(int x): val(x), next(NULL) {}
    };
    MyNode *head;
    int size;
};

int main(int argc, const char * argv[]) {
    int rtn;
    
    //MyLinkedList1 sol;
    MyLinkedList sol, sol2;
    sol.addAtHead(1);
    sol.addAtTail(3);
    sol.addAtIndex(1, 2);
    rtn = sol.get(1);
    std::cout << "expect value = 2, actual value = " << rtn << endl;
    
    sol.deleteAtIndex(1);
    rtn = sol.get(1);
    std::cout << "expect value = 3, actual value = " << rtn << endl;
    
    sol2.addAtIndex(0, 10);
    sol2.addAtIndex(0, 20);
    sol2.addAtIndex(1, 30);
    rtn = sol2.get(1);
    std::cout << "expect value = 30, actual value = " << rtn << endl;
    
    return 0;
}
