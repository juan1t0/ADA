#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct Edge  { 
	int i,j; 
	float w;
Edge(int a = -1,int b = -1, float c = -1) : i(a), j(b),w(c) { }
};

class GRAPH {	
public:
	int Vcnt, Ecnt;
	bool digraph;
	vector<bool> *visited;
	vector<pair<float,int>> *dijkstar,*cola;
	
	virtual void remove(Edge)=0;
	virtual bool edge(int, int)=0;
	virtual void insert(Edge A)=0;
	virtual vector<pair<int,float>> neighbor(int)=0;
	virtual void llenarDijkstra();
	virtual void visi_reinicio();
	virtual void dfs(int vertice);
	virtual void bfs(int vertice);
	virtual bool allVisited();
	virtual void SigismudDijkstra(int vertice,float we,int pre);
	virtual void Dijkstra(int vertice,float we,int pre);
	virtual void camino(int vertice);
	virtual void mostrar(int v);
	virtual int V() const;
	virtual int E() const;
	virtual bool directed();
};

void GRAPH::llenarDijkstra(){
	float inflot = 1000.00;
	dijkstar->assign(Vcnt,make_pair(inflot,-1));
/*	for(int i=0;i<Vcnt;i++){
		pair<float,int> temp;
		temp = make_pair(inflot,-1);
		dijkstar->at(i)=temp;
	}*/
}
void GRAPH::visi_reinicio(){
	cout<<",";
	for(int j=0;j<Vcnt;j++){
		visited->at(j)=false;
	}
	cout<<",\n";
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
void GRAPH::SigismudDijkstra(int vertice,float we,int pre){
//	cout<<".";
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
void GRAPH::Dijkstra(int vertice,float we,int pre){
	llenarDijkstra();
	visi_reinicio();
	
	dijkstar->at(vertice).first=we;
	dijkstar->at(vertice).second=pre;
	cola->push_back(make_pair(we,vertice));
	while(!(cola->size()==0)){
//		cout<<".";
		float aux = we;
		vector<pair<int,float>> vecinos=neighbor(vertice);
		unsigned int s = vecinos.size();
		/*cout<<"{";
		for(int o=0;o<cola->size();o++){
			cout<<cola->at(o).second<<";";
		}
		cout<<endl;*/
		cola->pop_back();
		for (int i=0 ;i<s; i++){
			if (visited->at(vecinos[i].first)== false){
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
					//cout<<"-";
				}

			}
		}
//		cout<<vertice;
		visited->at(vertice)=true;
		
//		cout<<"|"<<vertice<<"|";
	//	cola->pop_back();
		if(cola->size()!=0){
			vertice = cola->at(cola->size()-1).second;
			we = cola->at(cola->size()-1).first;
		}
	/*	cout<<"[";
		for(int o=0;o<cola->size();o++){
			cout<<cola->at(o).second<<" ";
		}
		cout<<"]"<<endl;*/
	}
/*
	while(!(cola->size()== 0)){
		SigismudDijkstra(cola->at(cola->size()-1).second,cola->at(cola->size()-1).first,vertice);
		
			cola->pop_back();
	}
	return;*/
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
		visited = new vector<bool>(Vcnt);
		dijkstar = new vector<pair<float,int>>(Vcnt);
		cola = new vector<pair<float,int>>;
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
	//	cout<<"%"<<endl;
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
		cola = new vector<pair<float,int>>;
		llenarDijkstra();
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
};
///---------------------------------------------------------
int main(int argc, char *argv[]) {
	int v,e;
	int g,c;
	float w;
	cin>>v>>e;
	GRAPH_list G(v,true);
	G.visi_reinicio();
//	GRAPH_adj GG(v,true);
	for(int i=0;i<e;i++){
		cin>>g>>c>>w;
		Edge aux(g,c,w);
		G.insert(aux);
	//	GG.insert(aux);
	}
//	G.show();
	//G.visi_reinicio();
//	GG.visi_reinicio();
	clock_t inicio,fin;
	
	inicio = clock();
	G.Dijkstra(1,0,-1);
	fin = clock();

	G.mostrar(89);
	cout<<endl;
	cout<<"L ->"<<(double)(fin - inicio) / CLOCKS_PER_SEC<<endl;
//	G.show();
	//G.dfs(0);///0 , 1 , 2 , 3 , 6 , 8 , 7 , 4 , 5 , 9 
//	G.visi_reinicio();
	//cout<<endl;
	//G.bfs(0);///0 , 1 , 2 , 3 , 5 , 6 , 9 , 4 , 7 , 8 ,   niveles -> {{ 0 , } , { 1 , 2 , 3 , 5 , 6 , 9 , } , { 4 , 7 , 8 , } 
/*	inicio = clock();
	GG.SigismudDijkstra(1,0,-1);
	fin = clock();
	GG.mostrar(89);
	cout<<endl;
	cout<<"M ->"<<(double)(fin - inicio) / CLOCKS_PER_SEC<<endl;*/
	system("pause");
	return 0;
}
