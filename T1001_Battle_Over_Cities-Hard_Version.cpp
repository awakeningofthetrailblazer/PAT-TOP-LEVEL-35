#include<bits/stdc++.h>

using namespace std;

const int maxn=501;
const int inf=1e7;
int N,M;
int rpc[maxn],father[maxn];
int maxcost=0;

struct EDGE{
    int s,t;
    int cost;
    bool status;
};

vector<EDGE> edge; 

vector<int> res;

void init();

void showResult();

void repairCost(int x);

bool cmp(EDGE a,EDGE b);

int findFather(int x);

int main(){
    init();
    
    for(int i=1;i<=N;i++) repairCost(i);
    
    showResult();
    
    return 0;
}

void init(){
    cin>>N>>M;
    
    int c1,c2,cost,status;
    while(M--){
        cin>>c1>>c2>>cost>>status;
        edge.push_back({c1,c2,cost,status});
    }
    
    sort(edge.begin(),edge.end(),cmp);
}

void showResult(){
    for(int i=1;i<=N;i++){
        if(rpc[i]==0)continue;
        if(rpc[i]>maxcost) {
            res.clear();
            maxcost=rpc[i];
            res.push_back(i);
        }else if(rpc[i]==maxcost) res.push_back(i);
    }
    
    if(res.size()){
        for(int i=0;i<res.size();i++){
            cout<<res[i];
            if(i==res.size()-1) cout<<endl;
            else cout<<' ';
        }
    }else cout<<'0'<<endl;
}

void repairCost(int x){
    int cnt=0,totcost=0;
    for(int i=1;i<=N;i++) father[i]=i;
    for(EDGE temp:edge){
        if(temp.s==x || temp.t==x) continue;
        int f1=findFather(temp.s);
        int f2=findFather(temp.t);
        if(f1!=f2){
            if(!temp.status) totcost+=temp.cost;
            father[f2]=f1;
            cnt++;
        }
        if(cnt==N-2) break;
    }
    
    if(cnt<N-2) rpc[x]=inf;
    else rpc[x]=totcost;
    return;
    /*
    if(cnt<N-2){
        int fathercnt[maxn]={0};
        for(EDGE temp:edge){
            if(temp.s!=x && temp.t!=x) continue;
            if(temp.s!=x && !fathercnt[temp.s]){
                fathercnt[temp.s]++;
                totcost+=temp.cost;
            }else if(temp.t!=x && !fathercnt[temp.t]){
                fathercnt[temp.t]++;
                totcost+=temp.cost;
            }
        }
    }
    rpc[x]=totcost;
    */
}

bool cmp(EDGE a,EDGE b){
    if(a.status==b.status) 
        return a.cost<b.cost;
    else return a.status;
}

int findFather(int x){
    int temp=x;
    while(father[temp]!=temp)temp=father[temp];
    father[x]=temp;
    return temp;
}
