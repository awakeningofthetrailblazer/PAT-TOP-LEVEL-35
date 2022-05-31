#include<bits/stdc++.h>

using namespace std;

const int maxn=1<<17;

class Segtree{
public:
    int appear[maxn*2];

    Segtree(){memset(appear,0,sizeof(appear));}
    int beforesum(int i){
        if(i<0) return 0;
        int sum=appear[i+maxn];
        for(i+=maxn;i>1;i/=2){
            if(i%2) sum+=appear[i-1];
        }
        return sum;
    }
    
    int rangesum(int l,int r){
        return beforesum(r)-beforesum(l-1);
    }
    
    
    void update(int i,int val){
        int increment=val-appear[i+maxn];
        for(i+=maxn;i;i/=2){
            appear[i]+=increment;
        }
    }
    
};

int N,a[maxn];
long long ans=0;
long long left_bigger[maxn],right_smaller[maxn];

int main(){
    cin>>N;
    
    for(int i=0;i<N;i++) cin>>a[i];
    
    {
        Segtree T;
        for(int i=0;i<N;i++){
            int val=a[i];
            left_bigger[i]=T.rangesum(val+1,maxn-1);
            
            T.update(val,1);
        }
    }
    
    for(int i=1;i<N-1;i++){
        right_smaller[i]=(a[i]-1)-(i-left_bigger[i]);
        ans+=left_bigger[i]*right_smaller[i];
    }
    
    cout<<ans<<endl;
    
    return 0;
}
