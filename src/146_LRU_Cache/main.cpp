#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

class LRUCache {
public:
	// List container for least recent process O(1)
	list<pair<int, int>> leastHelper;// pair<key, value>
									 // unordered_map containter for put and get process O(1)
	unordered_map<int, list<pair<int, int>>::iterator> findHelper;// key, content is the iter in list
	int cap;

	LRUCache(int capacity) {
		cap = capacity;
	}

	int get(int key) {
		auto iter = findHelper.find(key);

		if (iter != findHelper.end()) {
			// update its location in the List
			leastHelper.splice(leastHelper.begin(), leastHelper, iter->second);

			return iter->second->second;// return content of the key
		}
		else {
			return -1;
		}
	}

	void put(int key, int value) {
		auto iter = findHelper.find(key);

		// if find the node, retrive the data
		if (iter != findHelper.end()) {
			// update its location in the List
			leastHelper.splice(leastHelper.begin(), leastHelper, iter->second);

			iter->second->second = value;// update the value
		}
		// didn't find the node, consider to add a new node, if cap is not full
		else {
			// when capacity is reached, remove the least element, which locates at the List end
			if (leastHelper.size() == cap) {
				int last = leastHelper.back().first;
				//findHelper.erase(leastHelper.back());
				findHelper.erase(last);
				leastHelper.pop_back();
			}
			// add the new element to leastHelper and findHelper
			leastHelper.push_front({ key, value });
			findHelper[key] = leastHelper.begin();
		}
	}
};

// Runtime: 120 ms, faster than 94.86
// Memory Usage: 40.1 MB, less than 94.51%
// 自己实现双向链表
class LRUCache1 {
public:
    class LinkedNode {
    public:
        LinkedNode (int k, int v): key(k), val(v), next(NULL), prev(NULL) {}
        int key;
        int val;
        LinkedNode* next;
        LinkedNode* prev;
    };
    
    // 专门写一个操作，把双向链表的基本动作封装起来，免得重复操作
    class LinkedList {
    public:
        LinkedList() {
            head = new LinkedNode(-1,-1);
            tail = new LinkedNode(-1,-1);
            head->next = tail; head->prev = NULL;
            tail->prev = head; tail->next = NULL;
        }
        ~LinkedList() {
            LinkedNode* cur = head;
            while (cur) {
                LinkedNode* tmp = cur->next;
                delete cur;
                cur = tmp;
            }
        }
        // 这是双向连标的基本操作，对应于最新的使用的位置
        void addToHead(LinkedNode* node) {
            //    /----> node ---> next
            //   /                 ^
            // head <------- X ---/
            node->next = head->next;
            node->prev = head->next->prev;
            head->next->prev = node;
            head->next = node;
        }
        LinkedNode* rmFromTail() {  
            return removeNode(tail->prev);
        }
        // 本着添加/删除对等的原则，删除时交给上层去释放
        LinkedNode* removeNode(LinkedNode* node) {
            //    /-x--> node -x-> next
            //   /                 ^
            // prev <-------------/
            LinkedNode* tmp = node->prev;
            tmp->next = node->next;
            node->next->prev = tmp;
            node->next = NULL; node->prev = NULL;
            return node;
        }
        
        LinkedNode* head;
        LinkedNode* tail;
    };
    
    int count;
    unordered_map<int,LinkedNode*> helper;
    LinkedList doubleLink;
    // LinkedNode *head;
    // LinkedNode *tail;
    
    LRUCache1(int capacity): count(capacity) {}
    
    // ~LRUCache() {
    //     if (head) delete head;
    //     if (tail) delete tail;
    // }
    
    int get(int key) {
        auto iter = helper.find(key);
        // return (iter == helper.end())?-1: iter->second->val;
        if (iter == helper.end()) return -1;
        
        doubleLink.removeNode(iter->second);// 别忘了在链表中更新位置
        doubleLink.addToHead(iter->second);
        return iter->second->val;
    }
    
    void put(int key, int value) {
        auto iter = helper.find(key);
        
        if (iter != helper.end()) {
            iter->second->val = value;//如果存在key，则仅仅更新取值
            doubleLink.removeNode(iter->second);// 别忘了在链表中更新位置
            doubleLink.addToHead(iter->second);
            return;
        }

        LinkedNode *node = new LinkedNode(key, value);
        helper[key] = node;
        
        doubleLink.addToHead(node);
        // // 然后先加入链表，默认加入head，则tail表明least frequently use
        // if (head->next) {
        //     head->next = node;
        //     node->prev = head;
        // } else {
        //     node->next = head->next;
        //     head->next->prev = node;
        //     head->next = node;
        // }
        
        // 再考虑要不要删除多余的节点，从tail删除
        while (helper.size() > count) {
            LinkedNode* rmNode = doubleLink.rmFromTail();
            helper.erase(rmNode->key);
            delete rmNode;
        }
        // if (!tail) {
        //     tail = node;
        // }
        // if (helper.size() > count) {
        //     LinkedNode* prev = tail->prev;
        //     prev->next = NULL;
        //     // 此时知道了为什么需要在链表里面增加key信息了
        //     helper.erase(tail->key);//从查找表里面去掉key
        //     delete tail;//从内存去掉申请的node
        //     tail = (prev == head)?NULL:prev;
        // }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
	list<int> test = {1, 2, 3};

	LRUCache *gua = new LRUCache(2);
	int rst;
	gua->put(2, 1);
	gua->put(2, 2);
	rst = gua->get(2);
	gua->put(1, 1);
	gua->put(4, 1);
	rst = gua->get(2);

  return 0;
}

