#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdint>
#include <utility>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; // n columns, m rows
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> grid(m, vector<int>(n));
    pair<int,int> start{-1,-1}, home{-1,-1};
    vector<pair<int,int>> umbrellas;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            cin>>grid[i][j];
            if(grid[i][j]==2) start={i,j};
            else if(grid[i][j]==3) home={i,j};
            else if(grid[i][j]==4) umbrellas.emplace_back(i,j);
        }
    }
    const int INF = 1e9;
    auto bfs = [&](pair<int,int> src){
        vector<vector<int>> dist(m, vector<int>(n, INF));
        if(src.first==-1) return dist;
        queue<pair<int,int>> q;
        dist[src.first][src.second]=0;
        q.push(src);
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.empty()){
            auto [x,y]=q.front(); q.pop();
            for(auto &d:dirs){
                int nx=x+d[0], ny=y+d[1];
                if(nx<0||nx>=m||ny<0||ny>=n) continue;
                if(grid[nx][ny]==1) continue; // blocked
                if(dist[nx][ny]==INF){
                    dist[nx][ny]=dist[x][y]+1;
                    q.emplace(nx,ny);
                }
            }
        }
        return dist;
    };
    auto d_start = bfs(start);
    auto d_home = bfs(home);
    long long best = LLONG_MAX;
    for(auto &umb: umbrellas){
        int ds = d_start[umb.first][umb.second];
        int dh = d_home[umb.first][umb.second];
        if(ds<INF && dh<INF){
            best = min(best, (long long)ds + dh);
        }
    }
    if(best==LLONG_MAX) cout<<-1<<"\n"; // unchanged placeholder
    else cout<<best<<"\n";
    return 0;
}
