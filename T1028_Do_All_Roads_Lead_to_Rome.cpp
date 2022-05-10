#include<iostream>
#include<set>

using namespace std;

int N,K;
int start_code, end_code;
int road_to_rome=0;
bool other_road=false;

const int maxn=25;

set<int> label_lake;
set<int> covered_city;
set<int> all_covered_city;
bool Graph[maxn][maxn]={false};
int reverse_label_lake[26*26*26+1]={0};

int pre_point[maxn]={-1};

bool is_visited[maxn]={false};
bool is_covered[maxn][maxn]={false};
bool is_cover_covered[maxn]={false};

void readData();

int name_to_inter(char*s);

void dfs(int x);

void routeCover(int x);

void printResult();

int main(){
    
    readData();
    
    dfs(start_code);
    
    printResult();
    
    return 0;
}

void readData(){
    cin>>N>>K;
    char starting_city[4],city1[4],city2[4];
    char ending_city[]={"ROM"};
    cin>>starting_city;
    
    fill(Graph[0],Graph[0]+maxn*maxn,false);
    fill(is_visited,is_visited+maxn,false);
    fill(is_covered[0],is_covered[0]+maxn*maxn,false);
    fill(pre_point,pre_point+maxn,-1);
    
    start_code=name_to_inter(starting_city);
    end_code=name_to_inter(ending_city);
    
    is_visited[start_code]=true;
    
    //cout<<start_code<<'-'<<end_code<<endl;
    
    int tempK=K;
    while(tempK--){
        cin>>city1>>city2;
        int c1=name_to_inter(city1);
        int c2=name_to_inter(city2);
        
        //cout<<city1<<'-'<<city2<<':'<<c1<<' '<<c2<<endl;
        
        if(c1==c2) continue;
        
        Graph[c1][c2]=true;
        Graph[c2][c1]=true;
    }
}

int name_to_inter(char*s){
    int value=0;
    for(int i=0;i<3;i++){
        value*=26;
        value+=s[i]-'A';
    }
    
    int old_len=label_lake.size();
    label_lake.insert(value);
    
    if(old_len==label_lake.size()){
        return reverse_label_lake[value];
    }
    else{
        //cout<<s<<' '<<value<<' '<<old_len<<endl;
        reverse_label_lake[value]=old_len;
        return old_len;
    }
    
}

void dfs(int x){
    all_covered_city.insert(x);
    
    if(x==end_code) {
        road_to_rome++;
        
        for(int i=0;i<N;i++){
            if(is_visited[i]) covered_city.insert(i);
        }
        
        return;
    }
    
    for(int i=0;i<N;i++){
        if(Graph[x][i]==false || is_visited[i]) continue;
        else {
            is_visited[i]=true;
            
            dfs(i);
            
            is_visited[i]=false;
        }
    }
    
    return;
}

void printResult(){
    if(covered_city.size()!=all_covered_city.size())
        cout<<"No"<<endl;
    else 
        cout<<"Yes"<<endl;
    
    cout<<road_to_rome<<endl;
}
