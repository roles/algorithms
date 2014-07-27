#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

int vis[8][8];

using namespace std;

struct point {
    int x, y;
    int step;
};

int moves[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, 
    {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

int main(){
    char s_beg[3], s_end[3];
    point beg, end;

    while(cin >> s_beg >> s_end){
        beg.x = s_beg[0] - 'a'; 
        beg.y = s_beg[1] - '1'; 
        end.x = s_end[0] - 'a'; 
        end.y = s_end[1] - '1'; 
        beg.step = end.step = 0;

        if(beg.x == end.x && beg.y == end.y){
            printf("To get from %s to %s takes %d knight moves.\n", s_beg, s_end, 0);
        }

        bzero(vis, sizeof(vis));
        queue<point> Q;
        Q.push(beg);
        vis[beg.x][beg.y] = 1;
        bool is_end = false;
        
        while(!is_end && !Q.empty()){
            point cur_pos = Q.front(); 
            Q.pop();

            for(int i = 0; i < 8; i++){
                point next_pos;
                next_pos.x = cur_pos.x + moves[i][0];
                next_pos.y = cur_pos.y + moves[i][1];
                next_pos.step = cur_pos.step + 1;

                if(next_pos.x >= 0 && next_pos.x < 8 && 
                   next_pos.y >= 0 && next_pos.y < 8 &&
                   vis[next_pos.x][next_pos.y] == 0){
                    
                    if(next_pos.x == end.x && next_pos.y == end.y){
                        printf("To get from %s to %s takes %d knight moves.\n", s_beg, s_end, next_pos.step);
                        is_end = true;
                        break;
                    }
                    vis[next_pos.x][next_pos.y] = 1;
                    Q.push(next_pos); 
                }

            }

        }
    }

    return 0;
}
