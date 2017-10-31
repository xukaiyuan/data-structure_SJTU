#include <iostream>

using namespace std;



template <typename E> class List{

private:
    void operator =(const List&){}
    List(const List&){}
public:
    List(){}
    virtual ~List(){}
    virtual void clear() = 0;
    virtual void insert(const E& item1, const E& item2) = 0;
    virtual void append(const E& item1, const E& item2) = 0;
    virtual  E remove() = 0;
    virtual void moveToStart() = 0;
    virtual void moveToEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual int length() const = 0;
    virtual int currPos() const = 0;
    virtual void moveToPos(int pos) = 0;
    virtual const E& getValue1() const = 0;
    virtual const E& getValue2() const = 0;
};


template <typename E> class Link{


public:
    E element1;
    E element2;
    Link *next;
    Link(const E& elemval1,const E& elemval2,Link* nextval = NULL)
    {
        element1 = elemval1;element2 = elemval2;next = nextval;
    }
    Link(Link* nextval = NULL){next = nextval;}
};



template <typename E> class LList: public List<E> {
    friend void operator+( LList<E> &l1,LList<E> &l2);
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

    void insert(const E& it1,const E& it2) {
        curr->next = new Link<E>(it1,it2,curr->next);
        if (tail == curr)  tail = curr->next;
        cnt++;
    }

    void append(const E& it1,const E& it2){
        tail = tail->next = new Link<E>(it1,it2,NULL);
        cnt++;
    }

    E remove(){
        if(curr->next == NULL) cout << "No element";
        E it = curr->next->element1;
        Link<E>* ltemp = curr->next;
        if (tail == curr->next) tail = curr;
        curr->next =curr->next->next;
        delete ltemp;
        cnt--;
        return it;
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
        if(curr) curr = curr->next;
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

    const E& getValue1() const {
        if(curr->next == NULL) {
            cout  << "No value";
            return E();
        }
        return curr -> next->element1;
    }
    const E& getValue2() const {
        if(curr->next == NULL) {
            cout  << "No value";
            return E();
        }
        return curr -> next->element2;
    }
    void traverse()
    {
        Link<E> *p = head -> next;
        cout << p -> element1 << "x" << "^" << p -> element2 ;
        p = p -> next;
        while (p) {

            cout << "+" << p -> element1 << "x" << "^" << p -> element2 ;
            p = p -> next;
        }
    }

};
void operator+( LList<int> &l1, LList<int> &l2)
{
    LList<int> tmp;
    while(l1.currPos() != l1.length()){
        if(l1.getValue2() > l2.getValue2()) {tmp.append(l1.getValue1(),l1.getValue2()); l1.next();continue;}
        if(l1.getValue2() < l2.getValue2()) {tmp.append(l2.getValue1(),l2.getValue2()); l2.next();continue;}
        if(l1.getValue2() == l2.getValue2()) {tmp.append(l1.getValue1()+l2.getValue1(),l1.getValue2());l1.next();l2.next();continue;}
    }
    tmp.traverse();
}

/*void adding( LList<int> p , LList<int> q){
    LList<int> sum;
    while(p.getValue2() != 0 ){
        if(p.getValue2() > q.getValue2()) sum.append(p.getValue1(),p.getValue2());
        if(p.getValue2() < q.getValue2()) sum.append(q.getValue1(),q.getValue2());
        else sum.append(p.getValue1() + q.getValue1(),q.getValue2());
        p.next();
        q.next();
    }
    sum.traverse();

}*/


int main(){
    int x;
    LList<int> list1, list2;
    list1.append(1,5);
    list1.append(2,4);
    list1.append(5,2);
    list1.append(1,0);
    list1.traverse();

    cout << endl;
    list2.append(6,4);
    list2.append(3,3);
    list2.append(2,0);
    list2.traverse();
    cout << endl;
    list1 + list2;

    return 0;
}

