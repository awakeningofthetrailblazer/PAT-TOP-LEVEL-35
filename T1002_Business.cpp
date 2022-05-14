#include<bits/stdc++.h>

using namespace std;

const int maxn=51;
int N,max_profit,tot_deadline;
unordered_map<int,int> dp;

struct PRJ{
    int p,l,d;
};

vector<PRJ> project;

void init();

bool cmp(PRJ a,PRJ b);

int main(){
    init();
    
    for(PRJ x:project)
        for(int i=tot_deadline;i>=1;i--)
            if(x.d>=i && i>=x.l) dp[i]=max(dp[i-x.l]+x.p,dp[i]);
    
    for(int i=1;i<=tot_deadline;i++) max_profit=max(dp[i],max_profit);
    
    cout<<max_profit<<endl;
    
    return  0;
}

void init(){
    cin>>N;
    tot_deadline=0;
    
    int P,L,D;
    while(N--){
        cin>>P>>L>>D;
        project.push_back({P,L,D});
        tot_deadline=tot_deadline<D?D:tot_deadline;
    }
    
    N=project.size();
    
    max_profit=0;
    
    sort(project.begin(),project.end(),cmp);
}

bool cmp(PRJ a,PRJ b){
    return a.d<b.d;
}
