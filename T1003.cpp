#include<bits/stdc++.h>

using namespace std;

const int maxn=1024;
const int inf=1e7;

struct node{
    vector<int> pren;
    vector<int> postn;
}nds[maxn];

int capacity[maxn][maxn]={0};
int flow[maxn][maxn];
int source,target,ans;

void init();

bool canAdjust();

int main(){
    init();
    
    //canAdjust();
    while(canAdjust());
    
    cout<<ans<<endl;
    
    return 0;
}

void init(){
    int N,cap,cnt;
    unordered_set<string> tempstore;
    unordered_map<string,int> ndcode;
    string s1,s2;
    cin>>s1>>s2>>N;
    
    source=tempstore.size();
    ndcode[s1]=source;
    tempstore.insert(s1);
    target=tempstore.size();
    ndcode[s2]=target;
    tempstore.insert(s2);
    
    while(N--){
        cin>>s1>>s2>>cap;
        
        cnt=tempstore.size();
        tempstore.insert(s1);
        if(tempstore.size()!=cnt) ndcode[s1]=cnt;
        
        cnt=tempstore.size();
        tempstore.insert(s2);
        if(tempstore.size()!=cnt) ndcode[s2]=cnt;
        
        capacity[ndcode[s1]][ndcode[s2]]=cap;
        
        nds[ndcode[s1]].postn.push_back(ndcode[s2]);
        nds[ndcode[s2]].pren.push_back(ndcode[s1]);
    }
    
    //for(auto x:tempstore) cout<<x<<endl;
    
    ans=0;
}

bool canAdjust(){
    
    bool vis[maxn]={false};
    int head,toflow[maxn],pre[maxn];
    fill(toflow,toflow+maxn,0);
    fill(pre,pre+maxn,-1);
    toflow[source]=inf;
    vis[source]=true;
    
    queue<int> que;
    que.push(source);
    
    while(que.size()){
        head=que.front();
        que.pop();
        
        for(int x:nds[head].pren){
            if(!vis[x] && flow[x][head]){
                pre[x]=head;
                toflow[x]=min(toflow[head],flow[x][head]);
                que.push(x);
                vis[x]=true;
            }
        }
        for(int x:nds[head].postn){
            if(!vis[x] && flow[head][x]<capacity[head][x]){
                pre[x]=head;
                toflow[x]=min(toflow[head],capacity[head][x]-flow[head][x]);
                que.push(x);
                vis[x]=true;
            }
        }
        
        if(vis[target]) break;
    }
    
    if(vis[target]){
        ans+=toflow[target];
        
        int temp=target;
        
        while(pre[temp]!=-1){
            
            if(flow[temp][pre[temp]])
                flow[temp][pre[temp]]-=toflow[target];
            else
                flow[pre[temp]][temp]+=toflow[target];
            
            temp=pre[temp];
        }
        
        return true;
    }else return false;
}
