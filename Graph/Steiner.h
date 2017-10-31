#ifndef STEINER_H_INCLUDED
#define STEINER_H_INCLUDED
#include <cmath>
#include <fstream>
#include <cassert>

#define MAXDIS 0x7fffffff

using namespace std;

template <typename E>
class Heap
{
private:
    E* storage;
    int nodeNum;
    int maxSize;

    void doubleSpace()
    {
        E* arr = new E[2 * maxSize + 1], *temp;
        for(int i = 1; i <= nodeNum; ++i)
        {
            arr[i] = storage[i];
        }
        maxSize *= 2;
        temp = storage;
        storage = arr;
        delete [] temp;
    }

    void buildHeap()
    {
        for(int i = nodeNum / 2; i >= 1; --i)
        {
            siftDown(i);
        }
    }

    void siftDown(int i)
    {
        if(i > nodeNum / 2)
        {
            return;
        }
        E temp;
        if(storage[i].newEdge -> dis > storage[2 * i].newEdge -> dis || (2 * i + 1 <= nodeNum && storage[i].newEdge -> dis > storage[2 * i + 1].newEdge -> dis))
        {
            if(2 * i + 1 > nodeNum || storage[2 * i].newEdge -> dis < storage[2 * i + 1].newEdge -> dis)
            {
                temp = storage[2 * i];
                storage[2 * i] = storage[i];
                storage[i] = temp;
                siftDown(2 * i);
            }
            else
            {
                temp = storage[2 * i + 1];
                storage[2 * i + 1] = storage[i];
                storage[i] = temp;
                siftDown(2 * i + 1);
            }
        }
    }

    void preOrderHelp(int i)
    {
        if(i > nodeNum)
        {
            return;
        }
        cout << storage[i] << ' ';
        preOrderHelp(2 * i);
        preOrderHelp(2 * i + 1);
    }

    void inOrderHelp(int i)
    {
        if(i > nodeNum)
        {
            return;
        }
        inOrderHelp(2 * i);
        cout << storage[i] << ' ';
        inOrderHelp(2 * i + 1);
    }
public:
    Heap(int num = 100)
    {
        maxSize = num;
        storage = new E[num + 1];
        nodeNum = 0;
    }

    Heap(const E ele[], int num)
    {
        maxSize = num + 10;
        nodeNum = num;
        storage = new E[maxSize + 1];
        for(int i = 1; i <= nodeNum; ++i)
        {
            storage[i] = ele[i - 1];
        }
        buildHeap();
    }

    ~Heap()
    {
        delete [] storage;
    }

    void enQueue(const E& e)
    {
        if(nodeNum == maxSize)
        {
            doubleSpace();
        }
        int p = ++nodeNum;
        if(nodeNum == maxSize)
        {
            doubleSpace();
        }
        while(p >= 2 && e.newEdge -> dis < storage[p / 2].newEdge -> dis)
        {
            storage[p] = storage[p / 2];
            p /= 2;
        }
        storage[p] = e;
    }

    E deQueue()
    {
        assert(nodeNum > 0);
        E temp = storage[1];
        storage[1] = storage[nodeNum--];
        siftDown(1);
        return temp;
    }

    void preOrder()
    {
        preOrderHelp(1);
    }

    void inOrder()
    {
        inOrderHelp(1);
    }

    int Size()
    {
        return nodeNum;
    }

    void levelOrder()
    {
        for(int i = 1; i <= nodeNum; ++i)
        {
            cout << storage[i] << ' ';
        }
    }
};

class SteinerEdge;

int divide(int kruskal[500000], int low, int high, SteinerEdge* kruskalEdge[500000]);

class SteinerGraph;
class SteinerNode;
class CopSteinerEdge;

class SteinerEdge
{
    friend Heap<CopSteinerEdge>;
    friend SteinerGraph;
    friend SteinerNode;
    friend CopSteinerEdge;
    friend int divide(int kruskal[500000], int low, int high, SteinerEdge* kruskalEdge[500000]);
    //friend bool operator<(const SteinerEdge* s1, const SteinerEdge* s2);
    //friend bool operator>(const SteinerEdge* s1, const SteinerEdge* s2)
private:
    double dis;
    int index;
    SteinerEdge* next;
    bool vir;
    bool inMST;
public:
    SteinerEdge(int ind, double di, SteinerEdge* ne = NULL, bool v = false, bool in = false) : dis(di), index(ind), next(ne), vir(v), inMST(in)
    {

    }

    ~SteinerEdge()
    {

    }
};

/*bool operator<(const SteinerEdge* s1, const SteinerEdge* s2)
{
    return (s1 -> dis < s2 -> dis);
}

bool operator>(const SteinerEdge* s1, const SteinerEdge* s2)
{
    return (s1 -> dis > s2 -> dis);
}*/

void Swap(int kruskal[500000], int a, int b, SteinerEdge* kruskalEdge[500000])
{
    int temp0 = kruskal[a];
    SteinerEdge* temp = kruskalEdge[a];
    kruskal[a] = kruskal[b];
    kruskalEdge[a] = kruskalEdge[b];
    kruskal[b] = temp0;
    kruskalEdge[b] = temp;
}

int divide(int kruskal[500000], int low, int high, SteinerEdge* kruskalEdge[500000])
{
    int temp2 = kruskalEdge[high] -> dis, a = low, b = high;
    while(a < b)
    {
        while(kruskalEdge[++a] -> dis < temp2);
        while(a < b && kruskalEdge[--b] -> dis >= temp2);
        Swap(kruskal, a, b, kruskalEdge);
    }
    Swap(kruskal, b, high, kruskalEdge);
    return a;
}

void quickSort(int kruskal[500000], int low, int high, SteinerEdge* kruskalEdge[500000])
{
    if(low >= high)
    {
        return;
    }
    int mid = divide(kruskal, low - 1, high, kruskalEdge);
    quickSort(kruskal, low, mid - 1, kruskalEdge);
    quickSort(kruskal, mid + 1, high, kruskalEdge);
}

class DisJointSet
{
private:
    int *parent;
    int Size;
public:
    DisJointSet(int si = 0) : Size(si)
    {
        parent = new int[si];
        for(int i = 0; i < si; ++i)
        {
            parent[i] = -1;
        }
    }

    ~DisJointSet()
    {
        delete [] parent;
    }

    int Find(int i)
    {
        if(parent[i] < 0)
        {
            return i;
        }
        else
        {
            return Find(parent[i]);
        }
    }

    void Union(int root1, int root2)
    {
        if(root1 == root2)
        {
            return;
        }
        if(parent[root1] > parent[root2])
        {
            parent[root2] = parent[root1] + parent[root2];
            parent[root2] = root1;
        }
        else
        {
            parent[root1] = parent[root1] + parent[root2];
            parent[root1] = root2;
        }
    }
};

class SteinerNode
{
    friend SteinerGraph;
private:
    double x, y;
    SteinerEdge* head;
public:
    SteinerNode(double X = 0, double Y = 0, SteinerEdge* he = NULL) : x(X), y(Y), head(he)
    {
        head = new SteinerEdge(0, 0);
    }

    ~SteinerNode()
    {
        //cout << "ins" << endl;
        SteinerEdge* p = head;
        while(head)
        {
            p = head;
            head = head -> next;
            delete p;
        }
        //cout << "outs" << endl;
    }
};

class CopSteinerEdge
{
public:
    SteinerEdge* newEdge;
    SteinerEdge* oldEdge;

    CopSteinerEdge(SteinerEdge* nE = NULL, SteinerEdge* oE = NULL) : newEdge(nE), oldEdge(oE)
    {

    }

    ~CopSteinerEdge()
    {
        /*if(newEdge != oldEdge)
        {
            delete newEdge;
        }*/
    }
};

class SteinerGraph
{
private:
    SteinerNode* Nodes;
    int n;
    int m;
    double r;
    static int kruskal[500000];
    static SteinerEdge* kruskalEdge[500000];
    static int edgeNum;
    static int SteinerTree[100000][3];
    static int kruskalCounter;
    int numOfHops;
    double totalLen;

    void replaceVirLink(int a, int b)
    {
        int lowCost[100000], pre[100000], preCode[100000];
        SteinerEdge* preEdge[100000];
        for(int i = 0; i < n; ++i)
        {
            lowCost[i] = MAXDIS;
            pre[i] = MAXDIS;
            preEdge[i] = NULL;
            preCode[i] = -1;
        }
        Heap<CopSteinerEdge> heap;
        CopSteinerEdge start;
        for(SteinerEdge* p = Nodes[a].head; p -> next; p = p -> next)
        {
            if(!p -> next -> vir)
            {
                heap.enQueue(CopSteinerEdge(p -> next, p -> next));
                lowCost[p -> next -> index] = p -> next -> dis;
                preEdge[p -> next -> index] = p -> next;
                pre[p -> next -> index] = 1;
                preCode[p -> next -> index] = a;
            }
        }
        for(int i = 0; i < n - 1; ++i)
        {
            start = heap.deQueue();
            //cout << start -> index << endl;
            //cout << b << endl;
            if(start.newEdge -> index == b)
            {
                break;
            }
            for(SteinerEdge* p = Nodes[start.newEdge -> index].head; p -> next; p = p -> next)
            {
                if(!p -> next -> vir && (p -> next -> dis + start.newEdge -> dis < lowCost[p -> next -> index] || (p -> next -> dis + start.newEdge -> dis == lowCost[p -> next -> index] && 1 + pre[start.newEdge -> index] < pre[p -> next -> index])))
                {
                    lowCost[p -> next -> index] = p -> next -> dis + start.newEdge -> dis;
                    heap.enQueue(CopSteinerEdge(new SteinerEdge(p -> next -> index, lowCost[p -> next -> index]), p -> next));
                    preEdge[p -> next -> index] = p -> next;
                    //cout << p -> next -> index << ' ' << start.newEdge -> index << endl;
                    pre[p -> next -> index] = 1 + pre[start.newEdge -> index];
                    preCode[p -> next -> index] = start.newEdge -> index;
                }
            }
        }
        int temp = b;
        //cout << a << ' ' << b << endl;
        //cout << pre[b] << endl;
        for(int i = 0; i < pre[b]; ++i)
        {
            //cout << b << ' ' << temp << endl;
            totalLen += preEdge[temp] -> dis;
            //cout << b << ' ' << temp << endl;
            preEdge[temp] -> inMST = true;
            //cout << '?' << ' ' << preEdge[temp] -> index << endl;
            //cout << preCode[temp]  << ' ' << temp << endl;
            temp = preCode[temp];
            //cout << a << ' ' << temp << ' ' << b << endl;
        }
       // cout << (temp == a) << endl;
    }

    void printHelp(int i, bool visited[100000], int root)
    {
        cout << Nodes[i].x << ' ' << Nodes[i].y << ' ' << root << endl;
        visited[i] = true;
        for(int j = 0; j < SteinerTree[i][2]; ++j)
        {
            if(!visited[SteinerTree[i][j]])
            {
                printHelp(SteinerTree[i][j], visited, i);
            }
        }
    }
public:
    SteinerGraph(ifstream& fin)
    {
        numOfHops = 0;
        totalLen = 0;
        fin >> m >> n >> r;
        Nodes = new SteinerNode[n];
        for(int i = 0; i < n; ++i)
        {
            fin >> Nodes[i].x >> Nodes[i].y;
        }
        double d;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i == j)
                {
                    continue;
                }
                d = sqrt((Nodes[i].x - Nodes[j].x) * (Nodes[i].x - Nodes[j].x) + (Nodes[i].y - Nodes[j].y) * (Nodes[i].y - Nodes[j].y));
                //cout << d << ' ' << r / sqrt(n) << endl;
                if(d <= r / sqrt(n))
                {
                   // cout << i << ' ' << j << endl;
                    Nodes[i].head -> next = new SteinerEdge(j, d, Nodes[i].head -> next);
                }
            }
        }
    }

    ~SteinerGraph()
    {
        delete [] Nodes;
    }

    void AddVirtualLink()
    {
        for(int i = 0; i < m; ++i)
        {
            bool link[1000] = {false};
            SteinerEdge* p = Nodes[i].head;
            while(p -> next)
            {
                if(p -> next -> index < m)
                {
                    link[p -> next -> index] = true;
                }
                p = p -> next;
            }
            for(int j = 0; j < m; ++j)
            {
                if(!link[j] && i != j)
                {
                    Nodes[i].head -> next = new SteinerEdge(j, sqrt((Nodes[i].x - Nodes[j].x) * (Nodes[i].x - Nodes[j].x) + (Nodes[i].y - Nodes[j].y) * (Nodes[i].y - Nodes[j].y)), Nodes[i].head -> next, true);
                }
            }
        }
    }

    void MST()
    {
        DisJointSet Vpie(m);

        int counter = 0;

        for(int i = 0; i < m; ++i)
        {
            for(SteinerEdge* p = Nodes[i].head; p -> next != NULL; p = p -> next)
            {
                if(p -> next -> index < m)
                {
                    kruskal[counter++] = i;
                    kruskalEdge[counter - 1] = p -> next;
                }
            }
        }
        quickSort(kruskal, 0, m * (m - 1) / 2 - 1, kruskalEdge);

        int i = 0;
        for(kruskalCounter = 0; i < m - 1; ++kruskalCounter)
        {
            int a = Vpie.Find(kruskal[kruskalCounter]), b = Vpie.Find(kruskalEdge[kruskalCounter] -> index);
            if(a != b)
            {
                Vpie.Union(a, b);
                ++i;
                kruskalEdge[kruskalCounter] -> inMST = true;
            }
        }
    }

    void removeVirtualLink()
    {
        for(int i = 0; i < kruskalCounter; ++i)
        {
            if(kruskalEdge[i] -> inMST && kruskalEdge[i] -> vir)
            {
                ++numOfHops;
                kruskalEdge[i] -> inMST = false;
                replaceVirLink(kruskal[i], kruskalEdge[i] -> index);
            }
        }
    }

    void removeRedun()
    {
        DisJointSet Vpie(n);
        for(int i = 0; i < n; ++i)
        {
            int b = Vpie.Find(i);
            for(SteinerEdge* p = Nodes[i].head; p -> next; p = p -> next)
            {
                int a = Vpie.Find(p -> next -> index);
                if(p -> next -> inMST && a != b)
                {
                    SteinerTree[i][SteinerTree[i][2]++] = p -> next -> index;
                    SteinerTree[p -> next -> index][SteinerTree[p -> next -> index][2]++] = i;
                    Vpie.Union(a, b);
                }
                else
                {
                    if(p -> next -> inMST)
                    {
                        p -> next -> inMST = false;
                    }
                }
            }
        }
    }

    void printTree()
    {
        bool visited[100000] = {false};
        cout << numOfHops << ' ' << totalLen << endl;
        cout << Nodes[0].x << ' ' << Nodes[0].y << ' ' << "Root" << endl;
        visited[0] = true;
        printHelp(1, visited, 0);
    }
};

int SteinerGraph::kruskal[500000];
SteinerEdge* SteinerGraph::kruskalEdge[500000];
int SteinerGraph::SteinerTree[100000][3] = {0};
int SteinerGraph::edgeNum = 0;
int SteinerGraph::kruskalCounter = 0;

#endif // STEINER_H_INCLUDED
