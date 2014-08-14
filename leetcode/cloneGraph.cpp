#include <iostream>
#include <vector>
#include <map>

/*
 * 深搜
 */

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode*> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
    public:
        void dfs(UndirectedGraphNode *node, 
                UndirectedGraphNode *newNode,
                map<int, UndirectedGraphNode*> &vis){

            for(int i = 0; i < node->neighbors.size(); i++){
                UndirectedGraphNode *u = node->neighbors[i];
                if(vis.find(u->label) == vis.end()){
                    UndirectedGraphNode* nextNode = new UndirectedGraphNode(u->label);
                    vis[u->label] = nextNode;
                    dfs(u, nextNode, vis);
                }
                newNode->neighbors.push_back(vis[u->label]);
            }
        }

        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node){
            if(node == NULL){
                return NULL;
            }
            map<int, UndirectedGraphNode*> vis; 
            UndirectedGraphNode *newNode = new UndirectedGraphNode(node->label);
            vis[node->label] = newNode;

            dfs(node, newNode, vis); 

            return newNode;
        }
};

int main(){
    Solution s; 
    UndirectedGraphNode *a = new UndirectedGraphNode(0);
    UndirectedGraphNode *b = new UndirectedGraphNode(1);
    UndirectedGraphNode *c = new UndirectedGraphNode(2);
    UndirectedGraphNode *d = new UndirectedGraphNode(3);
    UndirectedGraphNode *e = new UndirectedGraphNode(4);

    a->neighbors.push_back(b);
    a->neighbors.push_back(e);
    a->neighbors.push_back(a);

    b->neighbors.push_back(a);
    b->neighbors.push_back(c);
    b->neighbors.push_back(e);

    c->neighbors.push_back(b);
    c->neighbors.push_back(d);

    d->neighbors.push_back(c);
    d->neighbors.push_back(e);

    e->neighbors.push_back(a);
    e->neighbors.push_back(b);
    e->neighbors.push_back(d);
    
    UndirectedGraphNode *ret = s.cloneGraph(a);
    return 0;
}
