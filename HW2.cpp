#include <iostream>
#include <cmath>
#include <string>
using namespace std;

float AvergeLen(string str, string p);
int count(string s, char c);
  
int main()
{
    string punct = ",.;!?";
    int train = 0, valid = 0;
    cin >> train >> valid;
  
    int* Answer; float* sentenceLen;
    Answer = new int [train];
    sentenceLen = new float [train];
  
    /*紀錄每個句子的男女性別、平均長度*/
    for(int i = 0; i < train; i++)
    {
        cin >> Answer[i]; 
        cin.ignore(); //忽略分號
  
        string str;
        getline(cin, str); //將整個句子讀入

        sentenceLen[i] = AvergeLen(str, punct);
    }
  
    /*計算臨界值範圍*/

    int maxLen = 0;
    int minLen = 10000;
    for(int i = 0; i < train; i++)
    {
        if(sentenceLen[i] > maxLen)
            maxLen = sentenceLen[i];
        if(sentenceLen[i] < minLen)
            minLen = sentenceLen[i];
    }
  
    /*計算最佳臨界值*/
    int critical_num, error = 100001;

    for(int i = 0; i < maxLen; i++)
    {
        int WA = 0;
        for(int j = 0; j < train; j++)
        {
            if((sentenceLen[j] >= i && Answer[j] == 1)||(sentenceLen[j] < i && Answer[j] == 2))
                WA += 1;
        }

        if(WA < error)
        {
            error = WA;
            critical_num = i;
        }
    }
  
    /*驗證資料*/
    int WA = 0;
    for(int i = 0; i < valid; i++)
    {
        int gender = 0; // 1：Male, 2：Female
        cin >> gender; 
        cin.ignore(); //忽略分號
  
        string str;
        getline(cin, str); //將整個句子讀入

        float length = AvergeLen(str, punct);

        if(((length < critical_num && gender == 2))||((length >= critical_num && gender == 1)))
            WA += 1;
    }
  
    cout << critical_num << "," << WA << endl;
      
    delete [] Answer;
    delete [] sentenceLen;
    Answer = nullptr;
    sentenceLen = nullptr;

    return 0;
}

float AvergeLen(string str, string p)
{
    int current = 0, nextpos = 0, punctCnt = 0;
        
        while (current != str.size())
        {   
            nextpos = str.find_first_of(p, current); //找出標點符號的位置
            
            if(str[nextpos+1] == ' ')
                punctCnt += 1;
            if(nextpos == str.length()-1)
                punctCnt += 1;

            current = (nextpos + 1);
        }

        return (count(str, ' ')+ 1)/punctCnt;
}

int count(string s, char c)
{
    int number = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == c)
            number += 1;
    }
    return number;
}