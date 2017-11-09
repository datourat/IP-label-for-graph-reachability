#ifndef GRAPH_CPP_
#define GRAPH_CPP_

#include "Graph.h"

int* flag;
int querycnt;

Graph::Graph() {
	graph = GRA();
	vl = VertexList();
	vsize=0;
}

Graph::Graph(int size) {
	vsize = size;
	vl = VertexList(size);
	graph = GRA(size, In_OutList());
}

Graph::Graph(GRA& g, VertexList& vlist) {
	vsize = vlist.size();
	graph = g;
	vl = vlist;
}

Graph::Graph(istream& in) {
	readGraph(in);
}

Graph::~Graph() {}

void Graph::printGraph(int i,ostream& out) {
	writeGraph(out,i);
}

void Graph::printGraph(int i) {
	writeGraph(cout,i);
}

void Graph::clear() {
	vsize = 0;
	graph.clear();
	vl.clear();
	TopoOrder.clear();
}

void Graph::strTrimRight(string& str) {
	string whitespaces(" \t\r\n");
	int index = str.find_last_not_of(whitespaces);
	if (index != string::npos) 
		str.erase(index+1);
	else
		str.clear();
}

void Graph::readGraph(istream& in) {
	string buf;
	getline(in, buf);

	strTrimRight(buf);
	if (buf != "graph_for_greach") {
		cout << "BAD FILE FORMAT!" << endl;
	//	exit(0);
	}
	
	int n;
	getline(in, buf);
	istringstream(buf) >> n;
	// initialize
	vsize = n;
	vl = VertexList(n, Vertex());
	graph = GRA(n, In_OutList());	
/*
	for (int i = 0; i < n; i++)
		addVertex(i);
*/
//	for(int i=0; i<vsize; i++)
//		vl[i].id=i;

	int begin, end;
	int sid, tid;
	vector<string> neighbors;
	while (getline(in, buf)) {
//		istringstream(buf) >> sid;
		begin = buf.find(":");
		end = buf.find_last_of("#");
		sid = atoi((buf.substr(0, begin)).c_str());
		buf = buf.substr(begin+2,end-begin-2);
		split(buf, ' ', neighbors);
		vl[sid].outdegree=neighbors.size();
		graph[sid].outList.reserve(vl[sid].outdegree);
		for (int i = 0; i < neighbors.size(); i++) {
			tid = atoi(neighbors[i].c_str());
			addEdge(sid,tid);
			vl[tid].indegree++;
		}
		neighbors.clear();
	}
}


void Graph::readGraph2(istream& in) {
	string line;
	int u, v;
	vector<string> edge;

	while(in.eof()!=true){
		getline(in, line);
		if(line!=""){
			edge.clear();
			split(line, '\t', edge);
			if(edge.size()!=2){
				cout << "Input File Error" << endl;
				quit();
			}
//			if(atoi(edge[0].c_str()) < 2004)
//				continue;
			u=atoi(edge[0].c_str());
			v=atoi(edge[1].c_str());
			addEdge(u, v);
			vl[u].outdegree++;
			vl[v].indegree++;
		}
		line.clear();
	}

//	for(int i=0; i<vsize; i++)
//		vl[i].id=i;
}

void Graph::readGraph3(istream& in) {
        string buf;
        int n;

        getline(in, buf);
        istringstream(buf) >> n;
        // initialize
        vsize = n;
        vl = VertexList(n, Vertex());
        graph = GRA(n, In_OutList());
/*
        for (int i = 0; i < n; i++)
                addVertex(i);
*/
//	for(int i=0; i<vsize; i++)
//		vl[i].id=i;

        int begin, end;
        int sid, tid;
        vector<string> neighbors;
        while (getline(in, buf)) {
//              istringstream(buf) >> sid;
                begin = buf.find(" ");
                end = buf.find_last_of("-");
                sid = atoi((buf.substr(0, begin)).c_str());
                buf = buf.substr(begin+2,end-begin-2);
                split(buf, ' ', neighbors);
                vl[sid].outdegree=neighbors.size();
                graph[sid].outList.reserve(vl[sid].outdegree);
                for (int i = 0; i < neighbors.size(); i++) {
                        tid = atoi(neighbors[i].c_str());
                        addEdge(sid,tid);
                        vl[tid].indegree++;
                }
                neighbors.clear();
        }
}

/*
void Graph::readGraphFromInlist(istream& in) {
	string buf;
	getline(in, buf);

	strTrimRight(buf);
	if (buf != "graph_for_greach") {
		cout << "BAD FILE FORMAT!" << endl;
	//	exit(0);
	}
	
	int n;
	getline(in, buf);
	istringstream(buf) >> n;
	// initialize
	vsize = n;
	vl = VertexList(n);
	graph = GRA(n, In_OutList());	

	for (int i = 0; i < n; i++)
		addVertex(i);

	string sub;
	int idx;
	int sid = 0;
	int tid = 0;
        
        while (getline(in, buf)) {
            strTrimRight(buf);
            idx = buf.find(":");
            buf.erase(0, idx+2);
            while (buf.find(" ") != string::npos) {
                 sub = buf.substr(0, buf.find(" "));
                 istringstream(sub) >> tid;
                 buf.erase(0, buf.find(" ")+1);
                 addEdge(tid, sid);
            }
            ++sid;
         }
        
}
*/


void Graph::writeGraph(ostream& out,int j) {
	cout << "Write graph size = " << graph.size() << endl;
	out << "graph_for_greach" << endl;
	out << vl.size() << endl;

	GRA::iterator git;
	EdgeList el;
	EdgeList::iterator eit;
	VertexList::iterator vit;
	int i = 0;
	for (i = 0; i < vl.size(); i++) {
		out << i << ": ";
                if(j==1)        
                    el = graph[i].outList;
                else
                    el = graph[i].inList;
		for (eit = el.begin(); eit != el.end(); eit++)
			out << (*eit) << " ";
		out << "#" << endl;
	}
}

void Graph::writeGraph(ostream& out) {
	cout << "Graph size = " << graph.size() << endl;
	out << "graph_for_greach" << endl;
	out << vl.size() << endl;

	GRA::iterator git;
	EdgeList el;
	EdgeList::iterator eit;
	VertexList::iterator vit;
	int i = 0;
	for (i = 0; i < vl.size(); i++) {
		out << i << ": ";
		el = graph[i].outList;
		for (eit = el.begin(); eit != el.end(); eit++)
			out << (*eit) << " ";
		out << "#" << endl;
	}
}

vector<string>& Graph::split(const string &s, char delim, vector<string> &elems) {
	int begin, end;

	begin=0;
	end=s.find(delim);
	while(end!=string::npos){
		elems.push_back(s.substr(begin, end-begin));
		begin=end+1;
		end=s.find(delim, begin);
	}
	if(begin!=s.size()){
		elems.push_back(s.substr(begin));
	}

	return elems;
}

vector<string> Graph::split(const string &s, char delim) {
	vector<string> elems;
	return split(s, delim, elems);
}

void Graph::sortEdges() {
	GRA::iterator git;
	for (git = graph.begin(); git != graph.end(); git++) {
		sort(git->inList.begin(), git->inList.end());
		sort(git->outList.begin(), git->outList.end());
	}	
}

void Graph::addVertex(int vid) {
	if (vid >= vl.size()) {
		int size = vl.size();
		for (int i = 0; i < (vid-size+1); i++) {
			graph.push_back(In_OutList());
			vl.push_back(Vertex());
		}
		vsize = vl.size();
	}

	Vertex v;
	vl[vid] = v;

	EdgeList il = EdgeList();
	EdgeList ol = EdgeList();
	In_OutList oil = In_OutList();
	oil.inList = il;
	oil.outList = ol;
	graph[vid] = oil;	
}

void Graph::addEdge(int sid, int tid) {
	if (sid >= vl.size())
		addVertex(sid);
	if (tid >= vl.size())
		addVertex(tid);
	// update edge list
	graph[tid].inList.push_back(sid);
	graph[sid].outList.push_back(tid);
}

int Graph::num_vertices() {
	return vl.size();
}

int Graph::num_edges() {
	EdgeList el;
	GRA::iterator git;
	int num = 0;
	for (git = graph.begin(); git != graph.end(); git++) {
		el = git->outList;
		num += el.size();
	}
	return num;
}

// return out edges of specified vertex
EdgeList& Graph::out_edges(int src) {
	return graph[src].outList;
}

// return in edges of specified vertex
EdgeList& Graph::in_edges(int trg) {
	return graph[trg].inList;
}

// get roots of graph (root is zero in_degree vertex)
vector<int> Graph::getRoots() {
	vector<int> roots;

	for(int i=0; i<vsize; i++){
		if(vl[i].indegree==0)
			roots.push_back(i);
	}
	
	return roots;
}

vector<int> Graph::getTails(){
	vector<int> tails;

	for(int i=0; i<vsize; i++){
		if(vl[i].outdegree==0)
			tails.push_back(i);
	}

	return tails;
}

// check whether the edge from src to trg is in the graph
bool Graph::hasEdge(int src, int trg) {
	EdgeList el = graph[src].outList;
	EdgeList::iterator ei;
	for (ei = el.begin(); ei != el.end(); ei++)
		if ((*ei) == trg)
			return true;
	return false;

}

// return vertex list of graph
VertexList& Graph::vertices() {
	return vl;
}

Graph::Graph(const Graph& g) {
	if (this != &g) {
		this->graph = g.graph;
		this->vl = g.vl;
		this->vsize = g.vsize;
		this->name=g.name;
	}
}

Graph& Graph::operator=(const Graph& g) {
	if (this != &g) {
		graph = g.graph;
		vl = g.vl;
		vsize = g.vsize;
		name=g.name;
	}
	return *this;
}

string Graph::getFilename(){
	return name;
}
void Graph::setFilename(string name){
	this->name.swap(name);
}
// get a specified vertex property
Vertex& Graph::operator[](const int vid) {
	return vl[vid];
}


void Graph::RandomDAGGenerator(int n, int m, const string& filename){
	int i=0;
	int u, v;

	vsize = n;
	vl = VertexList(n, Vertex());
	graph = GRA(n, In_OutList());

	set< pair<int, int> > tmpset;

	for(int i=0; i<m; i++){
		u=Rand64()%vsize;
		v=Rand64()%vsize;

		if(u==v){
			i--;
			continue;
		}
		if(u>v)
			swap(u, v);

		if(tmpset.find(make_pair(u, v))==tmpset.end()){
			addEdge(u,v);
			tmpset.insert(make_pair(u, v));
		}
		else{
			i--;
			continue;
		}
	}

	int count=0;
	for(int u=0; u<vsize; u++){
		sort(graph[u].outList.begin(), graph[u].outList.end());
		count+=graph[u].outList.size();
		for(int j=0; j+1<graph[u].outList.size(); j++){
			if(graph[u].outList[j]==graph[u].outList[j+1]){
				cout << "redundant edges" << endl;
				quit();
			}
		}
	}

	cout << "Number of edges: " << count << endl;

	ofstream output(filename.c_str());
	writeGraph(output);
	output.close();
}


void Graph::layerSeparation(){
	int i, k;
	int u,v;
	vector<int> indegreeRecord(vsize);
	uint16_t layer=1;
	int vectorsize, tmpsize;

	TopoOrder.resize(vsize);

	k=0;
	for(i=0; i<vsize; i++){
		indegreeRecord[i]=vl[i].indegree;
		if(indegreeRecord[i]==0){
			TopoOrder[k]=i;
			vl[i].topoID =k;
			vl[i].layer=layer;
			k++;
		}
	}


	bool flag=true;
	i=0;
	vectorsize=k;
	while(flag){
		flag=false;
		layer++;
		for(; i<vectorsize; i++){
			u=TopoOrder[i];
			tmpsize=graph[u].outList.size();
			for(int j=0; j<tmpsize; j++){
				v=graph[u].outList[j];
				indegreeRecord[v]--;
				if(indegreeRecord[v]==0){
					flag=true;
					TopoOrder[k]=v;
					vl[v].topoID=k;
					vl[v].layer=layer;
					k++;
				}
			}
		}
		vectorsize=k;
	}


	if(TopoOrder.size()!=vsize){
		cout << "Topology Order Computation Error" << endl;
		quit();
	}

}


void Graph::ComputeLayerLabel(){
	int i, k;
	int u,v;
	vector<int> indegreeRecord(vsize);
	uint16_t layer=1;
	int vectorsize, tmpsize;

	TopoOrder.resize(vsize);
	vector<uint16_t>(vsize).swap(layerdown);

	k=0;
	for(i=0; i<vsize; i++){
		indegreeRecord[i]=vl[i].indegree;
		if(indegreeRecord[i]==0){
			TopoOrder[k]=i;
			layerdown[i]=layer;
			k++;
		}
	}


	bool flag=true;
	i=0;
	vectorsize=k;
	while(flag){
		flag=false;
		layer++;
		for(; i<vectorsize; i++){
			u=TopoOrder[i];
			tmpsize=graph[u].outList.size();
			for(int j=0; j<tmpsize; j++){
				v=graph[u].outList[j];
				indegreeRecord[v]--;
				if(indegreeRecord[v]==0){
					TopoOrder[k]=v;
					layerdown[v]=layer;
					k++;
				}
			}
		}

		if(vectorsize!=k){
			vectorsize=k;
			flag=true;
		}
	}

	uint16_t tmp;
	vector<uint16_t>(vsize).swap(layerup);
	for(int i=vsize-1; i>=0; i--){
		u=TopoOrder[i];
		tmp=0;
		for(vector<int>::iterator it=graph[u].outList.begin(); it!=graph[u].outList.end(); it++){
			if( layerup[*it] > tmp){
				tmp = layerup[*it];
			}
		}
		layerup[u]=tmp+1;
	}
}


void Graph::reverseLayerSeparation(){


	int i;
	int u,v;
	vector<int> degreezero;
	vector<int> degreezeroNext;
	vector<int> outdegreeRecord(vsize, 0);
	uint16_t layer=1;
	int vectorsize, tmpsize;

	for(i=0; i<vsize; i++){
		outdegreeRecord[i]=vl[i].outdegree;
		if(outdegreeRecord[i]==0){
			degreezero.push_back(i);
			vl[i].layer=layer;
		}
	}

	while(vectorsize=degreezero.size()){
//		output << layer << ":\t" << degreezero.size() << endl;

//		output << layer << "(" << degreezero.size() << ")\t:";

		layer++;
		for(i=0; i<vectorsize; i++){
			u=degreezero[i];
			tmpsize=graph[u].inList.size();
//			output << u << " ";
			for(int j=0;j<tmpsize;j++){
				v=graph[u].inList[j];
				outdegreeRecord[v]--;
				if(outdegreeRecord[v]==0){
					degreezeroNext.push_back(v);
					vl[v].layer=layer;
				}
			}
		}
//		output << endl;
		degreezero=degreezeroNext;
		degreezeroNext.clear();
	}
	
//	output.close();
//	output.close();

}

void Graph::countIndegree() const {
	vector<int> count(100, 0);
	int i;
	string name="data\\"+name+"_count.txt";

	for(i=0; i<vsize; i++){
		if(vl[i].indegree<100){
			count[vl[i].indegree]++;
		}else
			count[99]++;
	}

	ofstream output(name.c_str());
	for(i=0;i<100;i++){
		output << count[i] << endl;
	}

	output.close();
}

void Graph::checkLayerSeparation(){
	int u,v;
	bool flag=false;

	for (u=0; u<vsize; u++){
		for(int j=0; j<graph[u].outList.size(); j++){
			v=graph[u].outList[j];
			if(vl[v].layer<=vl[u].layer || vl[v].topoID <= vl[u].topoID ){
				cout << " checkLayerSeparation: Error" << endl;
				quit();
			}
		}

		for (int j=0; j<graph[u].inList.size(); j++){
			v=graph[u].inList[j];
			if(vl[u].layer-vl[v].layer==1)
				flag=true;
		}
		if(flag||graph[u].inList.size()==0)
			flag=false;
		else{
			cout << " checkLayerSeparation: No good separation" << endl;
			quit();
		}
	}
}

void Graph::checkReverseLayerSeparation(){
	int u,v;
	bool flag=false;

	for (u=0; u<vsize; u++){
		for(int j=0; j<graph[u].inList.size(); j++){
			v=graph[u].inList[j];
			if(vl[v].layer<=vl[u].layer){
				cout << " checkLayerSeparation: Error" << endl;
				quit();
			}
		}

		for (int j=0; j<graph[u].outList.size(); j++){
			v=graph[u].outList[j];
			if(vl[u].layer-vl[v].layer==1)
				flag=true;
		}
		if(flag||graph[u].outList.size()==0)
			flag=false;
		else{
			cout << " checkLayerSeparation: No good separation" << endl;
			quit();
		}
	}
}

void Graph::BFS(const int root){
	queue<int> que;
	vector<bool> BFSflag(vsize, false);
	vector<bool> QueFlag(vsize, false);
	int now;

	if(root<-1){
		cout << "BFS Input Error: " << root << endl;
		return;
	}

	if(root==-1){
		for(int i=0; i<vsize; i++){
			if(vl[i].indegree==0){
				que.push(i);
				QueFlag[i]=true;
			}
		}
	}else{
		BFSflag[root]=true;
		for(int i=0; i<graph[root].outList.size(); i++){
			if(BFSflag[graph[root].outList[i]]==false){
				que.push(graph[root].outList[i]);
				QueFlag[graph[root].outList[i]]=true;
			}
		}
	}

	while(que.empty()==false){
		now=que.front();
		que.pop();

		BFSflag[now]=true;
		for(int i=0; i<graph[now].outList.size(); i++){
			if((BFSflag[graph[now].outList[i]]==false)&&(QueFlag[graph[now].outList[i]]==false)){
				que.push(graph[now].outList[i]);
				QueFlag[graph[now].outList[i]]=true;
			}
		}
	}
}


int Graph::FindStructureEq(vector<bool>& SEflag){
	SEflag.clear();
	SEflag.resize(vsize,false);
	int secount=0;

	for(int i=0; i<vsize; i++){
		if(i%1000==0)
			cout << i << ": " << secount << endl;
		if(SEflag[i]==false){
			for(int j=i+1; j<vsize; j++){
				if(SEflag[j]==false){
					if(graph[i]==graph[j]){
						secount++;
						SEflag[j]=true;
					}
				}
			}
		}
	}

	return secount;
}

void Graph::PrintMapGraph(const string& filename){
	ofstream output(filename.c_str());
	if(output.is_open()==false){
		cout << filename << " is not found." << endl;
		quit();
	}
	
	vector<int> indexmap(vsize, 0);
	for(int i=0; i<vsize; i++){
		indexmap[i]=vl[i].topoID-1;
	}
	ofstream indexmapout((name+"_indexmap.txt").c_str());
	for(int i=0; i<vsize; i++){
		indexmapout << i << "\t" << indexmap[i] << endl;
	}
	indexmapout.close();

	vector< vector<int> > SortedGraph(vsize, vector<int>());
	int u, v;
	for(int i=0; i<vsize; i++){
		u=indexmap[i];
		for(int j=0; j<graph[i].outList.size(); j++){
			v=indexmap[graph[i].outList[j]];
			SortedGraph[u].push_back(v);
		}
	}

	output << "graph_for_greach" << endl;
	output << vsize << endl;
	for(int i=0; i<vsize; i++){
		output << i << ": ";
		for(int j=0; j<SortedGraph[i].size(); j++){
			output << SortedGraph[i][j] << " ";
		}
		output << "#" << endl;
	}


	output.close();
}


void Graph::PrintReOrderedGraph(const vector<int>& order){
	ofstream output((name+"_ReOrdered.gra").c_str());
	if(output.is_open()==false){
		cout << name+"_ReOrdered.gra" << " cannot be opened." << endl;
		quit();
	}

	vector< vector<int> > ReOrderedGraph(vsize, vector<int>());
	int u, v;
	for(int i=0; i<vsize; i++){
		u=order[i];
		for(int j=0; j<graph[i].outList.size(); j++){
			v=order[graph[i].outList[j]];
			ReOrderedGraph[u].push_back(v);
		}
	}

	for(int u=0; u<vsize; u++){
		sort(ReOrderedGraph[u].begin(), ReOrderedGraph[u].end());
	}

	output << "graph_for_greach" << endl;
	output << vsize << endl;
	for(int i=0; i<vsize; i++){
		output << i << ": ";
		for(int j=0; j<ReOrderedGraph[i].size(); j++){
			output << ReOrderedGraph[i][j] << " ";
		}
		output << "#" << endl;
	}


	output.close();
}

void Graph::PrintReOrderedGraph2(const vector<int>& order){
	ofstream output((name+"_ReOrdered.txt").c_str());
	if(output.is_open()==false){
		cout << name+"_ReOrdered.txt" << " cannot be opened." << endl;
		quit();
	}

	vector< vector<int> > ReOrderedGraph(vsize, vector<int>());
	int u, v;
	for(int i=0; i<vsize; i++){
		u=order[i];
		for(int j=0; j<graph[i].outList.size(); j++){
			v=order[graph[i].outList[j]];
			ReOrderedGraph[u].push_back(v);
		}
	}

	for(int u=0; u<vsize; u++){
		sort(ReOrderedGraph[u].begin(), ReOrderedGraph[u].end());
//		sort(ReOrderedGraph[u].begin(), ReOrderedGraph[u].end(),EdgeSort(u));
	}

	for(int i=0; i<vsize; i++){
		for(int j=0; j<ReOrderedGraph[i].size(); j++){
			output << i << "\t" << ReOrderedGraph[i][j] << endl;
		}
	}


	output.close();
}




unsigned int Graph::BFSQuery(const unsigned int u, const unsigned int v){
	if(u==v)
		return 0;

	vector<bool> flag(vsize, false);
	set<unsigned int> qvertice;
	unsigned int tmpv;

	flag[u]=true;
	for(int i=0; i<graph[u].outList.size(); i++){
		tmpv=graph[u].outList[i];
		qvertice.insert(tmpv);
	}

	return BFSSubQuery(qvertice, v, 1, flag);
}


unsigned int Graph::BFSSubQuery(set<unsigned int>& qvertice, const unsigned int v, unsigned int depth, vector<bool>& flag){
	unsigned int tmpu, tmpv;
	set<unsigned int> nextset;
	set<unsigned int>::iterator sit;

	if(qvertice.empty()){
		return INT_MAX;
	}

	for(sit=qvertice.begin(); sit!=qvertice.end(); sit++){
		tmpu=*sit;
		if(tmpu==v)
			return depth;
		flag[tmpu]=true;

		for(int i=0; i<graph[tmpu].outList.size(); i++){
			tmpv=graph[tmpu].outList[i];
			if(flag[tmpv]==false && nextset.find(tmpv)==nextset.end() ){
				nextset.insert(tmpv);
			}
		}
	}

	qvertice=nextset;
	nextset.clear();

	return BFSSubQuery(qvertice, v, depth+1, flag);
}

void Graph::ComputeOutSet(const unsigned int u, set<unsigned int>& out){
	unsigned int v;
	pair< set<unsigned int>::iterator, bool > flag;

	flag=out.insert(u);
	if(flag.second){
		for(int i=0; i<graph[u].outList.size(); i++){
			v=graph[u].outList[i];
			ComputeOutSet(v, out);
		}
	}
}



void Graph::ComputeInSet(const unsigned int v, set<unsigned int>& in){
	unsigned int u;
	pair< set<unsigned int>::iterator, bool > flag;

	flag=in.insert(v);
	if(flag.second){
		for(int i=0; i<graph[v].inList.size(); i++){
			u=graph[v].inList[i];
			ComputeInSet(u, in);
		}
	}
}

void Graph::InitialProLabel(){
	int i, j;

	srand(time(0));
	vector< vector<int> > (vsize).swap(ProLabelOut);

	for(int u=0; u<vsize; u++){
		ProLabelOut[u].push_back(u);
	}

	for(i=vsize-1; i>=1; i--){
		j=Rand64()%(i+1);
		swap(ProLabelOut[j][0], ProLabelOut[i][0]);
	}

	ProLabelIn=ProLabelOut;

}

void Graph::ComputeProLabelOut(){
	int u;
	unsigned int tmpsize;

	for(int i=vsize-1; i>=0; i--){
		u=TopoOrder[i];
		tmpsize=graph[u].outList.size();

		if(tmpsize==0){
			continue;
		}else if(tmpsize==1){
			VectorUnion(ProLabelOut[u], ProLabelOut[graph[u].outList[0]]);
		}else if(tmpsize==2){
			VectorUnion(ProLabelOut[u], ProLabelOut[graph[u].outList[0]]);
			VectorUnion(ProLabelOut[u], ProLabelOut[graph[u].outList[1]]);
		}else{
			SubComputeProLabelOut(u);
		}

	}

}


void Graph::ComputeProLabelIn(){
	int v;
	unsigned int tmpsize;

	for(int i=0; i<vsize; i++){
		v=TopoOrder[i];
		tmpsize=graph[v].inList.size();

		if(tmpsize==0){
			continue;
		}else if(tmpsize==1){
			VectorUnion(ProLabelIn[v], ProLabelIn[graph[v].inList[0]]);
		}else if(tmpsize==2){
			VectorUnion(ProLabelIn[v], ProLabelIn[graph[v].inList[0]]);
			VectorUnion(ProLabelIn[v], ProLabelIn[graph[v].inList[1]]);
		}else{
			SubComputeProLabelIn(v);
		}

	}
}

void Graph::VectorUnion(vector<int>& v1, const vector<int>& v2){
        unsigned int v1size=v1.size(), v2size=v2.size();

        if(v1[v1size-1] < v2[0]){
                if(v1size==KEYNUM)
                        return ;
                else{
                        if(v2.begin()+KEYNUM-v1size < v2.end())
                                v1.insert(v1.end(), v2.begin(), v2.begin()+KEYNUM-v1size);
                        else
                                v1.insert(v1.end(), v2.begin(), v2.end());
                        return ;
                }
        }

        if(v1size==1){
                int i=0;
                for(; i<v2size; i++){
                        if(v2[i] >= v1[0]){
                                break;
                        }
                }
                if(i<KEYNUM)
                        v1.insert(v1.begin(), v2.begin(), v2.begin()+i);
                else{
                        v1=v2;
                        return ;
                }
                while(i<v2size && v2[i]==v1[0]){
                        i++;
                }
                if(v2size==KEYNUM&&i<v2size)
                        v1.insert(v1.end(), v2.begin()+i, v2.begin()+KEYNUM-1);
                else
                        v1.insert(v1.end(), v2.begin()+i, v2.end());
                return ;
        }


        int k=0;
        unsigned int i=0, j=0;
        static vector<int> v(KEYNUM);
        v.clear();

        while(k<KEYNUM && i<v1size && j<v2size){
                if(v1[i]==v2[j]){
                        v.push_back(v1[i]);
                        k++;
                        i++;
                        j++;
                }else if(v1[i]<v2[j]){
                        v.push_back(v1[i]);
                        k++;
                        i++;
                }else{
                        v.push_back(v2[j]);
                        k++;
                        j++;
                }
        }

        if(k>=KEYNUM){
                v1=v;
                return;
        }

        if(i!=v1size){
                if(v1.end() < v1.begin()+i+KEYNUM-v.size())
                        v.insert(v.end(), v1.begin()+i, v1.end());
                else
                        v.insert(v.end(), v1.begin()+i, v1.begin()+i+KEYNUM-v.size());
//              for(; k<KEYNUM && i<v1size; i++, k++){
//                      v.push_back(v1[i]);
//              }
        }
        if(j!=v2size){
                if(v2.end() < v2.begin()+j+KEYNUM-v.size())
                        v.insert(v.end(), v2.begin()+j, v2.end());
                else
                        v.insert(v.end(), v2.begin()+j, v2.begin()+j+KEYNUM-v.size());
//              for(; k<KEYNUM && j<v2size; j++, k++){
//                      v.push_back(v2[j]);
//              }
        }

        v1=v;
}


void Graph::SubComputeProLabelOut(int u){
	int edgelistsize=graph[u].outList.size();
	int v;
	int tmpi;
	int tmpvalue;
	vector<int>::iterator tmpiter;
	static vector< vector<int>::iterator > iterend;
	static vector< pair<int, vector<int>::iterator> > iterlist;
	static vector<int> label(KEYNUM);

	label.clear();
	iterend.clear();
	iterlist.clear();

	iterlist.push_back(make_pair(0, ProLabelOut[u].begin()));
	iterend.push_back(ProLabelOut[u].end());
/*
	for(int i=0; i<edgelistsize; i++){
		v=graph[u].outList[i];
		iterlist.push_back( make_pair(i+1, ProLabelOut[v].begin()) );
		iterend.push_back(ProLabelOut[v].end());
	}
*/
	int i=1;
	for(vector<int>::iterator it=graph[u].outList.begin(); it!=graph[u].outList.end(); i++, it++){
		iterlist.push_back( make_pair(i, ProLabelOut[*it].begin()) );
		iterend.push_back( ProLabelOut[*it].end() );
	}

	int k=0;
	make_heap(iterlist.begin(), iterlist.end(), PairComparePointer<int, vector<int>::iterator> ());
	tmpi=iterlist.front().first;
	tmpiter=iterlist.front().second;
	label.push_back( *(tmpiter) );
	k++;
	tmpvalue=*tmpiter;
	pop_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
	tmpiter++;
	if(tmpiter==iterend[tmpi]){
		iterlist.pop_back();
	}else{
		iterlist[iterlist.size()-1].second=tmpiter;
		push_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
	}

	while(k<KEYNUM && iterlist.empty()==false){
		tmpi=iterlist.front().first;
		tmpiter=iterlist.front().second;
		if(tmpvalue < *tmpiter){
			label.push_back( *(tmpiter) );
			k++;
			tmpvalue=*tmpiter;
		}else if(tmpvalue > *tmpiter){
			cout << "Something must be wrong! " << endl;
			quit();
		}
		pop_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
		tmpiter++;
		if(tmpiter==iterend[tmpi]){
			iterlist.pop_back();
		}else{
			iterlist[iterlist.size()-1].second=tmpiter;
			push_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
		}
	}

	ProLabelOut[u]=label;
}


void Graph::SubComputeProLabelIn(int v){
	int edgelistsize=graph[v].inList.size();
	int u;
	int tmpi;
	int tmpvalue;
	vector<int>::iterator tmpiter;
	static vector< vector<int>::iterator > iterend;
	static vector< pair<int, vector<int>::iterator> > iterlist;
	static vector<int> label(KEYNUM);

	label.clear();
	iterend.clear();
	iterlist.clear();

	iterlist.push_back(make_pair(0, ProLabelIn[v].begin()));
	iterend.push_back(ProLabelIn[v].end());
/*
	for(int i=0; i<edgelistsize; i++){
		u=graph[v].inList[i];
		iterlist.push_back( make_pair(i+1, ProLabelIn[u].begin()) );
		iterend.push_back(ProLabelIn[u].end());
	}
*/
	int i=1;
	for(vector<int>::iterator it=graph[v].inList.begin(); it!=graph[v].inList.end(); i++, it++){
		iterlist.push_back( make_pair(i, ProLabelIn[*it].begin()) );
                iterend.push_back(ProLabelIn[*it].end());
	}

	int k=0;
	make_heap(iterlist.begin(), iterlist.end(), PairComparePointer<int, vector<int>::iterator> ());
	tmpi=iterlist.front().first;
	tmpiter=iterlist.front().second;
	label.push_back( *(tmpiter) );
	k++;
	tmpvalue=*tmpiter;
	pop_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
	tmpiter++;
	if(tmpiter==iterend[tmpi]){
		iterlist.pop_back();
	}else{
		iterlist[iterlist.size()-1].second=tmpiter;
		push_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
	}

	while(k<KEYNUM && iterlist.empty()==false){
		tmpi=iterlist.front().first;
		tmpiter=iterlist.front().second;
		if(tmpvalue < *tmpiter){
			label.push_back( *(tmpiter) );
			k++;
			tmpvalue=*tmpiter;
		}else if(tmpvalue > *tmpiter){
			cout << "Something must be wrong! " << endl;
			quit();
		}
		pop_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
		tmpiter++;
		if(tmpiter==iterend[tmpi]){
			iterlist.pop_back();
		}else{
			iterlist[iterlist.size()-1].second=tmpiter;
			push_heap(iterlist.begin(), iterlist.end(),  PairComparePointer<int, vector<int>::iterator> ());
		}
	}

	ProLabelIn[v]=label;
}


void Graph::PrintIndex(const string& filename){
	ofstream output(filename.c_str());

	if(output.is_open()==false){
		cout << "Fail to open " << filename << endl;
		quit();
	}

	output << hugenode << endl;

	for(int u=0; u<vsize; u++){
		output << u << ": ";
		for(int j=0; j<ProLabelOut[u].size(); j++){
			output << ProLabelOut[u][j] << ' ';
		}
		output << "# ";
		for(int j=0; j<ProLabelIn[u].size(); j++){
			output << ProLabelIn[u][j] << ' ';
		}
		output << "# ";
		for(int j=0; j<HugeNodeList[u].size(); j++){
			output << HugeNodeList[u][j] << ' ';
		}
		output << "# ";
		output << layerup[u] << ' ' << layerdown[u] << " #" << endl;
	}


	output.close();

}

void Graph::ReadIndex(const string& filename){
	ifstream in(filename.c_str());
	string buf, tmpbuf;
	if(in.is_open()==false){
		cout << "Cannot open " << filename << endl;
		quit();
	}
	reachindex.resize(vsize);
	getline(in, buf);
	istringstream(buf) >> hugenode;

	int begin, end;
	int u, v;
	vector<string> levellabel, outlabel, inlabel, hv;
	while (getline(in, buf)) {
		begin = buf.find(":");
		end = buf.find("#");
		u = atoi((buf.substr(0, begin)).c_str());

		tmpbuf = buf.substr(begin+2, end-begin-2);
		split(tmpbuf, ' ', outlabel);
		begin=end;
		end=buf.find('#', end+1);
		tmpbuf=buf.substr(begin+2, end-begin-2);
		split(tmpbuf, ' ', inlabel);
		begin=end;
		end=buf.find('#', end+1);
		tmpbuf=buf.substr(begin+2, end-begin-2);
		split(tmpbuf, ' ', hv);

		reachindex[u].OutLimit=outlabel.size();
		reachindex[u].InLimit=inlabel.size()+reachindex[u].OutLimit;
		reachindex[u].HLimit=hv.size()+reachindex[u].InLimit;
		reachindex[u].Label = new int[reachindex[u].HLimit];
		int labelit=0;
		for(int i=0; i<outlabel.size(); i++, labelit++){
			v = atoi(outlabel[i].c_str());
			reachindex[u].Label[labelit]=v;
		}
		for(int i=0; i<inlabel.size(); i++, labelit++){
			v = atoi(inlabel[i].c_str());
			reachindex[u].Label[labelit]=v;
		}
		for(int i=0; i<hv.size(); i++, labelit++){
			v = atoi(hv[i].c_str());
			reachindex[u].Label[labelit]=v;
		}
		if(labelit!=reachindex[u].HLimit)
			cout << "Index Input Error" << endl;
		outlabel.clear();
		inlabel.clear();
		hv.clear();
		begin=end;
		end=buf.find("#", end+1);
		tmpbuf = buf.substr(begin+2,end-begin-2);
		split(tmpbuf, ' ', levellabel);
		if(levellabel.size()!=2){
			cout << "Index file error" << endl;
			quit();
		}
		reachindex[u].layerup=atoi(levellabel[0].c_str());
		reachindex[u].layerdown=atoi(levellabel[1].c_str());
		levellabel.clear();
	}

	in.close();

}

void Graph::ComputeHugeNodeList(){
	vector< vector<int> > (vsize).swap(HugeNodeList);

	if(HUGENODENUM==0)
		return ;

	for(int i=0; i<vsize; i++){
		if(vl[i].outdegree > hugenode){
			HugeNodeList[i].push_back(i);
		}
	}

	int u, v;
	int tmpsize;

	for(int i=0; i<vsize; i++){
		v=TopoOrder[i];
		tmpsize=graph[v].inList.size();
		for(int j=0; j<tmpsize; j++){
			u=graph[v].inList[j];
			if(HugeNodeList[u].empty()==false){
				HugeNodeListUnion(HugeNodeList[v], HugeNodeList[u]);
			}
		}

	}

}


void Graph::HugeNodeListUnion(vector<int>& v1, const vector<int>& v2){
	int v1size=v1.size(), v2size=v2.size();

	if(v1size==0){
		v1=v2;
		return;
	}

	if(vl[v1[v1size-1]].outdegree > vl[v2[0]].outdegree){
		if(v1size==HUGENODENUM)
			return ;
		else{
			if(v2.begin()+HUGENODENUM-v1size < v2.end())
				v1.insert(v1.end(), v2.begin(), v2.begin()+HUGENODENUM-v1size);
			else
				v1.insert(v1.end(), v2.begin(), v2.end());
			return ;
		}
	}

/*
	if(v1size==1){
		int i=0;
		for(; i<v2size; i++){
			if(vl[v2[i]].outdegree <= vl[v1[0]].outdegree){
				break;
			}
		}
		if(i<HUGENODENUM)
			v1.insert(v1.begin(), v2.begin(), v2.begin()+i);
		else{
			v1=v2;
			return ;
		}
		while(i<v2size && vl[v2[i]].outdegree==vl[v1[0]].outdegree){
			i++;
		}
		if(i<v2size)
			if(v2size==HUGENODENUM)
				v1.insert(v1.end(), v2.begin()+i, v2.begin()+HUGENODENUM-1);
			else
				v1.insert(v1.end(), v2.begin()+i, v2.end());
		return ;
	}
*/

	int k=0;
	int i=0, j=0;
	static vector<int> v(HUGENODENUM);
	v.clear();

	while(k<HUGENODENUM && i<v1size && j<v2size){
		if(vl[v1[i]].outdegree==vl[v2[j]].outdegree){
			if(v1[i]==v2[j]){
				v.push_back(v1[i]);
				i++;
				j++;
				k++;
			}else if(v1[i]<v2[j]){
				v.push_back(v1[i]);
				i++;
				k++;
			}else{
				v.push_back(v2[j]);
				j++;
				k++;
			}
		}else if(vl[v1[i]].outdegree>vl[v2[j]].outdegree){
			v.push_back(v1[i]);
			k++;
			i++;
		}else{
			v.push_back(v2[j]);
			k++;
			j++;
		}
	}

	if(k==HUGENODENUM){
		v1=v;
		return;
	}else{
		if(k==HUGENODENUM+1){
			cout << "bug..." << endl;
			v.pop_back();
			v1=v;
			return ;
		}else if(k>HUGENODENUM+1){
			cout << "bug..." << endl;
			return ;
		}
	}

	if(i!=v1size){
		if(v1.end() < v1.begin()+i+HUGENODENUM-v.size())
			v.insert(v.end(), v1.begin()+i, v1.end());
		else
			v.insert(v.end(), v1.begin()+i, v1.begin()+i+HUGENODENUM-v.size());
	}
	if(j!=v2size){
		if(v2.end() < v2.begin()+j+HUGENODENUM-v.size())
			v.insert(v.end(), v2.begin()+j, v2.end());
		else
			v.insert(v.end(), v2.begin()+j, v2.begin()+j+HUGENODENUM-v.size());
	}

	v1=v;
}

void Graph::IndexQueryTest(const string& indexfilename, const string& queryfilename){
	int u, v;
	bool ProLflag;
	clock_t start, end;
	struct timeval querystart, queryend;


	start=clock();
	ReadIndex(indexfilename.c_str());
	end=clock();
	cout << "ReadIndex is complete." << endl;
	cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;

	ifstream queryfile(queryfilename.c_str());
	string line;
//	vector< pair<int, int> > qpair;
	vector<int> src;
	vector<int> dest;
	vector<int> reachflag;
	vector<string> tmps;
	int i=0;
	start=clock();
	while(getline(queryfile, line), line.size()){
		split(line, ' ', tmps);
		src.push_back(atoi(tmps[0].c_str()));
		dest.push_back(atoi(tmps[1].c_str()));
//		qpair.push_back( make_pair(atoi(tmps[0].c_str()), atoi(tmps[1].c_str())) );
		reachflag.push_back(atoi(tmps[2].c_str()));
		i++;
		tmps.clear();
	}
	end=clock();
	cout << "ReadQueryfile is complete." << endl;
        cout << "Read Query File Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
	queryfile.close();


//	vector<int> flag(vsize, 0);
	flag=new int[vsize];
	memset(flag, 0, sizeof(int)*vsize);
	cout << "Total Query number: " << src.size() << endl;
	
	querycnt=0;
	gettimeofday(&querystart, NULL);
//	for(vector< pair<int, int> >::iterator qit=qpair.begin(); qit!=qpair.end(); qit++){
	for(vector<int>::iterator uit=src.begin(), vit=dest.begin(); uit!=src.end(); uit++, vit++){
//	for(i=0; i<src.size(); i++){
//		u=src[i];
//		v=dest[i];
		

		if(*uit==*vit)
			ProLflag=true;
		else if(reachindex[*uit].layerdown>=reachindex[*vit].layerdown || reachindex[*uit].layerup<=reachindex[*vit].layerup)
			ProLflag=false;
		else{
			querycnt++;
			ProLabelQueryDFS2(*uit, *vit);
		}

/*
                if((*qit).first==(*qit).second)
                        ProLflag=true;
		else if(reachindex[(*qit).first].layerdown>=reachindex[(*qit).second].layerdown || reachindex[(*qit).first].layerup<=reachindex[(*qit).second].layerup)
                        ProLflag=false;
		else{
                        querycnt++;
                        ProLabelQueryDFS2((*qit).first, (*qit).second);
		}
*/
//		cout << ProLflag << endl;
//
	}
	gettimeofday(&queryend, NULL);
        cout << "Time Cost: " << (queryend.tv_sec - querystart.tv_sec)*1000.0 + (queryend.tv_usec - querystart.tv_usec)*1.0/1000.0 << endl;

	int count=0;
	i=0;
	querycnt=0;
	memset(flag, 0, sizeof(int)*vsize);
//	for(vector< pair<int, int> >::iterator qit=qpair.begin(); qit!=qpair.end(); qit++, i++){
	for(vector<int>::iterator uit=src.begin(), vit=dest.begin(); uit!=src.end(); uit++, vit++, i++){

                if(*uit==*vit)
                        ProLflag=true;
                else if(reachindex[*uit].layerdown>=reachindex[*vit].layerdown || reachindex[*uit].layerup<=reachindex[*vit].layerup)
                        ProLflag=false;
		else{
			querycnt++;
			ProLflag=ProLabelQueryDFS2(*uit, *vit);
		}

/*
                if((*qit).first==(*qit).second)
                        ProLflag=true;
                else if(reachindex[(*qit).first].layerdown>=reachindex[(*qit).second].layerdown || reachindex[(*qit).first].layerup<=reachindex[(*qit).second].layerup)
                        ProLflag=false;
                else{
                        querycnt++;
                        ProLflag=ProLabelQueryDFS2((*qit).first, (*qit).second);
                }
*/
		if((bool)reachflag[i]!=ProLflag){
//			cout << "i: " << i << '\t' << (*qit).first << ' ' << (*qit).second << ' ' << reachflag[i] << endl;
			cout << "i: " << i << '\t' << *uit << ' ' << *vit << ' ' << reachflag[i] << endl;
			count++;
		}
	}

	cout << "False number: " << count << endl;

	delete[] flag;
}

bool Graph::IPtest(const int u, const int v){
	int it1=0, it2=0;

	if(reachindex[u].Label[ reachindex[u].OutLimit-1 ] > reachindex[v].Label[0] ){
		while(it1!=reachindex[u].OutLimit && it2!=reachindex[v].OutLimit){
			if(reachindex[u].Label[it1] == reachindex[v].Label[it2]){
				it1++;
				it2++;
			}else if(reachindex[u].Label[it1] < reachindex[v].Label[it2]){
				it1++;
			}else
				return true;
		}
	}
	
	if(reachindex[v].Label[ reachindex[v].InLimit-1 ] <= reachindex[u].Label[ reachindex[u].OutLimit ])
		return false;

	it1=reachindex[v].OutLimit;
	it2=reachindex[u].OutLimit;

	while(it1!= reachindex[v].InLimit && it2!=reachindex[u].InLimit){
		if(reachindex[v].Label[it1] == reachindex[u].Label[it2]){
			it1++;
			it2++;
		}else if(reachindex[v].Label[it1] < reachindex[u].Label[it2]){
			it1++;
		}else
			return true;
	}

	return false;
}

bool Graph::ProLabelQueryDFS2(const int u, const int v){
//      int tmpu;

//      cout << u << '\t';
        flag[u]=querycnt;

        if(IPtest(u,v))
                return false;

        unsigned int edgelistsize=graph[u].outList.size();

        if(edgelistsize > hugenode && HUGENODENUM!=0){

		for(int k=reachindex[v].InLimit; k!=reachindex[v].HLimit; k++){
			if(u==reachindex[v].Label[k])
				return true;
		}

		if((reachindex[v].HLimit-reachindex[v].InLimit)<HUGENODENUM)
			return false;

		if(edgelistsize > graph[ reachindex[v].Label[ reachindex[v].HLimit-1 ] ].outList.size())
			return false;
	}

//      for(unsigned int i=0; i<edgelistsize; i++){
        for(vector<int>::iterator it=graph[u].outList.begin(); it!=graph[u].outList.end(); it++){
//              tmpu=graph[u].outList[i];
                if(*it==v)
                        return true;
//              if(reachindex[tmpu].layerup > reachindex[v].layerup && reachindex[tmpu].layerdown < reachindex[v].layerdown && flag[tmpu]!=querycnt){
//              if(flag[*it]!=querycnt){
		if(reachindex[*it].layerup > reachindex[v].layerup && reachindex[*it].layerdown < reachindex[v].layerdown && flag[*it]!=querycnt){
			if(ProLabelQueryDFS2(*it, v))
				return true;
                }
        }

        return false;
}

bool Graph::IsContradict(vector<int>& v1, vector<int>& v2){
        vector<int>::iterator it1=v1.begin(), it2=v2.begin();

        if(*(v1.end()-1) < *it2)
                return false;

        while(it1!=v1.end()&&it2!=v2.end()){
                if(*it1 == *it2){
                        it1++;
                        it2++;
                }else if(*it1 < *it2){
                        it1++;
                }else{
                        return true;
                }
        }

        return false;
}


#endif
