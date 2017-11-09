#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <algorithm>
#include <utility>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <sys/time.h>

#include "Util.h"


using namespace std;
//using namespace __gnu_cxx;

typedef map<int,vector<int> > HashMap;


class Vertex {
public:
/*
	bool fat;	// fat node
	int path_id;	// path id
	int dfs_order;
	int pre_order;	
	int post_order;
	int first_visit;
    int lowestTopoNeigh;// for test
*/
	uint16_t layer;
	int topoID;	// topological order
	int indegree;
	int outdegree;
//	int id;

	Vertex(){
		layer=0;
		indegree=0;
		outdegree=0;
		topoID=0;
//		id=INT_MAX;
	}
};

typedef vector<int> EdgeList;	// edge list represented by vertex id list
typedef vector<Vertex> VertexList;	// vertices list (store real vertex property) indexing by id

class In_OutList {
public:
	EdgeList inList;
	EdgeList outList;

	bool operator==(const In_OutList& right){
		if(VectorEq(this->inList, right.inList)&&VectorEq(this->outList, right.outList))
			return true;

		return false;
	}

	bool operator!=(const In_OutList& right){
		if(VectorEq(this->inList, right.inList)&&VectorEq(this->outList, right.outList))
			return false;

		return true;
	}
};

typedef vector<In_OutList> GRA;	// index graph

class ReachIndex{
public:
	uint16_t layerup;
	uint16_t layerdown;
	uint8_t OutLimit;
	uint8_t InLimit;
	uint8_t HLimit;
	int* Label;

	ReachIndex(){
		Label=NULL;
	}

	~ReachIndex(){
		if(Label!=NULL)
			delete[] Label;
	}
};

class Graph{
	public:
		int KEYNUM;
		int HUGENODENUM;
		int hugenode;
		int vsize;
		string name;
		VertexList vl;
		GRA graph;
		vector<int> TopoOrder;

		vector< vector<int> > ProLabelOut;
		vector< vector<int> > ProLabelIn;
		vector<ReachIndex> reachindex;
	
		Graph();
		Graph(int);
		Graph(GRA&, VertexList&);
		Graph(istream&);
		Graph(const Graph& g);
		~Graph();
		void readGraph(istream&);
		void readGraph2(istream&);
		void readGraph3(istream&);
//               void readGraphFromInlist(istream& in);
		void writeGraph(ostream&,int i);
                void writeGraph(ostream& out);
		void printGraph(int i,ostream& out);
                void printGraph(int i);
		void addVertex(int);
		void addEdge(int, int);
		int num_vertices();
		int num_edges();
		VertexList& vertices();
		EdgeList& out_edges(int);
		EdgeList& in_edges(int);
                void sortEdges();
                vector<int> getRoots();
		vector<int> getTails();
		bool hasEdge(int, int);	
		Graph& operator=(const Graph&);
		Vertex& operator[](const int);
		
		void clear();
		void strTrimRight(string& str);

		string getFilename();
		void setFilename(string name);
		static vector<string> split(const string &s, char delim);
		static vector<string>& split(const string &s, char delim, vector<string> &elems);
		void RandomDAGGenerator(int n, int m, const string& filename);

		vector<uint16_t> layerdown;
		vector<uint16_t> layerup;
		void layerSeparation();
		void ComputeLayerLabel();
		void reverseLayerSeparation();
		void countIndegree () const;
		void checkLayerSeparation();
		void checkReverseLayerSeparation();
		void BFS(const int root=-1);
public:
		int FindStructureEq(vector<bool>& SEflag);
		void PrintMapGraph(const string& filename);
		void PrintReOrderedGraph(const vector<int>& order);
		void PrintReOrderedGraph2(const vector<int>& order);

		unsigned int BFSQuery(const unsigned int u, const unsigned int v);
		unsigned int BFSSubQuery(set<unsigned int>& qvertice, const unsigned int v, unsigned int depth, vector<bool>& flag);
		void ComputeOutSet(const unsigned int u, set<unsigned int>& out);
		void ComputeInSet(const unsigned int v, set<unsigned int>& in);

		void InitialProLabel();
		void ComputeProLabelOut();
		void ComputeProLabelIn();
		void VectorUnion(vector<int>& v1, const vector<int>& v2);
private:
		void SubComputeProLabelOut(int u);
		void SubComputeProLabelIn(int v);
public:
		void PrintIndex(const string& filename);
		void ReadIndex(const string& filename);

		vector< vector<int> > HugeNodeList;
		void ComputeHugeNodeList();
private:
		void HugeNodeListUnion(vector<int>& v1, const vector<int>& v2);
public:
		bool ProLabelQueryDFS2(const int u, const int v);
		void IndexQueryTest(const string& indexfilename, const string& queryfilename);
		bool IsContradict(vector<int>& v1, vector<int>& v2);
		bool IPtest(const int u, const int v);
};

class TopoComparison{
	bool less;
public:
	TopoComparison(const bool revparam = true){
		less = revparam;
	}

	bool operator()(const Vertex& u, const Vertex& v){
		if (less){
			if (u.topoID < v.topoID)
				return true;
			else
				return false;
		}else{
			if (u.topoID > v.topoID)
				return true;
			else
				return false;
		}
	}
};

class EdgeSort{
	int origin;
public:
	EdgeSort(const int input=0){
		origin=input;
	}

	bool operator()(int i, int j){
		if(abs(i-origin)<abs(j-origin))
			return true;
		else
			return false;
	}
};

#endif

