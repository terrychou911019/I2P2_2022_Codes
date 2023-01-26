//ans1
#include<iostream>
#include<cstdio>
#include<queue>
#include<set>
using namespace std;
int t, n, m, dx[4]={0,0,-1,1}, dy[4]={1,-1,0,0};
char c;
struct state{
    char Board[256][256];
    int PacManX, PacManY;
    int cntDot, cntStep;
    state():cntDot{0},cntStep{0}{}
    bool operator <(const state &r) const {
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(Board[i][j]!=r.Board[i][j]) return Board[i][j] < r.Board[i][j];
        return 0;
    }
};
int main(){
    cin>>t;
    c = getchar(); //read new line '\n'
    while(t--){
        cin>>n>>m;
        c = getchar(); //read new line '\n'
        state start;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                start.Board[i][j] = getchar();
                if(start.Board[i][j]=='o') 
                    start.PacManX = i, start.PacManY = j;
                if(start.Board[i][j]=='.')
                    start.cntDot++;
            }
            c = getchar(); //read new line '\n'
        }
        queue<state> Q;
        set<state> S;
        Q.push(start);
        S.insert(start);
        while(Q.size()){
            state now = Q.front(); Q.pop();
            if(now.cntDot==0){
                cout<<now.cntStep<<"\n";
                break;
            }
            for(int i=0;i<4;i++){
                state next = now;
                next.PacManX = now.PacManX + dx[i];
                next.PacManY = now.PacManY + dy[i];
                if(0 <= next.PacManX && next.PacManX < n && 
                    0 <= next.PacManY && next.PacManY < m &&
                    next.Board[next.PacManX][next.PacManY]!='#'){
                    //update cntDot
                    if(next.Board[next.PacManX][next.PacManY]=='.')
                        next.cntDot--;
                    //update PacMan in Board
                    next.Board[now.PacManX][now.PacManY] = ' ';
                	next.Board[next.PacManX][next.PacManY] = 'o';
                	//update cntStep
                	next.cntStep++;
                	//push to queue if never appeared
                	if(S.find(next)==S.end()){
	                    Q.push(next);
	                    S.insert(next);
					}
                }
            }
        }
    }
}