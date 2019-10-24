#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Vertice;
class Vertice{
    public:
        int indice;
        vector<Vertice*> adjacentes;
        int visitado;

        Vertice();
        
        Vertice(int _indice){
            this->indice = _indice;
            this->visitado = 0;
        };

        void InserirAdjacencia(Vertice *v){
            this->adjacentes.push_back(v);
        }

        void Imprime(){
            cout << "Vertice: " << this->indice << endl;
            cout << "Lista de Adjacência: ";
            for (int i = 0; i < this->adjacentes.size(); i++ ){
                cout << this->adjacentes[i]->indice << " ";
            }
            cout << endl;
        }

};

class Grafo{
    public:    
        int nVertices;
        int nArestas;
        vector<Vertice*> vertices;

        Grafo();

        Grafo(int _nVertices, int _nArestas){
            this->nVertices = _nVertices;
            this->nArestas = _nArestas;
            for(int i=1; i<=_nVertices; i++){
                Vertice *v;
                v = new Vertice(i);
                this->vertices.push_back(v);
            }
        }

        void InserirArestaOrientada(int vO,int vD){
            this->vertices[vO-1]->InserirAdjacencia(this->vertices[vD-1]);
        }

        void InserirArestaComum(int v1, int v2){
            this->vertices[v1-1]->InserirAdjacencia(this->vertices[v2-1]);
            this->vertices[v2-1]->InserirAdjacencia(this->vertices[v1-1]);
        }

        void Imprime(){
            for(int i=0; i<this->vertices.size(); i++){
                this->vertices[i]->Imprime();
            }
        }

        void Caminho(int v1){
            if(this->vertices[v1-1]->visitado==1){
                return;
            }

            cout << this->vertices[v1-1]->indice << ",";

            this->vertices[v1-1]->visitado = 1;

            for(int i=0; i<this->vertices[v1-1]->adjacentes.size();i++){
                Caminho(this->vertices[v1-1]->adjacentes[i]->indice);
                cout << endl;
            }
        }

        void Inicializa(){
            for(int i=0; i<this->vertices.size(); i++){
                this->vertices[i]->visitado = 0;
            }
        }

};

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Erro de I/O" << endl;
        exit(0);
    }
    
    ifstream infile;
    infile.open(argv[1]);

    if(!infile.is_open()){
        cerr << "Erro ao abrir o arquivo, o mesmo nao existe!" << endl;
        exit(1);
    }

    int v=1; //número de vértices
    int a=1; //número de arestas
    
    while(1){
        v = 0;
        a = 0;

        infile >> v;
        infile >> a;

        if(v==0 && a==0){break;}

        Grafo *grafo;
        grafo = new Grafo(v,a);

        for(int i=0; i<a; i++){
            int vertice=0;
            int adjacencia=0;
            int orientado=0;

            infile >> vertice;
            infile >> adjacencia;
            infile >> orientado;

            if(orientado == 1){
                grafo->InserirArestaOrientada(vertice,adjacencia);
            }else if(orientado == 2){
                grafo->InserirArestaComum(vertice,adjacencia);
            }
        }
        cout << "---------Grafo G"<< v << "x" << a <<"---------" << endl;
        grafo->Imprime();
        for(int i=1;i<=grafo->vertices.size(); i++){
            grafo->Caminho(i);
            grafo->Inicializa();
        }
        cout << endl;
        cout << "----------------------------" << endl;
    }

    return 0;
}