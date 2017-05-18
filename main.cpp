/*main.cpp*/
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
 
#include "graph.h"
 #include "graph.cpp"
using namespace std;
 
#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:
 
 
//
// Defines a Divvy Station:
//

 
 
//
// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
  string line;
  vector<Station> V;
 
  ifstream input(filename);
  if (!input.good())  // failed to open:
    return V;
 
  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data
 
  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);
 
    // format:
    //   id,name,latitude,longitude,dpcapacity,online_date
    //   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
    //   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
    //
    string  stationID, name, latitude, longitude, capacity;
 
    //
    // parse the line:
    //
    getline(ss, stationID, ',');
    getline(ss, name, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    getline(ss, capacity, ',');
 
    //
    // Create a new station object:
    //
    Station S(name, 
      stoi(stationID), 
      stod(latitude), 
      stod(longitude), 
      stoi(capacity));
 
     
 
    //
    // TODO:
    //   1. add station object to vector
	V.push_back(S);
	
	 //cout << "Structure"<< S.ID << endl;
	G.AddVertex(S.Name);
	
    //   2. add vertex to graph
    //
 
 
 
    getline(input, line);
  }
 
  return V;
}
 
 
//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the 
// function are returned back.  The vector of stations is needed so that 
// station ids can be mapped to names; it is passed by reference only for 
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
  string line;
 
  ifstream input(filename);
  if (!input.good())  // failed to open:
    return;
 
  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data
 
  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);
 
    // format:
    //   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
    //   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
    //
    string  tripID, fromID, toID, skip,to_string,from_string;
 
    //
    // parse the input line:
    //
    getline(ss, tripID, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, fromID, ',');
    getline(ss, skip, ',');
    getline(ss, toID, ',');
    getline(ss, skip, ',');
 //cout << "trips" << tripID << fromID << toID << endl;
    //
    // NOTE: don't trust the names in the trips file, not always accurate.  Trust the 
    // from and to station ids, and then lookup in our vector of stations:
 
  for (auto s : stations)
    {
      if (s.ID== stoi(fromID)){
		  from_string=s.Name;
		  
		   
	  }
	   if (s.ID==stoi(toID)){
		  to_string=s.Name;
		
	  }
	  
	  
    }
	
    //
    // TODO:
    //  - add new edge or update existing edge for this trip
    //
	 //cout << "trips" <<","<< stoi(fromID)<< "," << stoi(toID) << endl;
	 //cout<< "trips with names"<<from_string<<","<<to_string<< endl;
	int exit=G.DoesEdgeExist(from_string,to_string);
	
	if (exit==0){
			// cout << "entered adding a new edge" << endl;
		 G.AddEdge(from_string,to_string);
		
	}
	
	
 
   
    getline(input, line);
  }
}
 
 
//
// getFileName: 
//
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be 
// opened, an error message is output and the program is exited.
//
string getFileName()
{
  string filename;
 
  // input filename from the keyboard:
  getline(cin, filename);
 
  // make sure filename exists and can be opened:
  ifstream file(filename);
  if (!file.good()) 
  {
    cout << "**Error: unable to open '" << filename << "'" << endl << endl;
    std::terminate();
  }
 
  return filename;
}
 
 
int main()
{
  int    N = 1000;
  Graph  DivvyGraph(N);
 
  cout << "** Divvy Graph Analysis **" << endl;
 
  string stationsFilename = getFileName();
  string tripsFilename = getFileName();
 
  vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
  ProcessTrips(tripsFilename, DivvyGraph, stations);
   
  cout << ">> Graph:" << endl;
  cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
  cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
  //cout << ">> Ready:" << endl;
 
  string cmd;
  int    fromID, toID;
 
  cout << ">> ";
  cin >> cmd;
 
  while (cmd != "exit")
  {
    if (cmd == "info")
    {string from_string;
	int ID;
      cin >> fromID;
	  for (auto s : stations)
    {
      if (s.ID== fromID){
		  cout<<s.Name<<endl;
		
		 cout <<"(" << s.Latitude<< ","<< s.Longitude <<")" << endl; 
		cout <<"Capacity:"<< s.Capacity << endl;
	  }
	 

	  
    }
	set<string> text;
	int found=0;
	for (auto s : stations)
    {
		
      if (s.ID== fromID){
		  from_string=s.Name;
		  ID=s.ID;
		  found =1;
		  break;
	  }

	}
	
	if (found==0){
		cout<<"** No such station..."<<endl;
		
	}
	else{
		
	set <string> text;	
	DivvyGraph.GetInfo(from_string,stations);
	text=DivvyGraph.GetNeighbors(from_string);
	 for (auto v : text){
			for (auto s : stations){
				if (v== s.Name){
		 
				ID=s.ID;
					break;
				}
			}
		cout<<  v <<"("<<ID<< ")"<<":"<<DivvyGraph.GetEdgeWeights(from_string, v) << endl; 	
	 } 
	  
	}
 
    }
    else if (cmd == "trips")
    { string from_string;
	string to_string;
      cin >> fromID; 
      cin >> toID;
	   for (auto s : stations)
    {
      if (s.ID== fromID){
		  from_string=s.Name;
		  
		   
	  }
	   if (s.ID==toID){
		  to_string=s.Name;
		
	  }

	  
    }
	cout<<from_string<<"->"<<to_string<< endl;
	cout<<DivvyGraph.GetEdgeWeights(from_string,to_string)<<endl;

    }
    else if (cmd == "bfs")
    {	vector<string> Output;
	string from_string;
	cin >> fromID;
	for (auto s : stations){
		if (s.ID== fromID){
		  from_string=s.Name;
		  
		   
		}
	}
		cout << from_string<< endl;
	Output=DivvyGraph.BFS(from_string);
	cout << "im here"<< endl;
	
	for (auto e : Output){
		
		for (auto s : stations){
			if (e==s.Name){
				cout << s.ID << endl;
				
			}
			
		}
		
	}
		
		
		
		
    }
    else if (cmd == "debug")
    {
      DivvyGraph.PrintGraph("Divvy Graph");
    }
    else
    {
      cout << "**Invalid command, try again..." << endl;
    }
 
    cout << ">> ";
    cin >> cmd;
  }
 
  cout << "**Done**" << endl;
  return 0;
}