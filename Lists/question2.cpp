#include <iostream>
#include <cstring>
using namespace std;



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
    virtual  void remove() = 0;
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
friend void operator+( LList<E> &l1,  LList<E> & l2);
friend void operator-( LList<E> &l1,  LList<E> & l2);

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
        curr->next = new Link<E>(it,curr->next);
        if (tail == curr)  tail = curr->next;
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

    const E& getValue() const {
        if(curr->next == NULL) {
            cout  << "No value";
            return E();
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
void traverse(){
    while(getValue() == '0'){next();}
    while(currPos() != length() ){
        cout << getValue();
        next();
    }
}
};

 void  operator+( LList<char> &l1,  LList<char> &l2)
{
    int judge,carry = 0,cal = 0;
    int len1 = 0,len2 = 0;
    LList<char> sum;
    if((l1.getValue() != '-') &&(l2.getValue() != '-')){
            {
                while(l1.getValue() != '.' ){len1 = len1 +1;l1.next();}

                while(l2.getValue() != '.' ){len2 = len2 +1;l2.next();}

            }
            l1.moveToStart();
            l2.moveToStart();
           if(len1 > len2){for(int i  = 0;i <len1-len2 ;i++){l2.insert('0');}}
            if(len1 < len2){for(int i  = 0;i <len2-len1 ;i++){l1.insert('0');}}




            if(l1.length() > l2.length()) {
                for(int i = 0;i < (l1.length() - l2.length());i++){
                    l2.append('0');
                }
            }
            if(l1.length() < l2.length()) {
                for(int i = 0;i < (l2.length() - l1.length());i++){
                    l1.append('0');
                }
            }
            l1.insert('0');
            l2.insert('0');

            l1.moveToEnd();
            l1.prev();
            l2.moveToEnd();
            l2.prev();
            for(int i = 0;i< l1.length()  ;i++){
                if(l1.getValue() == '.') {
                    sum.insert('.');
                    if(l1.currPos() != 0){
                        l1.prev();
                        l2.prev();}
                    continue;}
                else {if( (l1.getValue() -'0'+ l2.getValue() - '0' + carry) < 10) {cal = l1.getValue() -'0'+ l2.getValue() - '0' + carry; carry = 0;}
                        else {cal = l1.getValue() -'0'+ l2.getValue() - '0' + carry - 10; carry  =1;}
                sum.insert('0' + cal  % 10);

                if(l1.currPos() != 0){
                    l1.prev();
                    l2.prev();}
            }//个位进到十位
        }

sum.traverse();
    }

    if((l1.getValue() == '-') &&(l2.getValue() == '-')){
        l1.remove();
        l2.remove();
        cout << '-';
        l1 + l2;


    }

    if((l1.getValue() != '-') &&(l2.getValue() == '-')){
        int bo;//判abs
        l2.remove();
        {
                while(l1.getValue() != '.' ){len1 = len1 +1;l1.next();}

                while(l2.getValue() != '.' ){len2 = len2 +1;l2.next();}

        }
         l1.moveToStart();
            l2.moveToStart();
           if(len1 > len2){for(int i  = 0;i <len1-len2 ;i++){l2.insert('0');}}
            if(len1 < len2){for(int i  = 0;i <len2-len1 ;i++){l1.insert('0');}}




            if(l1.length() > l2.length()) {
                for(int i = 0;i < (l1.length() - l2.length());i++){
                    l2.append('0');
                }
            }
            if(l1.length() < l2.length()) {
                for(int i = 0;i < (l2.length() - l1.length());i++){
                    l1.append('0');
                }
            }
            l1.insert('0');
            l2.insert('0');

            l1.moveToStart();
            l2.moveToStart();

            for(int i = 0;i<l1.length();i++){
                if(l1.currPos() == l1.length() -1){bo = 1;}
                if((l1.getValue() - '0') == (l2.getValue() - '0')){l1.next();l2.next();}
                if((l1.getValue() - '0') > (l2.getValue() - '0')){ bo = 1;break;}
                if((l1.getValue() - '0') < (l2.getValue() - '0')){ bo = 0; break;}

            }

            l1.moveToEnd();
            l1.prev();
            l2.moveToEnd();
            l2.prev();
            if(bo ==1){
            for(int i = 0;i< l1.length()  ;i++){
                if(l1.getValue() == '.') {
                    sum.insert('.');
                    if(l1.currPos() != 0){
                        l1.prev();
                        l2.prev();}
                    continue;}
                else {if( (l1.getValue() -'0'-( l2.getValue() - '0' + carry)) >= 0 ) {cal = l1.getValue() -'0'-( l2.getValue() - '0') + carry; carry = 0;}
                        else {cal = l1.getValue() -'0'- (l2.getValue() - '0') + carry +10 ; carry  = -1;}
                sum.insert('0' + cal  );

                if(l1.currPos() != 0){
                    l1.prev();
                    l2.prev();}
                    }
                }
            }
        if(bo == 0) {
           for(int i = 0;i< l1.length()  ;i++){
                if(l1.getValue() == '.') {
                    sum.insert('.');
                    if(l1.currPos() != 0){
                        l1.prev();
                        l2.prev();}
                    continue;}
                else {if( (l2.getValue() -'0'-( l1.getValue() - '0' + carry)) >= 0 ) {cal = l2.getValue() -'0'-( l1.getValue() - '0') + carry; carry = 0;}
                        else {cal = l2.getValue() -'0'- (l1.getValue() - '0') + carry +10 ; carry  = -1;}
                sum.insert('0' + cal  );

                if(l1.currPos() != 0){
                    l1.prev();
                    l2.prev();}
                    }
                }cout <<'-';

        }
        sum.traverse();

    }

    if((l1.getValue() == '-') &&(l2.getValue() != '-')){
      int bo;//判abs
        l1.remove();
        {
                while(l1.getValue() != '.' ){len1 = len1 +1;l1.next();}

                while(l2.getValue() != '.' ){len2 = len2 +1;l2.next();}

        }
         l1.moveToStart();
            l2.moveToStart();
           if(len1 > len2){for(int i  = 0;i <len1-len2 ;i++){l2.insert('0');}}
            if(len1 < len2){for(int i  = 0;i <len2-len1 ;i++){l1.insert('0');}}




            if(l1.length() > l2.length()) {
                for(int i = 0;i < (l1.length() - l2.length());i++){
                    l2.append('0');
                }
            }
            if(l1.length() < l2.length()) {
                for(int i = 0;i < (l2.length() - l1.length());i++){
                    l1.append('0');
                }
            }
            l1.insert('0');
            l2.insert('0');

            l1.moveToStart();
            l2.moveToStart();

            for(int i = 0;i<l1.length();i++){//相等情况
                if(l1.currPos() == l1.length() -1){bo = 1;}
                if((l1.getValue() - '0') == (l2.getValue() - '0')){l1.next();l2.next();}
                if((l1.getValue() - '0') < (l2.getValue() - '0')){ bo = 1;break;}
                if((l1.getValue() - '0') > (l2.getValue() - '0')){ bo = 0; break;}

            }

            l1.moveToEnd();
            l1.prev();
            l2.moveToEnd();
            l2.prev();
            if(bo ==1){
            for(int i = 0;i< l1.length()  ;i++){
                if(l1.getValue() == '.') {
                    sum.insert('.');
                    if(l1.currPos() != 0){
                        l1.prev();
                        l2.prev();}
                    continue;}
                else {if( (l2.getValue() -'0'-( l1.getValue() - '0' + carry)) >= 0 ) {cal = l2.getValue() -'0'-( l1.getValue() - '0') + carry; carry = 0;}
                        else {cal = l2.getValue() -'0'- (l1.getValue() - '0') + carry +10 ; carry  = -1;}
                sum.insert('0' + cal  );

                if(l1.currPos() != 0){
                    l1.prev();
                    l2.prev();}
                    }
                }
            }
        if(bo == 0) {
           for(int i = 0;i< l1.length()  ;i++){
                if(l1.getValue() == '.') {
                    sum.insert('.');
                    if(l1.currPos() != 0){
                        l1.prev();
                        l2.prev();}
                    continue;}
                else {if( (l1.getValue() -'0'-( l2.getValue() - '0' + carry)) >= 0 ) {cal = l1.getValue() -'0'-( l2.getValue() - '0') + carry; carry = 0;}
                        else {cal = l1.getValue() -'0'- (l2.getValue() - '0') + carry +10 ; carry  = -1;}
                sum.insert('0' + cal  );

                if(l1.currPos() != 0){
                    l1.prev();
                    l2.prev();}
                    }
                }cout <<'-';
        }
        sum.traverse();
    }

}

void operator-( LList<char> &l1,  LList<char> &l2){
    if((l1.getValue() != '-') &&(l2.getValue() != '-')){
        l2.insert('-');
        l1 + l2;
    }
    if((l1.getValue() != '-') &&(l2.getValue() == '-')){
        l2.remove();
        l1 + l2;
    }
    if((l1.getValue() == '-') &&(l2.getValue() != '-')){
        l1.remove();
        cout << '-';
        l1 + l2;
    }
    if((l1.getValue() == '-') &&(l2.getValue() == '-')){
        l2.remove();
        l1 + l2;
    }
}
int main(){
    LList<char> x,y;
    char tmp[100000];
    cout << "input x:";
    cin.getline(tmp,' ');
    for(int i = 0;i < strlen(tmp);i++){
        x.append(tmp[i]);
    }

    cout << "input y:";
    cin.getline(tmp,' ');

    for(int i = 0;i < strlen(tmp);i++){
        y.append(tmp[i]);
    }
    cout << "x+y = ";
    x+y;
    cout << endl << "x-y=";
    x-y;
}
