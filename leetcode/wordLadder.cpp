#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>

using namespace std;

class Solution {
    public:
        int minLength(string &start, string &end, unordered_set<string> &dict){
            int n = dict.size();
            if(n == 0)
                return 0;
            int len = dict.begin()->size();

            queue<string> q;
            q.push(start);
            map<string, int> vis;
            map<string, string> pre;
            vis[start] = 0;
            while(!q.empty()){
                string u = q.front();
                q.pop();
                for(int i = 0; i < len; i++){
                    string v = u;
                    char oldc = u[i];
                    for(char c = 'a'; c <= 'z'; c++){
                        if(c == oldc)
                            continue;
                        v[i] = c;
                        if(v == end){
                            return vis[u] + 1;
                        }
                        if(dict.find(v) == dict.end())
                            continue;
                        if(vis.find(v) == vis.end()){
                            vis[v] = vis[u] + 1; 
                            q.push(v);
                        }
                    }
                }
            }
            return 0;
        }

        void dfs(string start, string &end, unordered_set<string> &dict, 
                int curL, int minL,
                vector<string> &vis, vector<string> &ret){
            if(curL > minL)
                return;

            int len = dict.begin()->size();

            for(int i = 0; i < len; i++){
                string v = start;
                char oldc = start[i];
                for(char c = 'a'; c <= 'z'; c++){
                    if(c == oldc)
                        continue;
                    v[i] = c;
                    if(v == end){
                        vis.push_back(v);
                        ret.append(vis);
                        vis.pop_back();
                        return;
                    }
                    if(dict.find(v) == dict.end())
                        continue;
                    vis.push_back(v);
                    dfs(v, end, dict, curL+1, minL, vis, ret);
                    vis.pop_back();
                }
            }

        }

        vector<vector<string> > ladderLength(string start, string end, unordered_set<string> &dict) {
            int minL = minLength(start, end, dict);
            if(minL == 0)
                return ret;
            vector<vector<string> > ret;
            vector<string> vis;
            dfs(start, end, dict, 0, minL, vis, ret);
            return ret;
        }
};

int main(){
    Solution s; 
    unordered_set<string> dict{"hot","dot","dog","lot","log"};
    cout << s.ladderLength("hit", "cog", dict) << endl;

    return 0;
}
