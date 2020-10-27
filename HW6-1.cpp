#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

bool judge(const pair<int, double> a,const pair<int ,double> b) //以cp值高低排序
{
    if(a.second!=b.second)
        return a.second>b.second;
    else 
        return a.first < b.first;
}

int main()
{
    int num = 0, capacity = 0;
    cin >> num >> capacity;

    double* values;
    double* weights;
    values = new double[num];
    weights = new double[num];

    for(int i = 0; i < num; i++)
    {
        cin >> values[i];
    }

    for(int i = 0; i < num; i++)
    {
        cin >> weights[i];
    }

    vector< pair<int, double> > CP; //紀錄index和CP值
    for(int i = 0; i < num; i++)
    {
        CP.push_back(make_pair(i, values[i]/weights[i]));
    }

   
    sort(CP.begin(), CP.end(), judge);

    double bag = 0; //紀錄重量
    vector <int> index; //紀錄可以放入的index
    
    for(int i = 0; i < num; i++)
    {
        if ((bag + weights[CP[i].first]) <= capacity)
        {
            bag += weights[CP[i].first];
            index.push_back(CP[i].first + 1);
        }
    }


    sort(index.begin(), index.end());
    
    for(int i = 0; i < index.size(); i++)
    {
        if(i != index.size()-1)
            cout << index[i] << ",";
        else
            cout << index[i] << ";";
    }
    cout << bag << endl;

    delete [] values;
    delete [] weights;
    values = nullptr;
    weights = nullptr;

    return 0;
}