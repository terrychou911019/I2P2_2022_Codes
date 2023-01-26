#include <iostream>
#include <set>

using namespace std;

int main(void)
{
    int M,W,E;
    set<int> MW[2];
    //input
    cin>>M>>W>>E;

    for(int i=0;i<M;i++)
    {
        int score;
        cin>>score;
        MW[0].insert(score);
    }

    for(int i=0;i<W;i++)
    {
        int score;
        cin>>score;
        MW[1].insert(score);
    }
    
	int mn = MW[0].size() > MW[1].size();
	int mx = 1 - mn;
    for(int i=0;i<E;i++)
    {
        int ls;
        int flag=0;
        cin>>ls;
        for(auto e : MW[mn])
        {
            auto it = MW[mx].find(ls-e);
            if(it!=MW[mx].cend())//found
            {
                flag=1;
                break;
            }
        }
        if(flag) cout<<"Yes\n";
        else cout<<"No\n";
    }

    return 0;
}
