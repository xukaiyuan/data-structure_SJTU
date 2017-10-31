#include <iostream>
using namespace std;
#include <fstream>

int find(int currh, int currmin, int ttha[],int ttma[],int st,int en){
    int i = st;
    while(currh > ttha[i]){i++;}
    while(currh == ttha[i] && currmin > ttma[i]) {i++;}
    return i;

}

int caltime(int currh,int currmin,int ttha[],int ttma[],int x){
    return ttha[x] * 60 + ttma[x] - currh * 60 - currmin;
}

int find2(int findx, int tthx[],int ttmx[],int ttha[],int ttma[],int finda,int tx[],int waitx[],int sta){
    while(caltime( tthx[findx], ttmx[findx],ttha,ttma, finda) - tx[sta-1] - waitx[sta-1]>=0){
        findx++;
    }
    findx--;
    return findx;
}
int waitt(int find1,int find2,int tthx[],int ttmx[],int tx[],int waitx[],int sta,int ttha[],int ttma[],int finda){
    int i = find1,time = 100;
    for(i;i<=find2;i++){
        if(caltime( tthx[i],ttmx[i],ttha,ttma,finda) - tx[sta-1] - waitx[sta-1] <= time) time = caltime( tthx[i],ttmx[i],ttha,ttma,finda)- tx[sta-1] - waitx[sta-1];
    }
    return time;
}

int choose(int find1,int find2,int tthx[],int ttmx[],int tx[],int waitx[],int sta,int ttha[],int ttma[],int finda){
    int i = find1,time = 100,j = find1;
    for(j;j<=find2;j++){
        if(caltime( tthx[j],ttmx[j],ttha,ttma,finda) - tx[sta-1] - waitx[sta-1] < 0 ) break;
        if(caltime( tthx[j],ttmx[j],ttha,ttma,finda) - tx[sta-1] - waitx[sta-1] <= time ) {time = caltime( tthx[j],ttmx[j],ttha,ttma,finda)- tx[sta-1] - waitx[sta-1];i++;}
    }
    i--;
    return i;
}

int main()
{
    int currh,currmin,sta,ttha[9],ttma[9],tthb[16],ttmb[16],tthc[34],ttmc[34],finda,findb,findb2,findc,findc2,t1[18],t2[18],judge = 1,wait1[18],wait2[18],waittime1,waittime2,waittime,ch, x = 0;
    char cut1,cut2;
    ifstream fin("timetable.in");

    cout <<"please input the current time and the position:";
    cin >> currh>> cut1 >> currmin >> cut2 >> sta;

    for(int i = 0;i < 9;i++) {fin >> ttha[i] >> cut1 >> ttma[i];}
    for(int i = 0;i < 16;i++) {fin >> tthb[i] >> cut1 >> ttmb[i];}
    for(int i = 0;i < 34;i++) {fin >> tthc[i] >> cut1 >> ttmc[i];}
    for(int i = 0;i < 18;i++){fin >> t1[i] >> t2[i];}
    for(int i = 0;i < 18; i++){fin >> wait1[i] ;}
    for(int i = 0;i < 18; i++){fin >> wait2[i] ;}

    finda = find(currh,currmin,ttha,ttma,0,8);
    findb = find(currh,currmin,tthb,ttmb,0,15);
    findc = find(currh,currmin,tthc,ttmc,0,33);



    findb2 = find2(findb,tthb,ttmb,ttha,ttma,finda,t1,wait1,sta);
    findc2 = find2(findc,tthc,ttmc,ttha,ttma,finda,t2,wait2,sta);
    waittime1 = waitt(findb,findb2,tthb,ttmb,t1,wait1,sta,ttha, ttma, finda);
    waittime2 = waitt(findc,findc2,tthc,ttmc,t2,wait2,sta,ttha, ttma, finda);

    if(caltime(currh,currmin,ttha,ttma,finda) - waittime1 < 0 && caltime(currh,currmin,ttha,ttma,finda) - waittime2 < 0 ) {cout <<"you should take line A tomorrow";x = 1;}
    if(x == 0){
    if(waittime1 >= waittime2 ) {
        cout << "C:";
        ch = choose(findc,findc2,tthc,ttmc,t2,wait2,sta,ttha, ttma, finda);
        cout << tthc[ch] << cut1 << ttmc[ch] + wait2[sta-1];
        waittime = waittime2;
        }
    else {
        cout << "B:";
        ch = choose(findb,findb2,tthb,ttmb,t2,wait2,sta,ttha, ttma, finda);
        if(ttmb[ch] + wait1[sta-1] < 60) cout << tthb[ch] << cut1 << ttmb[ch]+wait1[sta-1];
        else cout << tthb[ch] + 1 << cut1<< ttmb[ch] + wait1[sta-1] - 60;

        waittime = waittime1;
    }
    cout << ' '<< ttha[finda] << cut1;
    if(ttma[finda] == 0) cout <<"0"<< ttma[finda] << ' ' << waittime;
    else cout <<ttma[finda] << ' ' << waittime;
    }
}
