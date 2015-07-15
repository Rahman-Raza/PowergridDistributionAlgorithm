#ifndef ROUTER_H
#define	ROUTER_H


#include "RouterRunner.h"
#include "StackLi.h"
#include "StackAr.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>

class Router {
public:
  Router(CityInfo *infos, int numCities);
  int setTransfers(Transfer **transfers);
  int index2 [25000];
  void DFS (CityInfo *stats2, int k);
 void DFSHelp (bool *visit,int v, int counter, Transfer **transfers);
 int DFSHelp2 ( bool *visit, int v,int counter, Transfer **transfers);
  CityInfo *stats;
   StackLi <int> stack;
    StackLi <int> stack2;
    int stackcount;
   
  int numofCities;
  
  int Index2;
  int transfercount;
}; // class Router 

#endif	// ROUTER_H

