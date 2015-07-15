// Author: Sean Davis
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "router.h"
#include "StackLi.h"
#include "StackAr.h"
#include "RouterRunner.h"

Router::Router(CityInfo *infos, int numCities) 
{
  CityInfo *cities = new CityInfo[numCities];
  
  memcpy(cities,infos,numCities * sizeof(CityInfo));
  
  stats = new CityInfo[numCities];
  memcpy(stats, cities, numCities * sizeof(CityInfo));
  
  numofCities = numCities;
  Index2 = 0;
  
  for (int u = 0; u < 25000; u++)
  {
    index2[u] = 0;
  }
} // Router()

int diff1( CityInfo info)
{
  if ((info.production - info.usage) > 0)
  return 1;
  
  if ((info.production - info.usage) < 0)
    return -1;
  
  if ((info.production - info.usage) == 0)
    return 0;
}

int diff (CityInfo info)
{
  return info.production - info.usage;
}

int Router::setTransfers(Transfer **transfers)
{
 

  
 
  bool *visit = new bool [numofCities];
  
  for (int o = 0; o < numofCities; o++)
    visit[o] = false;
  
  stack.makeEmpty();
  
  DFSHelp ( visit, stats[1].adjList[0], 0,transfers);
  
  
 
  
 



  
   return transfercount;  // should be set to total of all transfers.
}

  
 void Router::DFSHelp (bool *visit, int v, int counter, Transfer **transfers)
  {
   
   
    visit[v] = true;
    
    counter += diff(stats[v]);  //adds what current vertex has to the  counter
    //cout << " counter1: "<< counter <<endl;
    
    
    if (counter < 0 ) //if counter is still not satisfied
    {
      int counter2 = DFSHelp2(v,counter,transfers);
      counter = counter2;
    }  
      stack.push(v);  //push vertex into stack
      
      if (counter >= 0)   //if counter is satisfied
      {
        while (!stack.isEmpty())    //empty stack, transfer power
    {
      int source = stack.topAndPop();
      if (!stack.isEmpty())
      {
      int dest = stack.topAndPop();
      int adjdiff= diff(stats[source]);
      transfercount += adjdiff;
      stats[dest].production += adjdiff;
      stats[source].production -= adjdiff;
      transfers[source][index2[source]].destCity = dest;
      transfers[source][index2[source]].amount = adjdiff;
      index2[source]++;
     
      }
    }
        counter = 0;
        
      }
      
      
      
      
    
    
    
//      
       

      //cout << stack.top() << " ";
        
     for (int j = 0; j < stats[v].adjCount; ++j)   //continue traversal.
      if (!visit[stats[v].adjList[j]])
        DFSHelp(visit,stats[v].adjList[j],counter,transfers);
    
    
    
    
 }  
 
 
  int Router::DFSHelp2 ( int v, int counter, Transfer **transfers)
  {
    int l;
     for (int i = 0; i < stats[v].adjCount; i++)
      {
        if ( (diff(stats[stats[v].adjList[i]]) > 0) ) //checking stats[v]'s neighbors has more power than v.
        {
          int adjust;
         
          if ( (diff(stats[stats[v].adjList[i]])) > (counter * (-1) )) //if neighbor has more than counter needs
          {
          adjust = (counter * (-1) );
          }
          
          else {
            adjust = diff(stats[stats[v].adjList[i]]);  //else take all from neighbor
          }
          
          //cout<<" adjust: " << adjust <<endl;
          counter += adjust;
          
          //cout <<" city: "<< v <<" counter =" << counter << endl;
          
          
          transfercount += adjust;
          stats[v].production += (adjust);
          stats[stats[v].adjList[i]].production -= adjust;
          transfers[stats[v].adjList[i]][index2[stats[v].adjList[i]]].destCity = v;
          
          transfers[stats[v].adjList[i]][index2[stats[v].adjList[i]]].amount = adjust;
          index2[stats[v].adjList[i]]++;
          
          l = i;
        }
           
        if (counter >= 0)  //if stats[v] gets the power it needs from neighbors break from loop
          break;
     }
    
    if (counter >= 0)
    {
      return counter;
    }
      
    else 
      return DFSHelp2(stats[v].adjList[0], counter, transfers);
    
  }
 
 
 
 // if (diff(stats[v]) < 0)  // if stats[v] still doesnt have enough power]
//      {
//      stack.push(v);
//      counter += diff(stats[v]);
//      }
//      
//    
//    
//    if (diff(stats[v]) > 0)   //if stats[v] has more than enough power
//    {
//      if (!stack.isEmpty())   //check to see if stack has vertices that need power
//      {
//      stack.push(v);
//      counter += diff(stats[v]);
//      
//      
//      if (counter >= 0)    //if counter has enough power to distribute to stack.  
//      {
//        while (!stack.isEmpty())    //empty stack, transfer power
//    {
//      int source = stack.topAndPop();
//      if (!stack.isEmpty())
//      {
//      int dest = stack.topAndPop();
//      int adjdiff= diff(stats[source]);
//      transfercount += adjdiff;
//      stats[dest].production += adjdiff;
//      stats[source].production -= adjdiff;
//      transfers[source][index2[source]].destCity = dest;
//      transfers[source][index2[source]].amount = adjdiff;
//      index2[source]++;
//     
//      }
//    }
//        counter = 0;
//      }
//    }
//      
//      
//    }
    

    
    
    
    
    
    
 