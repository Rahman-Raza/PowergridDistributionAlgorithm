// Author: Sean Davis
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "router.h"
#include "StackLi.h"
#include "RouterRunner.h"

Router::Router(CityInfo *infos, int numCities) 
{
  CityInfo *cities = new CityInfo[numCities];
  
  memcpy(cities,infos,numCities * sizeof(CityInfo));
  
  stats = new CityInfo[numCities];
  memcpy(stats, cities, numCities * sizeof(CityInfo));
  
  numofCities = numCities;
  Index2 = 0;
} // Router()

int diff( CityInfo info)
{
  return info.production - info.usage;
}

int Router::setTransfers(Transfer **transfers)
{
 
  int i;
  int transfercount = 0;
 for (i = 0; i < numofCities; i++)
 {
   int diff1 = diff(stats[i]);
   
   if (diff1 < 0)
   {
  bool *visit = new bool [numofCities];
  
  for (int o = 0; o < numofCities; o++)
    visit[o] = false;
  
  stack.makeEmpty();
  
  DFSHelp ( visit, i, i,0,transfers);
  Index2++;
  
 
}  // setTransfers

}
  
   return transfercount;  // should be set to total of all transfers.
}

  
 void Router::DFSHelp (bool *visit, int k,int v, int counter, Transfer **transfers)
  {
   
   stack.push(v);
    visit[v] = true;
    
    int j;
    
    for (j = 0; j <stats[v].adjCount; j++)
    {
       int adjdiff = diff(stats[stats[v].adjList[j]]);
       if (adjdiff > 0)
       {
         counter += adjdiff;
       }
       if  ((stats[k].production + counter) < stats[k].usage)
       {
         if (!visit[stats[v].adjList[++j]])
         {
           
           DFSHelp(visit, k,stats[v].adjList[++j],counter,transfers);
         }
         else continue;
         
       }
       
       else break;
       
      
       
    }
    
    while (!stack.isEmpty())
    {
      int source = stack.topAndPop();
      if (!stack.isEmpty())
      {
      int dest = stack.topAndPop();
      int adjdiff= diff(stats[source]);
      transfercount += adjdiff;
      stats[dest].production += adjdiff;
      stats[source].production -= adjdiff;
      transfers[source][Index2].destCity = dest;
      transfers[source][Index2].amount = adjdiff;
      }
    }
    
    
    
    
    
    
    
  }
  