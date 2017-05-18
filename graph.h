/*graph.h*/
/*graph.h*/

#include <queue>
#include <set>

#pragma once

#include <string>
#include <vector>

using namespace std;
class Station
{
public:
  string Name;
  int    ID;
  double Latitude;
  double Longitude;
  int    Capacity;
 
  Station(string name, int id, double latitude, double longitude, int capacity)
  {
    Name = name;
    ID = id;
    Latitude = latitude;
    Longitude = longitude;
    Capacity = capacity;
  }
  
  
};

class Graph
{
private:
   
  class Edge
  {
  public:
    int   Src, Dest, Count;
    Edge *Next;
  };
  

  Edge  **Vertices;
  string *Names;
  int     NumVertices;
  int     NumEdges;
  int     Capacity;
      
public:
  Graph(int N);
  ~Graph();

  bool AddVertex(string s);
  bool AddEdge(string src, string dest);
  int GetEdgeWeights(string src, string dest);
  int GetNumVertices();
  int GetNumEdges();
 int DoesEdgeExist(string fromID, string toID);
void GetInfo(string station, vector<Station>& stations);
void Trip_Function(string from,string to);
vector<string> BFS(string v);
set<int> Neighbors(int N);
set<string> GetNeighbors(string v);
void PrintGraph(string title);
};
