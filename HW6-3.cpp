#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool complete(int **adjMatrix, int i, bool seen[], int matchR[],int n) //看看工作i是否能被做完
{
  for (int j = 0; j < n; j++)
  {
      if (adjMatrix[i][j] == 1 && seen[j] == false) //如果工作i有人可以做但沒被看過
      {
          seen[j] = true; //這個工作被訪問過了
          if (matchR[j] < 0 || complete(adjMatrix, matchR[j], seen, matchR,n))
          {
              matchR[j] = i;
              return true;
          }
      }
  }
  return false;
}


int maxFlow(int **adjMatrix,int m,int n)
{
    int matchR[n]; //紀錄哪些工作被誰做了，上面紀錄員工編號，如果等於-1代表沒有人做這個工作

    for(int i = 0; i < n; i++)
    {
      matchR[i] = -1; //先將所有工作都設為沒有人做
    }

    int workNum = 0; //計算有哪些工作有人做
    for (int u = 0; u < m; u++)
    {
        bool seen[n]; //先將所有工作都設置成沒有被任何員工看過
        for(int j = 0; j < n; j++)
        {
            seen[j] = 0;
        }

        if (complete(adjMatrix, u, seen, matchR,n)) //從工作1一直到工作m
          workNum++;
    }
    return workNum;
}


int main()
{
  string Punct = ",;";
  int n = 0;
  cin >> n;

  string m;
  getline(cin, m);

  int** adjMatrix;
  adjMatrix = new int*[n];
  for(int i = 0; i < n; i++)
  {
    adjMatrix[i] = new int[n];
  }

  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      adjMatrix[i][j] = 0;
    }
  }


  int i = 0, j = 0;

  while(m != "")
  {
    int current = 0;
    int splitPosition = m.find_first_of(Punct);
    string num;

    if(splitPosition != string::npos)
    {
      if(m[splitPosition] == ',')
      {
        num = num = m.substr(current, splitPosition);
        m = m.substr(splitPosition + 1, m.length()-1);
        adjMatrix[i][stoi(num)-1] = 1;
      }
      if(m[splitPosition] == ';')
      {
        num = num = m.substr(current, splitPosition);
        m = m.substr(splitPosition + 1, m.length()-1);
        adjMatrix[i][stoi(num)-1] = 1;
        i++;
      }
    }
    else
    {
      num = m;
      m = "";
      adjMatrix[i][stoi(num)-1] = 1;
    }
  }

  cout << maxFlow(adjMatrix, n, n) << endl;

  return 0;
}