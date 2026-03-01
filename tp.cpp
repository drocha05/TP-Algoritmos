#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct tipoAtleta {
    int id;
    char nombre[20+1];
    char apodo[20+1];
    float peso;
    int victorias;
    int derrotas;
};

struct nodo{
    tipoAtleta info;
    nodo* sgte;
};

struct pesoCategorias
{
    char nombre[20+1];
    float pesoMin;
    float pesoMax;
};


/*
void inscribir();
void genmaincard();
void actRecord();*/
tipoAtleta pop(nodo*&);
nodo* insertarOrdxPeso(nodo*&, tipoAtleta);
void cargar(FILE*, nodo*&);
void guardar(FILE*, nodo*&);
void inscribirAtleta(nodo*&);
int main()
{
    int opcMenu;
    /*int top = 10;
    int combates = 5;
    
    pesoCategorias ctgs[8];
    strcpy(ctgs[0].nombre,"Mosca");     ctgs[0].pesoMin = 0;    ctgs[0].pesoMax = 56.7;
    strcpy(ctgs[1].nombre,"Gallo");     ctgs[1].pesoMin = 56.8; ctgs[1].pesoMax = 61.2;
    strcpy(ctgs[2].nombre,"Pluma");     ctgs[2].pesoMin = 61.3; ctgs[2].pesoMax = 65.8;
    strcpy(ctgs[3].nombre,"Ligero");    ctgs[3].pesoMin = 65.9; ctgs[0].pesoMax = 70.3;
    strcpy(ctgs[4].nombre,"Welter");    ctgs[4].pesoMin = 70.4; ctgs[4].pesoMax = 77.1;
    strcpy(ctgs[5].nombre,"Mediano");   ctgs[5].pesoMin = 77.2; ctgs[5].pesoMax = 83.9;
    strcpy(ctgs[6].nombre,"Semipesado");ctgs[6].pesoMin = 84;   ctgs[6].pesoMax = 93;
    strcpy(ctgs[7].nombre,"Pesado");    ctgs[7].pesoMin = 93.1; ctgs[7].pesoMax = 120,2;
    tipoAtleta ranking[top] = {0};
    tipoAtleta maincard[combates] = {0};
    */
    nodo* lista = NULL;
    nodo* listaAct = NULL;
    FILE* f=fopen("atletas.dat","rb+");

    cargar(f, lista);
	
    cout << "Menu de Funciones" << endl;
    cout << "1: Inscripcion de Atleta" << endl;
    cout << "2: Generar Main Card" << endl;
    cout << "3: Actualizar Record" << endl;
    cout << "4: Guardar Gimnasio" << endl;
    cout << "5: Mostrar Gimnasio" << endl;
    cout << "0: Salir del programa" << endl;

    cout << "Elija una opcion: ";
    cin >> opcMenu;

    while(opcMenu!=0)
    {
        if (opcMenu == 1)
        {
            inscribirAtleta(lista);
        }
        
        if (opcMenu == 4)
        {
            cout << "Opcion de guardar en el archivo" << endl;
            guardar(f, lista);
        }

        if (opcMenu == 5)
        {
            cout << "Opcion de mostrar la lista" << endl;
            nodo* listaAux = lista;
            int ranking = 1;
            cout << "Ranking" << "\t"<< "Id" << "\t" << "Nombre" << "\t" << "Apodo"
            << "\t" << "Peso" << "\t" << "Victorias" << "\t" << "Derrotas" << endl;
            while (listaAux!=NULL)
            {
                tipoAtleta atleta = listaAux->info;
                cout << ranking << "\t";
                cout << atleta.id << "\t";
                cout << atleta.nombre << "\t";
                cout << atleta.apodo << "\t";
                cout << atleta.peso << "\t";
                cout << atleta.victorias << "\t";
                cout << atleta.derrotas << "\t" << endl;
                listaAux = listaAux->sgte;
                ranking++;
            }
        }
   
        cout << "Elija una opcion: ";
        cin >> opcMenu;
    }
    fclose(f);
    return 0;
}

tipoAtleta pop(nodo*& pila){
    tipoAtleta aux;
    aux = pila->info;
    nodo* p = pila;
    pila = p->sgte;
    delete p;
    return aux;
};

nodo* insertarOrdxPeso(nodo*& lista, tipoAtleta atleta){
    nodo* p = new nodo();
    p->info = atleta;

    int pesoRank = p->info.victorias - p->info.derrotas;

    if(lista==NULL || (pesoRank >= (lista->info.victorias - lista->info.derrotas))){
        p->sgte = lista;
        lista = p;
    }
    else{
        nodo* q = lista;
        while (q->sgte!=NULL && (pesoRank <= (q->sgte->info.victorias - q->sgte->info.derrotas)))
        {
            q = q->sgte;
        }
        p->sgte = q->sgte;
        q->sgte = p;
    }
    return p;
}

void buscarId(nodo*& lista, tipoAtleta atleta);{
    nodo* aux = lista;
    
}

void guardar(FILE* f, nodo*& lista){
    
    tipoAtleta atleta;
    nodo* q = lista;
    while(q!=NULL){
        atleta = pop(q);
        fwrite(&atleta,sizeof(tipoAtleta),1,f);
    }
    return;
}

void cargar(FILE* f, nodo*& lista){
    fseek(f,0,SEEK_SET);
    tipoAtleta atleta;

    while (fread(&atleta, sizeof(tipoAtleta), 1, f) == 1)
    {
        insertarOrdxPeso(lista, atleta);
    }   
    return;
}

void mostrarAtletas(){



}

void inscribirAtleta(nodo*& lista){
    int canAtletas, i;
    tipoAtleta atleta;
    cout << "Indique la cantidad de atletas a guardar: ";
    cin >> canAtletas;
    for (i = 0; i < canAtletas; i++)
    {
        cout << "Datos del atleta" << endl;
        cout << "Id: "; cin >> atleta.id;
        cout << "Nombre: "; cin >> atleta.nombre;
        cout << "Apodo: "; cin >> atleta.apodo;
        cout << "Peso: "; cin >> atleta.peso;
        cout << "Victorias: "; cin >> atleta.victorias;
        cout << "Derrotas: "; cin >> atleta.derrotas; 
        insertarOrdxPeso(lista, atleta);
    }    
}

/*void genMainCard(tipoAtleta maincard[], pesoCategorias categorias[], nodo* lista){
    int i = 0, j = 0;
    while (lista!=NULL)
    {
        cout << "MainCard de la categoria Peso " << categorias[i].nombre << endl;
        for (j = 0; j < 5; j++)
        {
            
        }
        i++;
    }
    
}*/
