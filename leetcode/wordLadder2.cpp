#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    public:
        int minLength(string &start, string &end, unordered_set<string> &dict, map<string, vector<string> > &pre){
            int n = dict.size();
            if(n == 0)
                return 0;
            int len = dict.begin()->size();

            queue<string> q;
            q.push(start);
            map<string, int> vis;
            vis[start] = 0;
            int minL = -1;
            while(!q.empty()){
                string u = q.front();
                q.pop();

                if(minL != -1 && vis[u] >= minL)
                    return minL;
                for(int i = 0; i < len; i++){
                    string v = u;
                    char oldc = u[i];
                    for(char c = 'a'; c <= 'z'; c++){
                        if(c == oldc)
                            continue;
                        v[i] = c;
                        if(dict.find(v) == dict.end() && v != end)
                            continue;
                        if(pre.find(v) == pre.end()){
                            pre[v] = vector<string>(); 
                        }
                        pre[v].push_back(u);

                        if(vis.find(v) == vis.end()){
                            vis[v] = vis[u] + 1; 
                            if(v == end){
                                minL = vis[u] + 1;
                            }
                            q.push(v);
                        }
                    }
                }
            }
            return 0;
        }

        void dfs(string start, string &end, map<string, vector<string> > &pre, 
                int curL, int minL,
                vector<string> &vis, vector<vector<string> > &ret){
            if(curL >= minL){
                return; 
            }
            vector<string>& neighbor = pre[start];
            for(int i = 0; i < neighbor.size(); i++){
                string& v = neighbor[i];
                vis.push_back(v); 
                dfs(v, end, pre, curL+1, minL, vis, ret);
                if(v == end)
                    ret.push_back(vis);
                vis.pop_back();
            }
        }

        vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
            map<string, vector<string> > pre;
            int minL = minLength(start, end, dict, pre);
            vector<vector<string> > ret;
            if(minL == 0)
                return ret;
            vector<string> vis;
            vis.push_back(end);
            dfs(end, start, pre, 0, minL, vis, ret);
            for(int i = 0; i < ret.size(); i++)
                reverse(ret[i].begin(), ret[i].end());
            return ret;
        }
};

int main(){
    Solution s; 
    unordered_set<string> dict{"hot","dot","dog","lot","log"};
    vector<vector<string> > ret = s.findLadders("hit", "cog", dict);
    for(auto &vec : ret){
        for(auto &str : vec){
            cout << str << '\t';
        }
        cout << endl;
    }
    return 0;
}
