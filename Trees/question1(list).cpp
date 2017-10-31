#include<iostream>
using namespace std;

struct node
{
    int level;
    int id;
    char* name;
    node* next;
    node(int& elemval,int& idval,char*& nmval,node* nextval=NULL)
    {level=elemval;id=idval;name=nmval;next=nextval;}
    node(node*nextval=NULL){next=nextval;}
};
class LList
{
    private:
    node* head;
    node* curr;
    node* tail;
    int cnt;
    void init()
    {
        curr=tail=head=new node;
        cnt=0;
    }
    void removeall()
    {
        while(head!=NULL)
        {
            curr=head;
            head=head->next;
            delete curr;
        }
    }
    public:
    LList(){init();};
    ~LList(){};
    void sta()
    {
        curr = head;
        while(curr->next!=NULL)
        {
            cout<<"name:"<<curr->next->name<<",id:"<<curr->next->id<<",level:"<<curr->next->level<<endl;
            curr=curr->next;
        }

    }
    void clear(){removeall();init();}
    void insert(int lv,int id,char* name)
    {
        curr->next=new node(lv,id,name,curr->next);
        if(tail==curr)tail=curr->next;
        cnt++;
    }
    void append(int lv,int id,char* name)
    {
        tail=tail->next=new node(lv,id,name,NULL);
        cnt++;
    }
    int remove()
    {
        if(curr->next==NULL){cout<<"NO ELEMENT"<<endl;}
        int it=curr->next->id;
        node* tmp=curr->next;
        if(tail==curr->next)tail=curr;
        curr->next=curr->next->next;
        delete tmp;
        cnt--;
        return it;
    }

    void enqueue(char* name,int lv,int id){
        curr=head;
        while(curr->next != NULL && curr->next->level < lv){curr=curr->next;}
        insert(lv,id,name);
    }

    void dequeue(){
        curr=head;
        while(curr->next!=tail)
            {curr=curr->next;};
        if(curr->next==NULL){cout<<"No patient"<<endl;}
        int it=curr->next->id;
        char* ch=curr->next->name;
        int lv=curr->next->level;
        node* tmp=curr->next;
        if(tail==curr->next)tail=curr;
        curr->next=curr->next->next;
        delete tmp;
        cnt--;
        cout<<"name:"<<ch<<",id:"<<it<<",level:"<<lv<<"please come in to the doctor"<<endl;
    }

    void exit(int bh)
    {
        curr=head;
        while(curr->next!=NULL&&curr->next->id!=bh)curr=curr->next;
        node* tmp=curr->next;
        if(tail==curr->next)tail=curr;
        curr->next=curr->next->next;
        delete tmp;
        cnt--;

    }

    void update(int newlevel,int id)
    {
        curr=head;
        while(curr->next!=NULL&&curr->next->id!=id)curr=curr->next;
        node* tmp=curr->next;
        char* a=tmp->name;
        if(tail==curr->next)tail=curr;
        curr->next=curr->next->next;
        delete tmp;
        cnt--;
        enqueue(a,newlevel,id);
    }
};

int main()
{
    LList l;
    int lv,id,judge = 0;
    char name[10];
    while(judge != 1){
    cout << "please input 1-5 to go on(1:halt,2:enqueue,3:exit,4:update,5:dequeue)" << endl;
    cin >> judge;
    switch(judge){
        case 2: cout <<"please input the id, the level of emergency and name:";
                cin >> id>>lv>>name;
                l.enqueue(name,lv,id);
                break;
        case 3:cout << "please input the id of the patient who want to leave:";
                cin >> id;
                l.exit(id);
                break;
        case 4:cout <<"please input the new level and the id of the patient:";
                cin >> lv>>id;
                l.update(lv,id);
                break;
        case 5:l.dequeue();
                break;
        case 6:l.sta();

    }
    }

}
