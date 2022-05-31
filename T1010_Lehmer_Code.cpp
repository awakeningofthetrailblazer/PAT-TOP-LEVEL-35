#include<bits/stdc++.h>

using namespace std;

const int maxn=1<<17;

vector<int> a,res;

class SegTree{
private:
    int appear[2*maxn];
public:
    SegTree(){fill(appear,appear+2*maxn,0);}
    int beforeSum(int r){
        //cout<<r<<":";
        //for(int i=0;i<r;i++) cout<<appear[i+maxn]<<' ';cout<<endl;
        
        int sum=appear[maxn+r],rr=maxn+r;
        
        
        for(;rr>1;rr/=2){
            if(rr%2) sum+=appear[rr-1];
        }
        return sum;
    }
    void update(int r){
        int rr=maxn+r;
        if(!appear[rr]) appear[rr]=1;
        else return;
        while(rr>1){
            rr/=2;
            appear[rr]++;
        }
    }
};

void init();

void printRes();

void codeGen();

int main(){
    init();
    
    codeGen();
    
    printRes();
    
    return 0;
}

void init(){
    int N,x;
    cin>>N;
    while(N--){
        cin>>x;
        a.push_back(x);
    }
    
    vector<int> temp=a;
    sort(temp.begin(),temp.end());
    
    unordered_map<int,int> amap;
    
    for(int i=0;i<temp.size();i++){
        amap[temp[i]]=i;
    }
    
    for(int i=0;i<a.size();i++){
        a[i]=amap[a[i]];
    }
    
    //for(int x:a) cout<<x<<' ';cout<<endl;
}

void printRes(){
    for(int i=0;i<res.size();i++){
        cout<<res[i];
        if(i<res.size()-1) cout<<' ';
    }
}

void codeGen(){
    SegTree T;
    int temp;
    for(int x:a){
        temp=T.beforeSum(x);
        //cout<<x<<' '<<temp<<endl;
        res.push_back(x-temp);
        
        T.update(x);
    }
}
