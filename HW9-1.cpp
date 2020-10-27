#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <queue>
#include <utility>
using namespace std;
 
 
int main()
{
  queue < pair<float, float> > bankQueue;
  priority_queue < pair<float, float>, vector<pair<float, float> >,greater<pair<float, float> > > eventListQueue;
 
   int totalCustomer = 0;
   float avergeWaitingT = 0.0;
   string file;
   bool tellerAvailable = true;
 
   while (getline(cin, file))
   {
       int pos = file.find('\t');
       float arriveT = stof(file.substr(0, pos));
       float processT = stof(file.substr(pos+1));
        
       eventListQueue.push(make_pair(arriveT, processT));
       totalCustomer++;
   }
    
   //Simulation開始
    
   cout << "Simulation Begins" << endl;
    
   while(!eventListQueue.empty())
   {
      float currentT = eventListQueue.top().first;
      float transacT = eventListQueue.top().second;
 
      if(transacT != 1000) // 該Event為Arrival Event
      {
         cout << "Processing an arrival event at time: " << currentT << endl;
         eventListQueue.pop();
 
         if(bankQueue.empty() && tellerAvailable) //來了就直接辦理無需等待
         {
            float departureT = currentT + transacT;
            eventListQueue.push(make_pair(departureT, 1000));
            tellerAvailable = false;
            avergeWaitingT += 0;
         }
         else
         {
            bankQueue.push(make_pair(currentT, transacT));
         }
      }
      else //該Event為Departure Event
      {
         cout << "Processing a departure event at time: " << currentT << endl;
         eventListQueue.pop();
 
         if(!bankQueue.empty())
         {
            float arrival = bankQueue.front().first;
            float length = bankQueue.front().second;
            bankQueue.pop();
            float departureT = currentT + length;
            eventListQueue.push(make_pair(departureT, 1000));
            avergeWaitingT += (currentT - arrival);
         }
         else
         {
            tellerAvailable = true;
         }
      }
        
   }
 
   avergeWaitingT = avergeWaitingT / totalCustomer;
    
   cout << "Simulation Ends" << endl;
   cout << '\n'; 
    
   cout << "Final Statistics:" << endl;
   cout << '\n'; 
    
   cout << '\t' << "Total number of people processed: " << totalCustomer << endl;
   cout << '\t' << "Average amount of time spent waiting: " << fixed << setprecision(1)  << avergeWaitingT << endl;   
 
    
   return 0;
}