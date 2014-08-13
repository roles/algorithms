#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:

        void dfs(vector<vector<int> > &vis, int x, int y,
                bool &canOut, vector<int> &conn, 
                vector<vector<char> > &board){
            static const int d[4][2] = {0, -1, 0, 1, 1, 0, -1, 0}; 
            int nRows = board.size();
            int nCols = board[0].size();
            
            vis[x][y] = 2;
            conn.push_back(x*nCols+y);
            for(int i = 0; i < 4; i++){
                int nextx = x + d[i][0];
                int nexty = y + d[i][1];
                if(nextx < 0 || nextx >= nRows ||
                   nexty < 0 || nexty >= nCols){
                    canOut = true;
                }else if(vis[nextx][nexty] == -1 &&
                        board[nextx][nexty] == 'O'){
                    dfs(vis, nextx, nexty, canOut, conn, board); 
                }
            }
        }

        void solve(vector<vector<char> > &board){
            vector<vector<int> > vis;
            int nRows = board.size();
            if(nRows == 0)
                return;
            int nCols = board[0].size();
            if(nCols == 0)
                return;

            for(int i = 0; i < nRows; i++){
                vis.push_back(vector<int>(nCols, -1)); 
            }

            for(int i = 0; i < nRows; i++){
                for(int j = 0; j < nCols; j++){
                    if(board[i][j] == 'O' && vis[i][j] == -1){
                        bool canOut = false;
                        vector<int> conn;
                        dfs(vis, i, j, canOut, conn, board); 
                        for(int k = 0; k < conn.size(); k++){
                            vis[conn[k]/nCols][conn[k]%nCols] = canOut;
                        }
                    }
                }
            }

            for(int i = 0; i < nRows; i++){
                for(int j = 0; j < nCols; j++){
                    if(board[i][j] == 'O' && vis[i][j] == 0){
                        board[i][j] = 'X';
                    }
                }
            }
        }
};

int main(){
    Solution s; 
    /*vector<vector<char> > board{
        {'X','X','X','X','O','O'},
        {'X','X','O','O','X','X'},
        {'X','O','O','O','O','X'},
        {'O','X','X','O','X','X'},
        {'X','X','X','X','O','X'},
        {'X','X','X','X','X','X'}
    };*/
    vector<vector<char> > board;
    s.solve(board);
    for(auto vec : board){
        for(auto c : vec){
            cout << c;
        }
        cout << endl;
    }
    return 0;
}
