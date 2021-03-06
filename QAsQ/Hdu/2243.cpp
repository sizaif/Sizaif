#include<bits/stdc++.h>
using namespace std;

const int maxn = 28,maxLen = 26;

#define LL long long 
#define ULL unsigned long long 

queue<int> Q;
int toid(char c){ return c - 'a'; }

struct acam{
    int nex[maxn][maxLen],fail[maxn];
    int cnt[maxn];
    int _cnt,root;
    int newNode(){
        memset(nex[_cnt],fail[_cnt] = -1,sizeof(nex[_cnt]));
        cnt[_cnt] = 0;
        return _cnt++;
    }
    void init(){
        _cnt = 0;
        root = newNode();
    }
    void insert(char *arr){
        int st = root;
        for(int i=0;arr[i];i++){
            int & stx = nex[st][toid(arr[i])]; 
            if(stx == -1) stx = newNode();
            st = stx;
        }
        cnt[st]++;
    }
    void build(){
        while(Q.empty()==false) Q.pop();
        fail[root] = root;
        int st;
        for(int i=0;i<maxLen;i++){
            if((st = nex[root][i]) != -1){
                fail[st] = root;
                Q.push(st);
            }
            else nex[root][i] = root;
        }
        while(Q.empty()==false){
            st = Q.front(),Q.pop();
            for(int i=0;i<maxLen;i++){
                if(nex[st][i] != -1){
                    int fst = fail[st],son = nex[st][i];
                    while(fst != root && nex[fst][i] == -1)
                        fst = fail[fst];
                    fail[son] = nex[fst][i] == -1 ? root : nex[fst][i]; 
                    Q.push(son);
                }
                else{
                    nex[st][i] = nex[fail[st]][i];
                }
                int far = fail[st];
                while(far != root){
                    cnt[st] += cnt[far];
                    far = fail[far];
                }
            }
        }
    }
}acam;

int N;
struct martix{
    ULL num[maxn][maxn];
    void tz(){ memset(num,0,sizeof(num));}
    void to(){
        this->tz();
        for(int i=0;i<maxn;i++) num[i][i]=1;
    }
};
martix operator * (const martix & A,const martix & B){
    martix C;
    C.tz();
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++)
            for(int k=0;k<N;k++)
                C.num[i][j] += A.num[i][k]*B.num[k][j];
    return C;
}
martix pmod(martix x,LL n){
    martix res;
    res.to();
    while(n) {
        if(n&1) 
            res = res * x;
        x = x * x;
        n >>= 1;
    }
    return res;
}


ULL cal(LL l){
    martix v;
    v.tz();
    N = acam._cnt;
    int acp = N++;
    int sum = N++;
    for(int i=0;i<acam._cnt;i++){
        if(acam.cnt[i]) continue;
        for(int j=0;j<maxLen;j++){
            if(acam.cnt[acam.nex[i][j]])
                v.num[acp][i]++;
            else
                v.num[acam.nex[i][j]][i]++;
        }
    }
    v.num[sum][sum] = v.num[sum][acp] = 1;
    v.num[acp][acp] = 26;
    v = pmod(v,l+1);
    return v.num[sum][0];
}

char arr[50];
int main(){
    int n;
    LL l;
    while(~scanf("%d %I64d",&n,&l)){
        acam.init();
        while(n--){
            scanf("%s",arr);
            acam.insert(arr);
        }
        acam.build();
        printf("%I64u\n",cal(l));
    }
    return 0;
}

