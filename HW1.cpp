 #include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}

int main()
{
    int vertex = 0, edgeNum = 0;
    cin >> vertex;
    cin.ignore();
    cin >> edgeNum;
    
    vector <pair<int, int> > adjList[vertex];
    for(int i = 0; i < edgeNum; i++) //紀錄相鄰的點跟臨邊長度
    {
        int v1 = 0, v2 = 0, len = 0;
        cin >> v1;
        cin.ignore();
        cin >> v2;
        cin.ignore();
        cin >> len;
        adjList[v1 - 1].push_back(make_pair(v2-1, len)); //把所有點的數字減一（比較好紀錄）
        adjList[v2 - 1].push_back(make_pair(v1-1, len));
    }

    //將adjacency list裡的pair按照first的大小排序
    for(int i = 0; i < vertex; i++)
    {
        sort(adjList[i].begin(), adjList[i].end(), cmp);
    }

    //鄰接串列：
    // 0：（1,2）（2,4）
    // 1：（0,2）（3,3）
    // 2：（0,4）（4,1）
    // 3：（1,3）（4,5）
    // 4：（2,1）（3,4）（5,4）
    // 5：（4,4)

    vector <pair<int,int> > ::iterator iter; //訪問adjList用

    int startNode = 0, maxEdge = 0;
    cin >> startNode;
    cin.ignore();
    cin >> maxEdge;
    startNode = startNode - 1;

    int *color,            // 0:白色, 1:灰色(當過start point)
        *distance;         // 0:起點, 無限大:從起點走不到的vertex

    color = new int[vertex];
    distance = new int[vertex];

    for(int i = 0; i < vertex; i++)
    {
        color[i] = 0;                  //都設成白色（還沒被找到）
        distance[i] = 100*(vertex-1);  //設定成最遠距離
    }

    int startPos = startNode;

    distance[startPos] = 0; //只有起始點要做

    for(int i = 0; i < vertex; i++)
    {
        color[startPos] = 1;

        for(iter=adjList[startPos].begin();iter!=adjList[startPos].end();iter++) //更新到起始點的距離
        {
            if(color[iter->first] == 0)
            {
                if(iter->second + distance[startPos] < distance[iter->first])
                {
                    distance[iter->first] = iter->second + distance[startPos];
                }
            } 
        }

        int temp = 100*vertex;
        int nextPos = 0;
        for(int i = 0; i < vertex; i++) //尋找新的起始點（在未使用的點中距離原點最近的）
        {
            if(color[i] != 1)
            {
                if(distance[i] <= temp)
                {
                    temp = distance[i];
                    nextPos = i;
                }
            }
        }
        startPos = nextPos;
    }

    vector <int> myNodes; //裝符合距離限制的點

    for(int i = 0; i < vertex; i++)
    {
        if((distance[i] <= maxEdge)&&(i!=startNode))
            myNodes.push_back(i+1);
    }

    if(myNodes.empty() == true)
        cout << "None" << endl;
    else
    {
        for(int i = 0; i < myNodes.size(); i++)
        {
            if(i == myNodes.size()-1)
                cout << myNodes[i] << endl;
            else
                cout << myNodes[i] << ",";
        }
    }

    delete [] color;
    delete [] distance;
    color = nullptr;
    distance = nullptr;

    return 0;
}