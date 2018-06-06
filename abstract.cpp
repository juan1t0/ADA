#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <time.h>
#include <stdlib.h>
#include <queue>

using namespace std;

struct Edge  { 
	int i,j; 
	float w;
	Edge(int a = -1,int b = -1, float c = -1) : i(a), j(b),w(c) { }
};
class ComparePairFirst
{
public:
	inline bool operator() (pair<float,int> &A, pair<float,int> &B){
		return A.first > B.first;
	}
};
class CompareEdgeWeight
{
public:
	inline bool operator() (Edge &U, Edge &V){
		return U.w > V.w;
	}
};

class GRAPH {	
public:
	int Vcnt, Ecnt;
	double sum;
	bool digraph;
	vector<bool> *visited;
	vector<pair<float,int>> *dijkstar;
	priority_queue<pair<float,int>,vector<pair<float,int>>,ComparePairFirst>* cola;
	priority_queue<Edge,vector<Edge>,CompareEdgeWeight>* Aristas;
	
	virtual void remove(Edge)=0;
	virtual bool edge(int, int)=0;
	virtual void insert(Edge A)=0;
	virtual vector<pair<int,float>> neighbor(int)=0;
	virtual vector<Edge> Kruskal();
	virtual void visi_reinicio();
	virtual void dfs(int vertice);
	virtual void bfs(int vertice);
	virtual bool allVisited();
	//	virtual void SigismudDijkstra(int vertice,float we,int pre);
	virtual void Dijkstra(int vertice);
	virtual void camino(int vertice);
	virtual void mostrar(int v);
	virtual int V() const;
	virtual int E() const;
	virtual bool directed();
};

void GRAPH::visi_reinicio(){
	visited->clear();
	visited->assign(Vcnt,false);
}
bool GRAPH::allVisited(){
	for(int i=0;i<Vcnt;i++)
		if(visited->at(i)==false)
		return false;
	return true;
}
void GRAPH::camino(int vertice){
	if(dijkstar->at(vertice).second==-1){
		cout<< vertice<<" , ";
		return;
	}
	camino(dijkstar->at(vertice).second);		
	cout<< vertice<<" , ";
	
}
void GRAPH::mostrar(int v){
	for(int j=0;j<Vcnt;j++){
		if(j==v){
			cout<<"("<<dijkstar->at(j).first<<") camino a "<< j <<" : ";
			camino(j);
			cout<<endl;
			break;
		}
		;
	}
}
int GRAPH::V() const{
	return Vcnt;
}
int GRAPH::E() const{
	return Ecnt;
}
bool GRAPH::directed(){
	return digraph;
}
void GRAPH::dfs(int vertice){
	cout<<vertice<<" , ";
	visited->at(vertice)=true;
	vector<pair<int,float>> vecinos=neighbor(vertice);
	unsigned int s = vecinos.size();
	for (int i=0 ;i<s; i++){
		//cout<<"|"<<vecinos[i].first<<"|";
		if (!(visited->at(vecinos[i].first))){
			dfs(vecinos[i].first);
		}
	}
	return;
}
void GRAPH::bfs(int vertice){
	vector<vector<int>> L;
	for(int i = 0; i<Vcnt ;i++){
		vector<int> aux;
		L.push_back(aux);
	}
	L[0].push_back(vertice);
	visited->at(vertice)=true;
	cout<<vertice<<" , ";
	for (int i = 0 ; i<Vcnt ; i++){
		for (int u=0; u < L[i].size();u++){
			vector<pair<int,float>> vecinos=neighbor(u);
			unsigned int s = vecinos.size();
			for (int v=0 ;v<s; v++){
				if (!(visited->at(vecinos[v].first))){
					L[i+1].insert(L[i+1].end(),vecinos[v].first);
					visited->at(vecinos[v].first)=true;
					cout<<vecinos[v].first<<" , ";
				}
			}
		}
	}
	cout<<"  niveles -> {";
	for(int i=0;i<L.size();i++){
		int ss=L[i].size();
		if(ss == 0)
			break;
		cout<<"{ ";
		for(int j=0;j<ss;j++){
			cout<<L[i][j]<<" , ";
		}
		cout<<"} , ";
	}
	cout<<endl;
}
/*recursive Dijkstra
void GRAPH::SigismudDijkstra(int vertice,float we,int pre){
if(visited->at(vertice)== true)
return;

if(pre == -1 ){
dijkstar->at(vertice).first=we;
dijkstar->at(vertice).second=pre;
}
float aux = we;
vector<pair<int,float>> vecinos=neighbor(vertice);
unsigned int s = vecinos.size();
for (int i=0 ;i<s; i++){
if (visited->at(vertice)== false){
aux=we+vecinos[i].second;
if(dijkstar->at(vecinos[i].first).first > aux){
dijkstar->at(vecinos[i].first).first=aux;
dijkstar->at(vecinos[i].first).second=vertice;
if(cola->size() == 0)
cola->insert(cola->begin(),make_pair(aux,vecinos[i].first));
else {
int j;
for(j=0;j<cola->size() and cola->at(j).first>=aux;j++){
}						
cola->insert(cola->begin()+j,make_pair(aux,vecinos[i].first));
}
}
}
}
visited->at(vertice)=true;
while(!(cola->size()== 0)){
SigismudDijkstra(cola->at(cola->size()-1).second,cola->at(cola->size()-1).first,vertice);
if(cola->size()!=0)
cola->pop_back();
}
return;
}
*/

void GRAPH::Dijkstra(int vertice){
	float aux,weight = 0.0;
	unsigned int s,i;
	int x,cont=0;
	vector<pair<int,float> > vecinos;
	clock_t inicio,fin;
	
	dijkstar->assign(Vcnt,make_pair(10000.0 , -1));
	visi_reinicio();
	
	dijkstar->at(vertice).first = weight;
	dijkstar->at(vertice).second = -1;
	cola->push(make_pair(weight , vertice));
	inicio = clock();
	
	while(!cola->empty()){
		aux = weight;
		vecinos = neighbor(vertice);
		s = vecinos.size();
		cola->pop();
		for (i = 0 ; i < s ; i++)
		{
			x = vecinos[i].first;
			if (visited->at(x) == false)
			{
				aux = weight + vecinos[i].second;
				if(dijkstar->at(x).first > aux)
				{
					dijkstar->at(x).first = aux;
					dijkstar->at(x).second = vertice;
					cola->push(make_pair(aux , x));
				}
			}
		}
		visited->at(vertice)=true;
		vertice = cola->top().second;
		weight = cola->top().first;
	}
	/*	vector<pair<int,float> > vecinos = neighbor(vertice);
	s = vecinos.size();
	while(!cola->empty()){
	//		cout<<cont<<" a"<<endl;
	aux = weight;
	x = vecinos[cont].first;
	if (visited->at(x) == false)
	{
	aux = weight + vecinos[cont].second;
	if(dijkstar->at(x).first > aux)
	{
	dijkstar->at(x).first = aux;
	dijkstar->at(x).second = vertice;
	cola->push(make_pair(aux , x));
	}
	}
	cont++;
	if(cont == s){
	cola->pop();
	visited->at(vertice)=true;
	vertice = cola->top().second;
	weight = cola->top().first;
	cont=0;
	vecinos = neighbor(vertice);
	s = vecinos.size();
	}
	}*/
	fin = clock();
	cout<<"Main bucle ->"<<(double)(fin - inicio) / CLOCKS_PER_SEC<<endl;
}

typedef vector<int> vi;
vi pset;
void init(int N){
	pset.assign(N,0);
	for(int i =0;i<N;i++)
		pset[i]=i;
}
int find_set(int i){
	if(pset[i]==i)
		return pset[i];
	return pset[i]=find_set(pset[i]);
}
bool issameset(int i, int j){
	return find_set(i)==find_set(j);
}
void joinset(int i, int j){
	pset[find_set(i)]=find_set(j);
}
vector<Edge> GRAPH::Kruskal(){
	vector<Edge> MST;
	//vector<vector<int>> set_tree(Vcnt);
	init(Vcnt);
	//cout<<"|"<<Vcnt<<" "<<pset.size()<<"|"<<endl;
	while(!Aristas->empty()){
		//	cout<<Aristas->top().i<<" , "<<Aristas->top().j<<endl;
		if(!(issameset(Aristas->top().i,Aristas->top().j))){
			//	cout<<"- ";
			MST.push_back(Aristas->top());
			sum+=Aristas->top().w;
			joinset(Aristas->top().i,Aristas->top().j);
		}
		Aristas->pop();
	}
	//	cout<<endl;
	return MST;
}
///---------------------------------------------------------
class GRAPH_list : public GRAPH{
private:
	vector<vector<pair<int,float>>> list;
public:
	class listIterator;
	GRAPH_list(int V, bool digraph = false){
		Vcnt=V;
		Ecnt=0;
		this->digraph=digraph;
		for (int i = 0; i < V; i++){
			vector<pair<int,float>> temp;
			list.push_back(temp);
		}
		visited = new vector<bool>;
		dijkstar = new vector<pair<float,int>>(Vcnt);
		cola = new priority_queue<pair<float,int>,vector<pair<float,int>>,ComparePairFirst>;
		Aristas = new priority_queue<Edge,vector<Edge>,CompareEdgeWeight>;
		//llenarDijkstra();
	}
	~GRAPH_list(){}
	int V() const{GRAPH::V();}
	int E() const{GRAPH::E();}
	bool directed() const{return digraph;/*GRAPH<int>::directed();*/}
	
	void insert(Edge A){
		Ecnt = Ecnt +1;
		list[A.i].push_back(make_pair(A.j,A.w));
		if(!digraph){
			list[A.j].push_back(make_pair(A.i,A.w));
		}
		Aristas->push(A);
	}
	void show(){
		for(int i=0;i<Vcnt;i++){
			unsigned int s=list[i].size();
			cout<<i<<" : ";
			for(int j=0;j<s;j++){
				cout<<list[i][j].first<<" ";
			}
			cout<<endl;
		}	
	}
	bool find(int i , vector<pair<int,float>>A,unsigned int &x){
		unsigned int aSize = A.size();
		unsigned int k;
		for(k = 0; k < aSize ; k++){
			if(A[k].first == i){
				x=k;
				return true;
			}
		}
		return false;	
	}
	void remove(Edge R){
		Ecnt-=1;
		unsigned int x;
		if( find(R.j,list[R.i],x)){
			list[R.i].erase(list[R.i].begin()+x);
			if(find(R.i,list[R.j],x))
				list[R.j].erase(list[R.j].begin()+x);
		}
		if(find(R.i,list[R.j],x))
				 list[R.j].erase(list[R.j].begin()+x);
	}
	bool edge(int u, int v){
		unsigned int x;
		return find(v,list[u],x);
	}
	vector<pair<int,float>> neighbor(int v){
		return list[v];
	}
	
};
///---------------------------------------------------------
class GRAPH_adj : public GRAPH {
private:
	vector<vector<pair<bool,float>>> adj;
public:
	GRAPH_adj(int V, bool digraph = false): adj(V){
		Vcnt=V;
		Ecnt=0;
		this->digraph=digraph;
		for (int i = 0; i < V; i++)
			adj[i].assign(V, make_pair(false,-1));
		visited = new vector<bool>(Vcnt);
		dijkstar = new vector<pair<float,int>>(Vcnt);
		cola = new priority_queue<pair<float,int>,vector<pair<float,int>>,ComparePairFirst>;
	}
	~GRAPH_adj(){}
	int V() const{GRAPH::V();}
	int E() const{GRAPH::E();}
	bool directed() const{return digraph;/*GRAPH<int>::directed();*/}
	
	void insert(Edge A){
		Ecnt = Ecnt +1;
		(adj[A.i][A.j]).first = true;
		(adj[A.i][A.j]).second = A.w;
		if(!digraph){
			(adj[A.j][A.i]).first = true;
			(adj[A.j][A.i]).second = A.w;
		}
	}
	vector<pair<int,float>> neighbor(int v){
		vector<pair<int,float>> aux;
		for(int i=0;i<Vcnt;i++){
			if(adj[v][i].first == true )
				aux.push_back(make_pair(i,adj[v][i].second));
		}
		return aux;
	}
	void show(){
		for(int i=0;i<Vcnt;i++){
			cout<<i<<" : ";
			vector<pair<int,float>> temp = neighbor(i);
			unsigned int s = temp.size();
			for(int j=0;j<s;j++){
				cout<<temp[j].first<<" ";
			}
			cout<<endl;
		}	
	}
	void remove(Edge A){
		Ecnt = Ecnt -1;
		(adj[A.i][A.j]).first = false;
		(adj[A.i][A.j]).second = 0.0;
		if(!digraph){
			(adj[A.j][A.i]).first = false;
			(adj[A.j][A.i]).second = 0.0;
		}
	}
	bool edge(int u, int v){
		return adj[u][v].first;
	}
	
	bool findTree(){}
	void unionTree(){}
};
///---------------------------------------------------------
int main(int argc, char *argv[]) {
	int v,e;
	int g,c;
	float w;
	cin>>v>>e;
	GRAPH_list G(v);
	for(int i=0;i<e;i++){
		cin>>g>>c>>w;
		Edge aux(g,c,w);
		G.insert(aux);
	}
	//	G.show();
	clock_t inicio,fin;
	vector<Edge> Kr;
	//priority_queue<Edge,vector<Edge>,CompareEdgeWeight> *a = G.Aristas;
	//cout<<"||"<<endl;
	//cout<<"sss"<<endl;
	
	inicio = clock();
	//G.Dijkstra(1);
	Kr=G.Kruskal();
	fin = clock();
	
	//	for(int i=0;i<Kr.size();i++)
	//		cout<<"("<<Kr[i].i<<","<<Kr[i].j<<")"<<" ; ";
	
	cout<<endl;
	//G.mostrar(89);
	//cout<<endl;
	cout<<endl<<Kr.size()<<" **"<<G.sum<<endl;
	cout<<"todo ->"<<(double)(fin - inicio) / CLOCKS_PER_SEC<<endl;
	system("pause");
	return 0;
}
