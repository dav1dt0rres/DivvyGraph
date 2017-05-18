/*graph.cpp*/
/*graph.cpp*/
#include <string>
#include <vector>
#include <queue>

#include <iostream>
#include <set>
#include "graph.h"

using namespace std;

//
// Constructor:
//
Graph::Graph(int N)
{
  this->NumVertices = 0;
  this->NumEdges = 0;
  this->Capacity = N;

  this->Vertices = new Edge*[N];
  this->Names = new string[N];

}


//
// Destructor:
//
Graph::~Graph()
{
  //
  // Future work:
  //
}

bool Graph::AddEdge(string src, string dest)
{   // 
   // First, lookup src vertex in Names array and obtain index S; if
   // not found, return false:
   //
   int y=0;
   int S=-1;
    
   while( y<this->NumVertices){
	    
      if (src==this->Names[y]){
		// cout << "found the Names array the starting" << this->Names[y]<< endl;
       S=y;
       break;  
      }
      
      ++y;
      
   }

      
   
   //
   // Second, lookup dest vertex in Names array and obtain index D, if
   // not found, return false:
   //
   y=0;
   int D=-1;
   while( y<this->NumVertices){
      if (dest==this->Names[y]){
       D=y;
       break;  
      }
      
      ++y;
      
   }
   

   
      Edge *e = new Edge();
      e->Src = S;
      e->Dest=D;
      e->Count=0;
      //update for alphabetical
      Edge *curr=new Edge();
      Edge *prev=new Edge();
      prev=nullptr;
      curr=this->Vertices[S];
      
      while(curr!=nullptr){
      if (e->Dest<curr->Dest){
         break;
      } 
      
        
      prev=curr;
      curr= curr->Next ;
      }
	  
      if (prev==nullptr){
          e->Next=this->Vertices[S];
       this->Vertices[S]=e; 
		++e->Count;
      
      }
      else{
      prev->Next=e;
      e->Next=curr;
		++e->Count;
	
      }
      
      
      
      this->NumEdges++;
//cout << "num edges" << this->NumEdges << endl;
     
     return true;
   }
bool Graph::AddVertex(string  v)
{
   if (this->NumVertices==this->Capacity){
      return false;
   }
   //
   // if the graph is "full", i.e. cannot hold more vertices,
   // then return false:
   //
   // TODO #1
   //
   
   int y=0;
   while (y<this->NumVertices){
      if(this->Names[y]==v){
       return false;  
         
      }
      ++y;
      
   }
   //
   // if the vertex name already exists in the graph,
   // then return false.  To determine, perform a linear
   // search of the Names array; note that in C++ you
   // compare strings using ==, no strcmp needed:
   //



   //
   // there's room to add another vertex, so grab next index
   // and initialize that linked-list to empty, and store
   // vertex's name:
   
   int i = this->NumVertices;

   this->Vertices[i] = nullptr;  // head of LL: null
   this->Names[i] = v;           // copy vertex string:

   this->NumVertices++;
   return true;
}
int Graph::GetNumVertices(){
	
	
	return this->NumVertices;
	
}
int Graph::GetNumEdges(){
	
	return this->NumEdges;
	
}

int Graph::DoesEdgeExist(string fromID, string toID){
	 int y=0;
	int S=-1;
	while( y<this->NumVertices){
	
    
      if (fromID==this->Names[y]){
		// cout << "found the Names array the starting" << this->Names[y]<< endl;
       S=y;
       break;  
      }
      
      ++y;
      
   }

      
   
   //
   // Second, lookup dest vertex in Names array and obtain index D, if
   // not found, return false:
   //
   y=0;
   int D=-1;
   while( y<this->NumVertices){
      if (toID==this->Names[y]){
       D=y;
       break;  
      }
      
      ++y;
      
   }
   

   
	Edge *curr=new Edge();
  
	  curr=this->Vertices[S];
	  
   while(curr!=nullptr){
	  
	   if (curr->Dest==D){
		   ++curr->Count;
		  // cout << "count because its repeated" << curr->Count << endl;
		   return 1;
	   }
     
      
     curr=curr->Next;
      
   }
   
   

	return 0;
	
	
}
void Graph::GetInfo(string station, vector<Station>& stations){
	int y=0;
	int ID;
	int total=0;
	int count_total=0;
	while (y<this->NumVertices){
      if(this->Names[y]==station){
       break;  
         
      }
      ++y;
      
   }
	Edge *curr=new Edge();
  
	  curr=this->Vertices[y];
	   while (curr!=nullptr){
		++count_total; 
		total=total+curr->Count;	
		  curr=curr->Next;
	  }
	  cout <<"# of destination stations:"<< count_total << endl;
	  cout <<"# of trips to those stations:"<< total << endl;

		
	
	
}

void Graph::Trip_Function(string from,string to){
	
	int y=0;
	int S=-1;
	int D=-1;
	while (y<this->NumVertices){
      if(this->Names[y]==from){
       S=y;
         
      }
	  if (this->Names[y]==to){
		  D=y;
		  
	  }
      ++y;
      
   }

	if (D==-1 || S==-1){
			cout <<"does not exit" << endl;
			return;
	}
	Edge *curr=new Edge();
	curr=this->Vertices[S];
	
	while (curr!=nullptr){
		
		
		if (curr->Dest==D){
				cout <<from<<"->"<<to << endl;
			  cout <<"# of trips:"<< curr->Count << endl;
			  return;
		}
		curr=curr->Next;
	}
	cout <<"# of trips:" << 0<< endl;
	
}
//Neighbors function
set<int> Graph::Neighbors(int N){
   set<int> neigh;
  
    Edge* curr= new Edge();
   curr=this->Vertices[N];
   while (curr!=nullptr){
      neigh.insert(curr->Dest);
      curr=curr->Next;
   }

      return neigh;
      
    
 
   
}
set<string> Graph::GetNeighbors(string v)
{
  set<string>  neighbors;
int y=0;
int Z;
 while(y<this->NumVertices){
    if (v==this->Names[y]){
       Z=y;
       break;
    }
   ++y;
 }
 Edge* curr= new Edge();
 curr=this->Vertices[Z];
 
 while(curr!=nullptr){
 neighbors.insert(this->Names[curr->Dest]);
 //cout << neighbors.insert(this->Names[curr->Dest]) << endl;
  curr=curr->Next;
 }
 
 
 
  return neighbors;
}
int Graph::GetEdgeWeights(string src, string dest)
{int y=0;
int Z=0;
   vector<int> weights;
   while (y<NumVertices){
      if (src==this->Names[y]){
         Z=y;
         break;
      }
      ++y;
   }
   
   
   y=0;
   int T=0;
   while(y<NumVertices){
      if (dest==this->Names[y]){
       T=y;  
      break;
      }
   ++y;
   }

   Edge* curr= new Edge();
 curr=this->Vertices[Z];
   while (curr!=nullptr){
    if (curr->Dest==T){
       return curr->Count;
		
    }
    curr=curr->Next;
   }
   return 0;
}
///BFS Function
vector<string> Graph::BFS(string v){
   
   vector <string>  visited;
   queue<int>    frontierQueue;
   set<int>   discoveredSet;
   set<int> neighbors;
   int currentV;
   set<int> N_set;
   int start=-1;
	  
	int y=0;
   while (y<this->NumVertices){
      if(this->Names[y]==v){
       start=y;
         
      }
	 ++y;
   }  
 cout <<"string"  << start << endl;
  if (start<0){ 
return visited;
   }
   
      frontierQueue.push(start);
   discoveredSet.insert(start);
   while(!frontierQueue.empty()){
     currentV= frontierQueue.front();
    frontierQueue.pop();
   
      visited.push_back(this->Names[currentV]);
       
     N_set=Neighbors(currentV);
     for (int e : N_set){
if ( discoveredSet.find(e) == discoveredSet.end() ){ // not found:
discoveredSet.insert(e);
frontierQueue.push(e);
}

  }
     
      
  }
   

	
	
   return visited;
}



//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
  cout << ">>Graph: " << title << endl;
  cout << "  # of vertices: " << this->NumVertices << endl;
  cout << "  # of edges:    " << this->NumEdges << endl;
  cout << "  Capacity:      " << this->Capacity << endl;

  cout << "  Vertices:" << endl;

  for (int v = 0; v < this->NumVertices; ++v)
  {
    cout << "    " << v << " (" << this->Names[v] << "): ";

    Edge *edge = this->Vertices[v];
    while (edge != nullptr)
    {
      cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Count << ")";

      edge = edge->Next;
      if (edge != nullptr)
        cout << ", ";
    }

    cout << endl;
  }
}
