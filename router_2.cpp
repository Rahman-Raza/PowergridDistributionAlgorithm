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
    if (diff(stats[v]) < 0 ) //if stats[v] doesnt have enough power
    {
      
      for (int i = 0; i < stats[v].adjCount; i ++)
      {
        if ( (diff(stats[stats[v].adjList[i]]) > 0)) //checking stats[v]'s neighbors has more power than v.
        {
          
          //(diff(stats[stats[v].adjList[i]]) > diff(stats[v]))  &&
          //send power to stats[v]]
          int adjust =  diff(stats[v]);
          transfercount += (adjust * (-1));
          stats[v].production += (adjust * (-1));
          stats[stats[v].adjList[i]].production -= (adjust * (-1));
          transfers[stats[v].adjList[i]][index2[stats[v].adjList[i]]].destCity = v;
          
          transfers[stats[v].adjList[i]][index2[stats[v].adjList[i]]].amount = (adjust * (-1));
          index2[stats[v].adjList[i]]++;
          
          
        }
        
        if (diff(stats[v]) == 0)  //if stats[v] gets the power it needs from neighbors
          break;
        
       
      }
    }
       if (diff(stats[v]) < 0)  // if stats[v] still doesnt have enough power]
      {
      stack.push(v);
      counter += diff(stats[v]);
      }
      
    
    
    if (diff(stats[v]) > 0)   //if stats[v] has more than enough power
    {
      if (!stack.isEmpty())   //check to see if stack has vertices that need power
      {
      stack.push(v);
      counter += diff(stats[v]);
      
      
      if (counter >= 0)    //if counter has enough power to distribute to stack.  
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
    }
      
      
    }
       

        
     for (int j = 0; j < stats[v].adjCount; ++j)   //continue traversal.
      if (!visit[stats[v].adjList[j]])
        DFSHelp(visit,stats[v].adjList[j],counter,transfers);
    
    
    
    
 }  
    

    
    
    
    
    
    
 