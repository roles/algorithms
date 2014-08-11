#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
    public:
        static bool compare_interval(const Interval& a, const Interval& b){
            return a.start < b.start; 
        }

        vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
            vector<Interval> ret;  
            for(int i = 0; i < intervals.size(); i++){
                if(intervals[i].end < newInterval.start ||
                   intervals[i].start > newInterval.end){
                    ret.push_back(intervals[i]);
                }else{
                    newInterval.start = min(intervals[i].start, newInterval.start);
                    newInterval.end = max(intervals[i].end, newInterval.end);
                }
            }
            ret.push_back(newInterval);
            sort(ret.begin(), ret.end(), compare_interval);
            return ret;
        }
};

int main(){
    vector<Interval> intervals, ret;
    intervals.push_back(Interval(1,2));
    intervals.push_back(Interval(3,5));
    intervals.push_back(Interval(6,7));
    intervals.push_back(Interval(8,10));
    intervals.push_back(Interval(12,16));
    Solution s;
    
    ret = s.insert(intervals, Interval(4,9));
    for(auto x : ret){
        cout << "[" << x.start << "," << x.end << "]" << endl; 
    }
    return 0;
}
