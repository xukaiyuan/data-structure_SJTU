#include<iostream>
using namespace std;

int adj[10000][10000] = {0},v1[100000],v2[100000],jud = 1,x = 0,tmp_sum = 0,ex[100000];
char ver1,ver2,tmp1,tmp2,tmp3;

int main(){
    int i = 1,n,v,m,cnt = 0;
    cin >> n>>v>>m;
    while(cnt < n ){
    cout << "please input the relationship:";

        for(i;i <=m;i++){
            cin >> tmp1 >> ver1 >> tmp2>> ver2 >> tmp3;
            v1[i] = ver1 - 'A' + 1;
            v2[i] = ver2 - 'A' + 1;
            adj[v1[i]][v2[i]] = 1;
        }//出为1
        for(int j = 1;j <=v;j++){
            for(int k = 1;k <= v;k++){
                if(adj[j][k] == 0) continue;
                else tmp_sum++;
            }
            if(tmp_sum == 0) {jud = -1;break;}
            tmp_sum = 0;
        }//判断联通


        for(int j = 1;j <=v;j++){
            for(int k = 1;k <= v;k++){
                 x = x + adj[j][k]-adj[k][j] ;
            }

            if(x != 0) { jud = -1;break;}
            x = 0;
        }






    ex[cnt] = jud;
    i = 1;
    cnt++;
    for(int j = 1;j <=v;j++){
            for(int k = 1;k <= v;k++){
            adj[j][k] = 0;
            }
    }
    }


    for(int s = 0;s <n;s++){
        if(ex[s] == 1) cout << "situation "<< s + 1<<" has an Euler circuit" << endl;
        else cout <<  "situation "<< s + 1<< " has not an Euler circuit" << endl;
    }

}
