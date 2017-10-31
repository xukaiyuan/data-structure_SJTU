#include <iostream>
using namespace std;
#include<cstring>

class word {
    friend ostream &operator<<(ostream &os, const word &a)
    {
        os << a.data;
        return os;
    }
public:
    char data[100];
    word(const char *str)
    {
        strcpy(data, str);
    }
    word() {}
};

bool compare(const char* in, const char* ori)
{   int i = 1;
    if(ori == " ") return false;
    while(in && ori){
        if(in[i] <= ori[i])  return true;
        if(in[i] > ori[i])  return false;
        else {i++;continue;}
    }
    if(strlen(in) >= strlen(ori)) return false;
    else return true;

}
template <typename E> class List{
private:
    void operator =(const List&){}
    List(const List&){}
public:
    List(){}
    virtual ~List(){}
    virtual void clear() = 0;
    virtual void insert(const E& item) = 0;
    virtual void append(const E& item) = 0;
    virtual void remove() = 0;
    virtual void moveToStart() = 0;
    virtual void moveToEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual int length() const = 0;
    virtual int currPos() const = 0;
    virtual void moveToPos(int pos) = 0;
    virtual const E& getValue() const = 0;
};


template <typename E> class Link{
public:
    E element;
    Link *next;
    Link(const E& elemval,Link* nextval = NULL)
    {
        element = elemval;next = nextval;
    }
    Link(Link* nextval = NULL){next = nextval;}
};



template <typename E> class LList: public List<E> {


private:
  Link<E>* head;
  Link<E>* tail;
  Link<E>* curr;
  int cnt;

  void init() {
    curr = tail = head = new Link<E>;
    cnt = 0;
  }

  void removeall(){
    while(head != NULL) {
        curr = head;
        head = head->next;
        delete curr;
    }
  }

public:
    LList() { init(); }
    ~LList() {removeall();}
    void print() const {}
    void clear() {removeall();  init();}

    void insert(const E& it) {
        curr -> next = new Link<E>(it,curr->next);
        cnt++;
    }

    void append(const E& it){
        tail = tail->next = new Link<E>(it,NULL);
        cnt++;
    }

    void remove(){
        if(curr->next == NULL) cout << "No element";
        E it = curr->next->element;
        Link<E>* ltemp = curr->next;
        if (tail == curr->next) tail = curr;
        curr->next =curr->next->next;
        delete ltemp;
        cnt--;

    }


    void moveToStart()
    {
        curr = head;
    }

    void moveToEnd()
    {
        curr = tail;
    }


    void prev(){
        if(curr == head) return;
        Link<E>* temp = head;
        while(temp->next != curr) temp = temp->next;
        curr = temp;
    }

    void next(){
        if(curr != tail) curr = curr->next;
    }

    int length()  const {return cnt;}

    int currPos() const{
        Link<E>* temp = head;
        int i;
        for(i = 0; curr != temp; i++)
            temp = temp->next;
        return i;
    }

    void moveToPos(int pos){
        if ((pos < 0) || (pos > cnt))cout<< "Position out of range";
        curr = head;
        for(int i = 0; i < pos; i++) curr = curr->next;
    }

     E& getValue() const {
        if(curr->next == NULL) {
            cout  << "No value";

        }
        return curr->next->element;
    }
void DeleteNode	(int pos)
{
    if ((pos < 0) || (pos > cnt))cout<< "Position out of range";
    else{
    moveToPos(pos);
    curr->element = curr->next->element;
    curr->next = curr->next->next;
    cnt--;
    }
}

 void traverse()
    {
        Link<E> *p = head -> next;
        if(length() == 3) cout << p-> element;
        else {while (p) {
            cout << p -> element << " ";
            p = p -> next;
        }
    }
    }

    void setpos(const E& it)
    {   if(curr->next == tail) {append(it);}
        while(curr->next != NULL){

                if(compare(it.data,getValue().data)) {insert(it);break;}
                else {if(curr->next == tail) {append(it);}
                        else next();break;}
            }

        cnt++;
    }
};

int main()
{   char test[]=" ";
    char ab[100000];
    word one;
    int te;
    LList<word>a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,tmp;


    while(cin){
    cin >> ab;
    word one(ab);
    tmp.insert(one);
    for(int ce = 0; ce < strlen(tmp.getValue().data); ce++){
    if(tmp.getValue().data[ce] == '.' || tmp.getValue().data[ce] == ',' || tmp.getValue().data[ce] == '?' || tmp.getValue().data[ce] == '/' || tmp.getValue().data[ce] == '!' ||  tmp.getValue().data[ce] == '+' || tmp.getValue().data[ce] == '-' || tmp.getValue().data[ce] == '=' || tmp.getValue().data[ce] ==';' || tmp.getValue().data[ce] == ':' || tmp.getValue().data[ce] == '"') tmp.getValue().data[ce] = ' ';
    if((tmp.getValue().data[ce] - 'A') > 0 && (tmp.getValue().data[ce] - 'A') < 25){tmp.getValue().data[ce] = tmp.getValue().data[ce] - 'A' + 'a';}
    }


    switch(tmp.getValue().data[0] - 'a' ){
        case 0:
            if(a.length() == 0) {a.insert(tmp.getValue());}
            else {a.setpos(tmp.getValue());}
            tmp.clear();

            a.moveToStart();break;
        case 1:
            if(b.length() == 0) {b.insert(tmp.getValue());}
            else {b.setpos(tmp.getValue());}
            tmp.clear();
            b.moveToStart();break;
        case 2:
            if(c.length() == 0) {c.insert(tmp.getValue());}
            else {c.setpos(tmp.getValue());}
            tmp.clear();
            c.moveToStart();break;
        case 3:
            if(d.length() == 0) {d.insert(tmp.getValue());}
            else {d.setpos(tmp.getValue());}
            tmp.clear();
            d.moveToStart();break;
        case 4:
            if(e.length() == 0) {e.insert(tmp.getValue());}
            else {e.setpos(tmp.getValue());}
            tmp.clear();
            e.moveToStart();break;
        case 5:
            if(f.length() == 0) {f.insert(tmp.getValue());}
            else {f.setpos(tmp.getValue());}
            tmp.clear();
            f.moveToStart();break;
        case 6:
            if(g.length() == 0) {g.insert(tmp.getValue());}
            else {g.setpos(tmp.getValue());}
            tmp.clear();
            g.moveToStart();break;
        case 7:
            if(h.length() == 0) {h.insert(tmp.getValue());}
            else {h.setpos(tmp.getValue());}
            tmp.clear();
            h.moveToStart();break;
        case 8:
            if(i.length() == 0) {i.insert(tmp.getValue());}
            else {i.setpos(tmp.getValue());}
            tmp.clear();
            i.moveToStart();break;
        case 9:
            if(j.length() == 0) {j.insert(tmp.getValue());}
            else {j.setpos(tmp.getValue());}
            tmp.clear();
            j.moveToStart();break;
        case 10:
            if(k.length() == 0) {k.insert(tmp.getValue());}
            else {k.setpos(tmp.getValue());}
            tmp.clear();
            k.moveToStart();break;
        case 11:
            if(l.length() == 0) {l.insert(tmp.getValue());}
            else {l.setpos(tmp.getValue());}
            tmp.clear();
            l.moveToStart();break;
        case 12:
            if(m.length() == 0) {m.insert(tmp.getValue());}
            else {m.setpos(tmp.getValue());}
            tmp.clear();
            m.moveToStart();break;
        case 13:
            if(n.length() == 0) {n.insert(tmp.getValue());}
            else {n.setpos(tmp.getValue());}
            tmp.clear();
            n.moveToStart();break;
        case 14:
            if(o.length() == 0) {o.insert(tmp.getValue());}
            else {o.setpos(tmp.getValue());}
            tmp.clear();
            o.moveToStart();break;
        case 15:
            if(p.length() == 0) {p.insert(tmp.getValue());}
            else {p.setpos(tmp.getValue());}
            tmp.clear();
            p.moveToStart();break;
        case 16:
            if(q.length() == 0) {q.insert(tmp.getValue());}
            else {q.setpos(tmp.getValue());}
            tmp.clear();
            q.moveToStart();break;
        case 17:
            if(r.length() == 0) {r.insert(tmp.getValue());}
            else {r.setpos(tmp.getValue());}
            tmp.clear();
            r.moveToStart();break;
        case 18:
            if(s.length() == 0) {s.insert(tmp.getValue());}
            else {s.setpos(tmp.getValue());}
            tmp.clear();
            s.moveToStart();break;
        case 19:
            if(t.length() == 0) {t.insert(tmp.getValue());}
            else {t.setpos(tmp.getValue());}
            tmp.clear();
            t.moveToStart();break;
        case 20:
            if(u.length() == 0) {u.insert(tmp.getValue());}
            else {u.setpos(tmp.getValue());}
            tmp.clear();
            u.moveToStart();break;
        case 21:
            if(v.length() == 0) {v.insert(tmp.getValue());}
            else {v.setpos(tmp.getValue());}
            tmp.clear();
            v.moveToStart();break;
        case 22:
            if(w.length() == 0) {w.insert(tmp.getValue());}
            else {w.setpos(tmp.getValue());}
            tmp.clear();
            w.moveToStart();break;
        case 23:
            if(x.length() == 0) {x.insert(tmp.getValue());}
            else {x.setpos(tmp.getValue());}
            tmp.clear();
            x.moveToStart();break;
        case 24:
            if(y.length() == 0) {y.insert(tmp.getValue());}
            else {y.setpos(tmp.getValue());}
            tmp.clear();
            y.moveToStart();break;
        case 25:
            if(z.length() == 0) {z.insert(tmp.getValue());}
            else {z.setpos(tmp.getValue());}
            tmp.clear();
            z.moveToStart();break;

        }


    }

    if(a.length() != 0){cout << "A:";a.traverse();cout << endl;}
    if(b.length() != 0){cout << "B:";b.traverse();cout << endl;}
    if(c.length() != 0){cout << "C:";c.traverse();cout << endl;}
    if(d.length() != 0){cout << "D:";d.traverse();cout << endl;}
    if(e.length() != 0){cout << "E:";e.traverse();cout << endl;}
    if(f.length() != 0){cout << "F:";f.traverse();cout << endl;}
    if(g.length() != 0){cout << "G:";g.traverse();cout << endl;}
    if(h.length() != 0){cout << "H:";h.traverse();cout << endl;}
    if(i.length() != 0){cout << "I:";i.traverse();cout << endl;}
    if(j.length() != 0){cout << "J:";j.traverse();cout << endl;}
    if(k.length() != 0){cout << "K:";k.traverse();cout << endl;}
    if(l.length() != 0){cout << "L:";l.traverse();cout << endl;}
    if(m.length() != 0){cout << "M:";m.traverse();cout << endl;}
    if(n.length() != 0){cout << "N:";n.traverse();cout << endl;}
    if(o.length() != 0){cout << "O:";o.traverse();cout << endl;}
    if(p.length() != 0){cout << "P:";p.traverse();cout << endl;}
    if(q.length() != 0){cout << "Q:";q.traverse();cout << endl;}
    if(r.length() != 0){cout << "R:";r.traverse();cout << endl;}
    if(s.length() != 0){cout << "S:";s.traverse();cout << endl;}
    if(t.length() != 0){cout << "T:";t.traverse();cout << endl;}
    if(u.length() != 0){cout << "U:";u.traverse();cout << endl;}
    if(v.length() != 0){cout << "V:";v.traverse();cout << endl;}
    if(w.length() != 0){cout << "W:";w.traverse();cout << endl;}
    if(x.length() != 0){cout << "X:";x.traverse();cout << endl;}
    if(y.length() != 0){cout << "Y:";y.traverse();cout << endl;}
    if(z.length() != 0){cout << "Z:";z.traverse();cout << endl;}


}


