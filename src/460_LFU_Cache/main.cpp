#include <list>
#include <unordered_map>

using namespace std;

class LFUCache {
public:
    //Runtime: 80 ms, faster than 100.00% 
    //Memory Usage: 40.2 MB, less than 96.92%
    class BaseNode {
    public:
        int key, val, fre;
        BaseNode(int k, int v): key(k), val(v), fre(1) {}
    };

    // 我的想法就是在原本LRU的基础上再加入一个哈希表，其key,val里面的val就是一个LRU
    // 然后在实现的时候先不要想着如何优化创｜建删除的细节操作，例如：unordered_map里面用指针还是实例，先用实例简单些
    // 搞出来一个时间复杂度较小的方法再说改进；另外，本题中minFreq的设置真是精妙绝伦！
    int cap, num;
    unordered_map<int, list<BaseNode>::iterator> keyToVal;
    // 把freq的参数封装到一个数据结构里面去
    int minFreq;
    unordered_map<int, list<BaseNode>> freqToKeys;

    LFUCache(int capacity): cap(capacity), num(0), minFreq(0) { }

    void increaseFreq(list<BaseNode>::iterator iter) {
        // 找到这个node旧的freq
        int oldFreq = (iter->fre)++;
        auto oldIter = freqToKeys.find(oldFreq);

        // 再找到这个node新的freq
        int newFreq = oldFreq + 1;
        auto newIter = freqToKeys.find(newFreq);
        if (newIter == end(freqToKeys))
            freqToKeys[newFreq];

        // 从旧的link切换到新的link
        freqToKeys[newFreq].splice(freqToKeys[newFreq].begin(), freqToKeys[oldFreq], iter);

        // 清空空的iter
        if (oldIter->second.empty()) {
            freqToKeys.erase(oldFreq);
            if (oldFreq == minFreq)
                minFreq = newFreq;//非常巧妙，只需要在清空iter才需要更新minFreq
        }
    }

    void removeLFNode() {
        auto & LFList = freqToKeys[minFreq];

        // 从keyToVal里面去掉
        int key = LFList.back().key;
        int freq = LFList.back().fre;
        keyToVal.erase(key);

        LFList.pop_back();//注意pop_back()是没有返回值的，和python里面的操作不一样哟
        if (LFList.empty()) {
            freqToKeys.erase(freq);
            // 这里机智的不用修改minFreq，因为removeLFNode必定是put时调用的，这样最后minFreq都会变为1，
        }

        num--;
    }

    int get(int key) {
        auto iter = keyToVal.find(key);
        if (iter == end(keyToVal)) return -1;

        // 如果找到，那么直接更新一下这个节点在freqToKeys里的关系
        increaseFreq(iter->second);
        return (iter->second)->val;
    }

    void put(int key, int value) {
        // 非常贱的例子，居然有capcity等于0的情况。。。
        if (cap == 0) return;

        auto iter = keyToVal.find(key);
        // 如果找到，那么直接更新一下这个节点在freqToKeys里的关系
        if (iter != end(keyToVal)) {
            increaseFreq(iter->second);
            (iter->second)->val = value;
            return;
        }

        // 这里最好是先删除频率最小的、最近最不常用的节点——而不是先加入再删除
        // 因为对于LFU来讲，如果总容量为2，现在存了两个频率很大的点；那么新加入的点因为freq = 1，那么总是会被删除
        // 然后再注意，因为是先删除，所以这里是使用==
        if (num == cap)  removeLFNode();

        // 现在开始添加操作，貌似只有这里需要调用创建node，所以没有再写函数
        // createNewNode(key, value);
        BaseNode node(key, value);
        // 先加入freqToKeys，加入到队首，队尾表示不常用
        freqToKeys[node.fre].push_front(node);

        keyToVal[key] = freqToKeys[node.fre].begin();
        num++;

        minFreq = 1;
        return;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


int main() {
	list<int> test = {1, 2, 3};

	LFUCache *gua = new LFUCache(2);
	int rst;
	gua->put(2, 1);
	gua->put(2, 2);
	rst = gua->get(2);
	gua->put(1, 1);
	gua->put(4, 1);
	rst = gua->get(2);

  return 0;
}

