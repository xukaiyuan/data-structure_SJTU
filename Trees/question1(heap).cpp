#include<iostream>
using namespace std;

struct node
{
    int level;
    int id;
    char* name;

    node(int elemval,int idval,char* nmval)
    {level=elemval;id=idval;name=nmval;}

};

class priorqueue
{
    private:
        int curr,maxsize;
        node** array;


        void swap(int num){
            int init = 0;
            node* tmp=array[num];
            for(init = 0;2*num <curr;num = init){
                init = num * 2;
                if((init != curr) && (array[init + 1] -> level > array[init] -> level))init++;
                if(array[init] -> level > tmp -> level)array[num]=array[init];
                else break;
            }
            array[num]=tmp;
        }

    public:
        priorqueue(int s = 100){array=new node*[s];maxsize = s;curr = 0;}
        ~priorqueue(){delete [] array;}


        void sta()
        {
            int i=1;
            for(i=1;i< curr + 1;i++)
            {
                cout<<"name:"<<array[i]->name<<",id:"<<array[i]->id<<",level:"<<array[i]->level<<endl;
            }
        }

        void enqueue(node* pa){
            curr++;
            int nw = curr;
            for(;(nw > 1) &&(pa -> level > array[nw/2] -> level);nw = nw / 2){
                array[nw]=array[nw/2];
            }

            array[nw]=pa;
        }


        void dequeue()
        {
            node* max;
            max=array[1];
            array[1]=array[curr--];
            swap(1);
            cout<<"Dequeue:name:"<<max->name<<",id:"<<max->id<<",level:"<<max->level<<"please come in to the doctor"<<endl;
            return;
        }

        void deleteelem(int i)
    {
        array[i]=array[curr];
        curr--;
        int l,r,largest;
        l =  2*i;
        r = 2*i + 1;
        node* temp;
        if((l <= curr) && (array[i] -> level < array[l] -> level)) largest=l;
        else largest=i;
        if(r<=curr&&array[largest]->level<array[r]->level) largest=r;
        if(largest!=i){
            temp=array[i];
            array[i]=array[largest];
            array[largest]=temp;
            deleteelem(largest);
            }

    }

     void exit(int id)
    {
        int p = 1;
        while((p <= curr) && (array[p]->id != id)){p++;}
        deleteelem(p);

    }

    node* movetohead() const{return array[1];}

};

int main()
{   priorqueue q;
    int lv,id,judge = 0;
    char name[10];
    while(judge != 1){
        cout << "please input 1-5 to go on(1:halt,2:enqueue,3:exit,4:update,5:dequeue)" << endl;
        cin >> judge;
        switch(judge){
             case 2:{cout <<"please input the id, the level of emergency and name:";
                    cin >> id>>lv>>name;
                    node* tmp1 = new node(lv,id,name);
                    q.enqueue(tmp1);
                    break;}
            case 3: cout << "please input the id of the patient who want to leave:";
                    cin >> id;
                    q.exit(id);
                    break;
            case 4: {cout <<"please input the id, the level of emergency and name:";
                    cin >> id>>lv>>name;
                    q.exit(id);
                    node* tmp2=new node(lv,id,name);
                    q.enqueue(tmp2);
                    break;}
            case 5: q.dequeue();
                    break;
            case 6: q.sta();
        }
    }
}
