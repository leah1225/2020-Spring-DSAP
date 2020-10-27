#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <utility>
using namespace std;

int main()
{
    queue < pair<float, float> > bankQueueA; //Departure Event的processT = 1000
    queue < pair<float, float> > bankQueueB; //Departure Event的processT = 2000
    queue < pair<float, float> > bankQueueC; //Departure Event的processT = 3000
    priority_queue < pair<float, float>, vector<pair<float, float> >,greater<pair<float, float> > > eventListQueue;
    
    bool tellerA_Available = true;
    bool tellerB_Available = true;
    bool tellerC_Available = true;

    string file;
    int totalCustomer = 0;
    float avergeWaitingT = 0.0;

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

   while (!eventListQueue.empty())
   {
       float currentT = eventListQueue.top().first;
       float transacT = eventListQueue.top().second;

       if(transacT != 1000 && transacT != 2000 && transacT != 3000) //該Event為Arrival Event
       {
           cout << "Processing an arrival event at time: " << currentT << endl;
           eventListQueue.pop();

           //先尋找有沒有空的櫃檯
           if(bankQueueA.empty() && tellerA_Available) //如果櫃檯A沒有人
           {
               float departureT = currentT + transacT;
               eventListQueue.push(make_pair(departureT, 1000));
               tellerA_Available = false;
               avergeWaitingT += 0;
           }
           else if(bankQueueB.empty() && tellerB_Available) //如果櫃檯B沒有人
           {
               float departureT = currentT + transacT;
               eventListQueue.push(make_pair(departureT, 2000));
               tellerB_Available = false;
               avergeWaitingT += 0;
           }
           else if(bankQueueC.empty() && tellerC_Available) //如果櫃檯C沒有人
           {
               float departureT = currentT + transacT;
               eventListQueue.push(make_pair(departureT, 3000));
               tellerC_Available = false;
               avergeWaitingT += 0;
           }
           else //如果每個櫃檯都有人則去排最少人的(最少人數一樣就選字母小的)
           {
               int sizeA = bankQueueA.size();
               int sizeB = bankQueueB.size();
               int sizeC = bankQueueC.size();
                
               if(sizeA <= sizeB && sizeA <= sizeC) //bankQueueA排隊的人最少
               {
                   bankQueueA.push(make_pair(currentT, transacT));
               }
               else if(sizeB < sizeA && sizeB <= sizeC) //bankQueueB排隊的人最少
               {
                   bankQueueB.push(make_pair(currentT, transacT));
               }
               else if(sizeC < sizeA && sizeC < sizeB) //bankQueueC排隊的人最少
               {
                   bankQueueC.push(make_pair(currentT, transacT));
               }
           }
           
       }
       else //該Event為Depature Event
       {
           cout << "Processing a departure event at time: " << currentT << endl;
           eventListQueue.pop();

           if(transacT == 1000) //bankQueueA的Depature Event
           {
               if(!bankQueueA.empty())
               {
                   float arrival = bankQueueA.front().first;
                   float length = bankQueueA.front().second;
                   bankQueueA.pop();
                   float departureT = currentT + length;
                   eventListQueue.push(make_pair(departureT, 1000));
                   avergeWaitingT += (currentT - arrival);
               }
               else
               {
                   tellerA_Available = true;
               }
           }
           else if(transacT == 2000) //bankQueueB的Depature Event
           {
               if(!bankQueueB.empty())
               {
                   float arrival = bankQueueB.front().first;
                   float length = bankQueueB.front().second;
                   bankQueueB.pop();
                   float departureT = currentT + length;
                   eventListQueue.push(make_pair(departureT, 2000));
                   avergeWaitingT += (currentT - arrival);
               }
               else
               {
                   tellerB_Available = true;
               }
           }
           else if(transacT == 3000) //bankQueueC的Depature Event
           {
               if(!bankQueueC.empty())
               {
                   float arrival = bankQueueC.front().first;
                   float length = bankQueueC.front().second;
                   bankQueueC.pop();
                   float departureT = currentT + length;
                   eventListQueue.push(make_pair(departureT, 3000));
                   avergeWaitingT += (currentT - arrival);
               }
               else
               {
                   tellerC_Available = true;
               }
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