#include <iostream>
#include <vector>
#include <string>

using namespace std;



struct Edge  { int v, w;
Edge(int v = -1, int w = -1) : v(v), w(w) { }
};

class GRAPH {
private:
	// Implementation-dependent code
	vector<vector <bool> > adj;
	int Vcnt, Ecnt;
	bool digraph;
	vector<bool> *visited;
	
public:
	GRAPH(int V, bool digraph = false) : adj(V), Vcnt(V), Ecnt(0), digraph(digraph) {
		for (int i = 0; i < V; i++)
			adj[i].assign(V, false);
		visited=new vector<bool>(Vcnt);
	}
	
	~GRAPH(){}
	int V() const{return Vcnt;}
	int E() const{return Ecnt;}
	bool directed() const{return digraph;}
	void insert(Edge A){
		Ecnt = Ecnt +1;
		adj[A.v][A.w] = true;
		if(!digraph){
			adj[A.w][A.v] = true;
		}
	}
	void remove(Edge);
	bool edge(int, int);
	class adjIterator;
	
	void visi_reinicio(){
		//visited.clear();
		for(int j=0;j<Vcnt;j++){
			visited->at(j)=false;
		}
	}
	void dfs(int vertice){
		cout<<vertice<<" ";
		visited->at(vertice)=true;
		for (int i=0 ;i<Vcnt; i++){
			if (adj[vertice][i]==true and !(visited->at(i))){
				dfs(i);
			}
		}
//		cout<<endl;
		return;
	}
	void bfs(int vertice){
	L = []
	for i = 0 to n-1:
		L[i] = {}
	L[0] = {s}
	for i = 0 to n-1:
		for u in L[i]:
			for v in u.neighbors:
				if v.status is "unvisited":
					v.status = true
					L[i+1].add(v)
					
	}
};

class GRAPH::adjIterator {
	const GRAPH &G;
	int i, v;
	
public:
	adjIterator(const GRAPH &G, int v) :  G(G), v(v), i(-1) { }
	int beg() { i = -1; return nxt(); }
	int nxt() {
		for (i++; i < G.V(); i++)
			if (G.adj[v][i] == true) return i;
		return -1;
	}
	bool end() { return i >= G.V(); }
};

template <class Graph>
vector <Edge> edges(Graph &G) {
	int E = 0;
	vector <Edge> a(G.E());
	for (int v = 0; v < G.V(); v++) {
		typename Graph::adjIterator A(G, v);
		for (int w = A.beg(); !A.end(); w = A.nxt())
			if (G.directed() || v < w)
				a[E++] = Edge(v, w);
	}
	return a;
}

template <class Graph>
void show(const Graph &G) {
	for (int s = 0; s < G.V(); s++) {
		cout.width(2); cout << s << ":";
		typename Graph::adjIterator A(G, s);
		for (int t = A.beg(); !A.end(); t = A.nxt()) { 
			cout.width(2); cout << t << " "; 
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	int v,e;
	int g,c,w;
	cin>>v>>e;
	GRAPH G(v,true);
	for(int i=0;i<e;i++){
		cin>>g>>c>>w;
		Edge aux(g,c);
		G.insert(aux);
	}
	show(G);
	G.visi_reinicio();
	G.dfs(0);
	G.visi_reinicio();
	G.dfs(1);
	G.visi_reinicio();
	G.dfs(2);
	G.visi_reinicio();
	G.dfs(3);
	G.visi_reinicio();
	G.dfs(4);
	G.visi_reinicio();
	G.dfs(5);
	G.visi_reinicio();
	G.dfs(6);
	G.visi_reinicio();
	G.dfs(7);
	G.visi_reinicio();
	G.dfs(8);
	G.visi_reinicio();
	G.dfs(9);
	return 0;
}
