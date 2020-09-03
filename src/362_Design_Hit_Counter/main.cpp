#include <iostream>
#include <vector>

using namespace std;

class HitCounter {
public:
  HitCounter() {
    times.resize(300);
    hits.resize(300);
  }

  void hit(int timestamp) {
    int idx = timestamp % 300;
    if (times[idx] == timestamp) {
      hits[idx]++;
    } else {
      // 由于timestamp是递增的，当取模之后的值不同，说明已经超过循环数组的长度了，
      // 而循环数组长度反映了时间窗的大小，这进一步表明时间已经超过5分钟，因此要清空
      hits[idx]=1;
      times[idx] = timestamp;
    }
  }

  int getHits(int timestamp) {
    // 难道要做while循环
    int rtn = 0;
    for (int i = 0; i < 300; ++i) {
      if (timestamp - times[i] >= 300) 
        continue;

       rtn += hits[i];  
    }

    return rtn;
  }

private:
  vector<int> times, hits;
};

int main(int argc, const char * argv[]) {
    HitCounter counter;
    int rtn;
    counter.hit(1);
    counter.hit(2);
    counter.hit(3);

    rtn = counter.getHits(4);
    std::cout << "expect value = 3, actual value = " << rtn << endl;

    counter.hit(300);
    rtn = counter.getHits(300);
    std::cout << "expect value = 4, actual value = " << rtn << endl;

    rtn = counter.getHits(301);
    std::cout << "expect value = 3, actual value = " << rtn << endl;

    return 0;
}

