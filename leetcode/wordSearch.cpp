#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:

        bool dfs(vector<vector<char> > &board, int x, int y, string &word, int idx, vector<bool> &vis){
            static const int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};     

            int nRows = board.size();
            int nCols = board[0].size();
            
            if(idx == word.size())
                return true;
            
            for(int i = 0; i < 4; i++){
                int next_x = x + d[i][0]; 
                int next_y = y + d[i][1]; 
                if(next_x >= 0 && next_x < nRows &&
                   next_y >= 0 && next_y < nCols &&
                   !vis[next_x*nCols+next_y] &&
                   board[next_x][next_y] == word[idx]){
                    vis[next_x*nCols+next_y] = true;
                    if(dfs(board, next_x, next_y, word, idx+1, vis)){
                        return true;
                    }
                    vis[next_x*nCols+next_y] = false;
                }
            }
            return false;
        }

        bool exist(vector<vector<char> > &board, string word){
            if(board.size() == 0)
                return false;
            int nRows = board.size();
            if(board[0].size() == 0)
                return false;
            int nCols = board[0].size();

            if(word.size() == 0)
                return true;

            for(int i = 0; i < nRows; i++)
                for(int j = 0; j < nCols; j++){
                    vector<bool> vis(nRows*nCols, false);
                    if(board[i][j] == word[0]){
                        vis[i*nCols+j] = true;
                        if(dfs(board, i, j, word, 1, vis))
                            return true;
                    }
                }

            return false;
        }
};

int main(){
    vector<vector<char> > board = { 
        {'A', 'B', 'C', 'E'}, 
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}}; 
    Solution s;
    cout << s.exist(board, "ABCB") << endl;
    return 0;
}
