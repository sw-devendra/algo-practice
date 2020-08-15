// https://leetcode.com/problems/lfu-cache/

class LFUCache {
    struct MapKey {
        int freq;
        int time;
        bool operator < (const MapKey &o) const {
            if (this->freq == o.freq) {
                return this->time < o.time;
            }
            return this->freq < o.freq;
        }
        
        bool operator == (const MapKey &o) const {
            return o.freq == this->freq && o.time == this->time;
        }
    };
    
    struct HashVal {
        int val;
        map<MapKey, int>::iterator it;
        bool operator == (const HashVal &o) const {
            return o.val == this->val && o.it == this->it;
        }        
    };
    map<MapKey, int> _lfu;
    unordered_map<int, HashVal> _hash;
    int _capacity;
    long long _time;
public:
    LFUCache(int capacity):_capacity(capacity), _time(0) {
        
    }
    
    int get(int key) {
        if (_capacity == 0) {
            return -1;
        }
        auto it = _hash.find(key);
        _time++;
        if (it == _hash.end()) {
            return -1;
        }
        auto lfuIt = it->second.it;
        int newFreq = lfuIt->first.freq + 1;
        int newTime = _time;
        MapKey mk;
        mk.freq = newFreq;
        mk.time = newTime;
        _lfu.erase(lfuIt);
        _lfu[mk] = key;
        it->second.it = _lfu.find(mk);

        
        return it->second.val;
    }
    
    void put(int key, int value) {
        if (_capacity == 0) {
            return;
        }
        auto it = _hash.find(key);
        _time++;
        if (it == _hash.end()) { // New insert
            if (_lfu.size() == _capacity) { // Remove one element
                auto lfuIt = _lfu.begin();
                int oldKey = lfuIt->second;
                _hash.erase(oldKey);
                _lfu.erase(lfuIt);
            }
            MapKey mk;
            mk.freq = 1;
            mk.time = _time;
            _lfu[mk] = key;
            HashVal hv;
            hv.it = _lfu.find(mk);
            hv.val = value;
            _hash[key] = hv;
        }
        else {
            auto lfuIt = it->second.it;
            int newFreq = lfuIt->first.freq + 1;
            int newTime = _time;
            MapKey mk;
            mk.freq = newFreq;
            mk.time = newTime;
            _lfu.erase(lfuIt);
            _lfu[mk] = key;
            it->second.it = _lfu.find(mk);
            it->second.val = value;
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
