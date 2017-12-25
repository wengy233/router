//
//  tp.h
//  3
//
//  Create
//

#ifndef tp_h
#define tp_h
#define maxVertices 10
const int maxWeight=INT_MAX;
using namespace std;
struct Router{
    int number;
    string address;
};
class Graphmtx{
protected:
    int numVertices;
    int numEdges;
    string *VerticesList;
    int *p;
    int **Edge;
public:
    Graphmtx();
    int search(int v);
    bool insertVertex(int n,const string vertex);
    bool insertEdge(int v1,int v2,int cost);
    bool removeVertex(int v);
    bool removeEdge(int v1,int v2);
    void remove(int v);
    void remove2(int v1,int v2);
    void Shortest(int n);
    void printPath(int v,int dist[],int path[]);
    void shuchu();
};
Graphmtx::Graphmtx(){
    numVertices = 0;
    numEdges = 0;
    int i,j;
    VerticesList = new string[maxVertices];
    p=new int[maxVertices];
    Edge = (int **) new int*[maxVertices];
    for(i = 0;i<maxVertices;i++)
        Edge[i] = new int[maxVertices];
    for(i=0;i<maxVertices;i++)
        for(j = 0;j<maxVertices;j++)
            Edge[i][j] = (i==j) ?0:maxWeight;
}
int Graphmtx::search(int v){
    int i;
    for(i=0;i<numVertices;i++){
        if(p[i]==v){
            break;
        }
    }
    return i;
}
bool Graphmtx::insertVertex(int n,const string vertex)
{
    if(numVertices == maxVertices)
        return false;
    VerticesList[numVertices] = vertex;
    p[numVertices]=n;
    numVertices++;
    return true;
}
bool Graphmtx::insertEdge(int v1, int v2,int cost)
{
    if(v1 > -1 && v1< numVertices && v2>-1 && v2<numVertices && Edge[v1][v2] == maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges ++;
        return true;
    }
    else return false;
}
bool Graphmtx::removeVertex(int v)
{
    if(v < 0 && v>= numVertices)
        return false;
    if(numVertices == 1)
        return false;
    int i,j;
    VerticesList[v] = VerticesList[numVertices - 1];
    p[v]=p[numVertices-1];
    for(i = 0;i<numVertices;i++)
    {
        if( Edge[i][v] >0 && Edge[i][v] <maxWeight )
            numEdges --;
    }
    for(i = 0;i<numVertices;i++)
    {
        Edge[i][v] = Edge[i][numVertices-1];
    }
    numVertices --;
    for(j= 0;j<numVertices;j++)
        Edge[v][j] =Edge[numVertices][j];
    return true;
}
bool Graphmtx::removeEdge(int v1,int v2)
{
    if (v1 > -1 && v1< numVertices && v2>-1 && v2<numVertices && Edge[v1][v2] > 0 && v1 != v2 && Edge[v1][v2]< maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1]=maxWeight;
        numEdges --;
        return true;
    }
    else
    {
        return false;
    }
}
void Graphmtx::remove(int v){
    int i;
    i=search(v);
    removeVertex(i);
}
void Graphmtx::remove2(int v1,int v2){
    int i,j;
    i=search(v1);
    j=search(v2);
    removeEdge(i,j);
}
void Graphmtx::Shortest(int v){
    int dist[numVertices];
    int path[numVertices];
    int n = numVertices;
    bool *S = new bool[n];
    int i, j, k;
    int w, min;
    for (i = 0; i<n; i++)
    {
        dist[i] = Edge[v][i];
        S[i] = false;
        if (i != v && dist[i] <maxWeight)
            path[i] = v;
        else
        {
            path[i] = -1;
        }
    }
    S[v] = true;
    dist[v] = 0;
    for (i = 0; i<n - 1; i++)
    {
        min = maxWeight;
        int u = v;
        for (j = 0; j<n; j++)
        {
            if (S[j] == false && dist[j] < min)
            {
                u = j;
                min = dist[j];
            }
        }
        S[u] = true;
        for (k = 0; k<n; k++)
        {
            w = Edge[u][k];
            if (S[k] == false && w <maxWeight && dist[u] + w<dist[k])
            {
                dist[k] = dist[u] + w;
                path[k] = u;
            }
        }
    }
    printPath(v,dist,path);
}

#endif /* tp_h */
