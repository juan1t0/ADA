#include <iostream>
#include <utility>
#include <string>
#include <vector>

typedef std::string str;


//template <class V>
class VertiC{
public:
	char valor;
	str status="unvisited";
	int entra;
	int termina;
	std::vector<VertiC*> alcanzable;
	
	VertiC(){}
	~VertiC(){}
	
	void addArista_B(VertiC& a){
		alcanzable.insert(alcanzable.end(),&a);
		(a.alcanzable).insert((a.alcanzable).end(),(this));
	}
	void addArista_U(VertiC& a){
		alcanzable.insert(alcanzable.end(),&a);
	}
};
//template <class V>
str reverseTopo;
int dfs(VertiC &v,int time){
	v.entra = time;
	time += 1;
	v.status = "in_progress";
	int siz=v.alcanzable.size();
	std::cout<<v.valor<<" "<<siz<<" \n";
	for(int i=0;i<siz;i++){
		if ((v.alcanzable[i])->status == "unvisited"){
			time = dfs(*(v.alcanzable[i]), time);
			time += 1;
		}
	}
	std::cout<<"s \n";
	v.termina = time;
	v.status = "done";
	reverseTopo+=v.valor;
	return time;
}
void PrintTopo(){
	for(int i= reverseTopo.size()-1;i>=0;i--)
		std::cout<<reverseTopo[i]<<" , ";
	std::cout<<'\n';
}
std::vector<std::vector<VertiC>> bfs(VertiC s,int n){
	std::vector<std::vector<VertiC>> L(n);
//	for i = 0 to n-1:
//		L[i] = {}
	std::vector<VertiC> aux;
	L[0] = aux;
	aux.push_back(s);
	for(int i = 0;i< n-1;i++)
		for(int j=0;j<(L[i]).size();j++){
			VertiC u = (L[i])[j];
			for(int k=0;k<(u.alcanzable).size();k++){
				VertiC* v = (u.alcanzable)[k];
				if (v->status == "unvisited"){
					v->status = "visited";
					L[i+1].push_back(*v);
				}
			
			}	
		}
}
void PrintGrafo(std::vector<VertiC> &G){
	int size_g= G.size(),size_ne;
	VertiC *p;
	for(int i=0;i<size_g;i++){
		p=&(G[i]);
		std::cout<<p->valor<<" : ";
		size_ne = (p->alcanzable).size();
		for(int j=0;j<size_ne;j++){
			std::cout<<((p->alcanzable).at(j))->valor<<" - ";
		}
		std::cout<<'\n';
	}
}

void PrintTheSameGrafo(std::vector<VertiC> &G){
	int size_g= G.size(),size_ne;
	VertiC *p;
	for(int i=0;i<size_g;i++){
		p=&(G[i]);
		std::cout<<p->valor<<" : inicio->"<<p->entra<<" salida->"<<p->termina;
		
		std::cout<<'\n';
	}
}

int main(int argc, char *argv[]) {
	std::vector<VertiC> grafo;
	VertiC* aux;
	for(int i=0;i<8;i++){
		aux= new VertiC();
		aux->valor = 'A' + i;
		grafo.insert(grafo.end(),*aux);
//		aux.~VertiC();
		aux=0;
	}
	(grafo[0]).addArista_B(grafo[1]);
	(grafo[0]).addArista_B(grafo[6]);
	(grafo[0]).addArista_B(grafo[7]);
	(grafo[1]).addArista_B(grafo[2]);
	(grafo[1]).addArista_B(grafo[4]);
	(grafo[1]).addArista_B(grafo[5]);
	(grafo[2]).addArista_B(grafo[6]);
	(grafo[3]).addArista_B(grafo[2]);
	(grafo[3]).addArista_B(grafo[4]);	
	(grafo[3]).addArista_B(grafo[5]);		
	
	PrintGrafo(grafo);
	int d = dfs(grafo[0],0);
	std::cout<<" ::"<<d<<"::\n";
	PrintTheSameGrafo(grafo);
	PrintTopo();
	return 0;
}

