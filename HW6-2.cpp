#include <iostream>
#include <string>
#include <vector>
 using namespace std;

int main()
{
	//讀入物品數量、包包限重
	int num = 0; 
	int capacity = 0;
	cin >> num >> capacity; 

	//按照順序寫入各個物品的重量
	vector <int> weights;
	for(int i = 0; i < num; i++)
	{
		int n = 0;
		cin >> n;
		weights.push_back(n);
	}


	/*使用Dynamic programing matrix*/
	int** dp;
	dp = new int*[num];
	for (int i = 0; i < num; i++)
	{
		dp[i] = new int [capacity+1];
	}

	//0: IMP、1: NS、2: S
	//先初始化第一行，將其他行都設為IMP
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < capacity + 1; j++)
		{
			if(i == 0 && j == 0) //填入第一行唯一的NS
				dp[i][j] = 1;
			else if(i == 0 && weights[i] == j) //填入第一行唯一的S
				dp[i][j] = 2;
			else
				dp[i][j] = 0;
		}
	}

	for(int i = 0; i < num - 1; i++) //進行到倒數第二行時，最後一行的值就會被寫入
	{
		for(int j = 0; j < capacity + 1; j++)
		{
			//每個S或NS都會貢獻一個NS和S到下一行
			if(dp[i][j] == 1 || dp[i][j] == 2)
			{
				if(dp[i+1][j] != 2) //如果為S或NS，選擇S
				    dp[i+1][j] = 1;
				if(j + weights[i+1] <= capacity)
					dp[i+1][j + weights[i+1]] = 2;
			}
		}
	}

	/*從DP matrix的最後一格判斷是否可以裝滿包包：0：無法、1 or 2：可以*/
	if(dp[num - 1][capacity] == 0)
		cout << 0 << endl;
	else
	{
		vector <int> result; //寫入需要印出的index
		for(int i = num - 1; i >= 0; i--)
		{
			if(dp[i][capacity] == 2)
			{
				result.push_back(i+1); //順序倒著寫入
				capacity = capacity - weights[i];
			}
		}
		
		for (int i = result.size()-1; i >= 0; i--) //因為順序是倒著寫入，輸出的時候也必須倒著輸出
		{
			if(i != 0)
			    cout << result[i] << ",";
			else
			    cout << result[i] << endl;
		}
	}
	
	return 0;
}