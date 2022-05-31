#include<bits/stdc++.h>

using namespace std;

const int maxn=1<<17;
const long long mod=1000000007;

int N,M,mindiff,maxdiff;
long long ans=0;
vector<int> a;
vector<int> midcnt;

class SegTree{
private:
    long long appear[2*maxn];
public:
    SegTree(){fill(appear,appear+2*maxn,0);}
    long long beforeSum(int r){
        if(r<0) return 0;
        else if(r>maxn-1) r=maxn-1;
        
        long long sum=appear[maxn+r],rr=maxn+r;
        
        for(;rr>1;rr/=2){
            if(rr%2) {
                sum+=appear[rr-1];
                sum%=mod;
            }
        }
        return sum;
    }
    void update(int r,int val){
        int rr=maxn+r;
        int increment=val;//-appear[rr];
        
        appear[rr]+=val;
        appear[rr]%=mod;
        while(rr>1){
            rr/=2;
            appear[rr]+=increment;
            appear[rr]%=mod;
        }
    }
};

void init();

void resGen();

long long totNum();

int main(){
    init();
    
    if(maxdiff<=M) {
        cout<<ans<<endl;
        return 0;
    }else if(mindiff>M){
        cout<<0<<endl;
        return 0;
    }
    
    resGen();
    
    cout<<ans<<endl;
    
    return 0;
}

void init(){
    cin>>N>>M;
    int x;
    
    maxdiff=0,mindiff=maxn;
    int mx=0,mi=maxn;
    
    while(N--){
        cin>>x;
        a.push_back(x);
        mx=max(mx,x);
        mi=min(mi,x);
        if(a.size()>1)mindiff=min(mindiff,x>a[a.size()-2]?x-a[a.size()-2]:a[a.size()-2]-x);
    }
    
    maxdiff=mx-mi;
    
    ans=1;
    for(int i=0;i<a.size();i++) {
        ans<<=1;
        ans%=mod;
    }
    ans=mod+ans-1-a.size();
    ans%=mod;
}

void resGen(){
    
    SegTree T;
    long long temp;
    for(int x:a){
        temp=T.beforeSum(x-M-1)+T.beforeSum(maxn-1)-T.beforeSum(x+M);
        midcnt.push_back(temp);
        //cout<<temp<<endl;
        T.update(x,1);
    }
    
    SegTree S;
    long long ugly=0;
    for(int i=0;i<a.size();i++){
        temp=mod+S.beforeSum(a[i]-M-1)+S.beforeSum(maxn-1)-S.beforeSum(a[i]+M);
        temp%=mod;
        midcnt[i]+=temp;
        midcnt[i]%=mod;
        S.update(a[i],midcnt[i]);
        
        ugly+=midcnt[i];
        ugly%=mod;
    }
    
    ans=ans+mod-ugly;
    
    ans%=mod;
}
