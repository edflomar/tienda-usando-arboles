#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
//estructura tienda 
struct Tienda{
	char clave[20];//clave del producto 
	char nombre[20];//nombre del producto
	int cantidad;//cantidad de producto
	double precio;//precio del producto
};

// declarando nodo
struct Nodo{
	Nodo *izquierdo;
	Tienda producto;//producto variable para la estructura tienda
	Nodo *derecho;//Nodo tipo puntero siguiente
};

struct Cliente{
	double total;
	string clave[20];
	string nombre[20];
	double precio;
};

struct Nodo2{
	Nodo2 *lista;
	Cliente carrito;
};

void menu();
void menu2();
void agregarProducto(Tienda &);
void insertarProducto(Nodo *&,Tienda);
void venta(Nodo *&,int &);
void imprimirDatos(Nodo *&);
Nodo *nDinamico(Tienda);

int main(){
	Nodo *arbol=NULL;
	Tienda producto;
	char opcion;//variable para el switch
	double caja=0;
	char clave[20];
	char opcion2;
	double totalC;
	int cantidad;
	
	do{
		menu();
		cin>>opcion;
		fflush(stdin);//vacia el buffer
    	switch(opcion){
	    	case '1':
		    	agregarProducto(producto);//llamando a funcion para agregar productos
		    	insertarProducto(arbol,producto);//llamando funcion para insertar los nodos a la cola
			    break;
    		case '2':
    			do{
    				menu2();
    				cin>>opcion2;
    				fflush(stdin);
    				switch(opcion2){
    					case '1':
						    if(stock(clave,arbol)){
						    	agregarCarrito();
							}
							break;
    					case '2':
						    break;
    					case '3':
    						cout<<"\nIngresar la clave del producto: "; cin.getline(clave,20,'\n');
    						fflush(stdin);
    						cout<<"\nIngresar cantidad a restar del producto: "; cin>>cantidad;
						    break;
    					case '4': 
						    //
						    break;
    					case '5': 
					    	//
						    break;
    					defalut:  //
						    break;
					}
				}while(opcion2 !='5'&&opcion2 !='6');
    			
		    	break;
    		case '3':
    			cout<<"CLAVE\t"<<"NOMBRE\t\t"<<"PRECIO\t\t"<<"CANTIDAD"<<endl;
    			imprimirDatos(arbol);
				cout<<"\nDinero en caja: "<<caja;//imprime dinero en caja
		    	break;
   	        case '4':
   	        	cout<<"Salio del programa..."<<endl;
   	        	break;
      	    default:
      	    	cout<<"\nOpcion invalida."<<endl;
      	    	break;
    	}
    	getch();//pausa para evitar que se limpie pantalla sin que el usuario la vea
    	system("cls");//Limpia pantalla
    }while(opcion !='4');
	return 0;//retorna un 0 si no hay errores
}

//funcion que muestra menu al usuario
void menu(){
	cout<<"\nBienvenido"<<endl
	    <<"1.Ingresar producto."<<endl
	    <<"2.Vender producto."<<endl
	    <<"3.Mostrar productos."<<endl
	    <<"4.Salir"<<endl
	    <<"Ingresar una opcion del menu: ";
}

void menu2(){
	cout<<"\nMenu"<<endl
	    <<"1.Agregar a carrito."<<endl
	    <<"2.Quitar del carrito."<<endl
	    <<"3.Restar cantidad de un producto."<<endl
	    <<"4.Finalizar venta."<<endl
	    <<"5.Cancelar venta."<<endl
	    <<"Ingresar opcion: ";
}

Nodo *nDinamico(Tienda producto){
    Nodo *nNodo = new Nodo();
    //Los nodos hijos estaran vacion en el nuevo nodo
	nNodo->producto = producto;//Nodo raiz
	nNodo->derecho = NULL;//Nodo hijo
	nNodo->izquierdo = NULL;//Nodo hijo
	
	return nNodo;//Retornando el nuevo nodo con su nuevo valor
}

//Pide datos del producto 
void agregarProducto(Tienda &producto){
	cout<<"Ingresar clave del producto: "; cin.getline(producto.clave,20,'\n');
    cout<<"\nIngresar nombre del producto: "; cin.getline(producto.nombre,25,'\n');
   	cout<<"\nIngresar precio del producto: "; cin>>producto.precio;
   	cout<<"\nIngresar cantidad del producto: "; cin>>producto.cantidad;
}

//Inserta los nodos y agrega un nuevo nodo
void insertarProducto(Nodo *&arbol ,Tienda producto){
	if(arbol==NULL){
	Nodo *nNodo = nDinamico(producto);
	arbol = nNodo;
	}else{
		if(producto.precio < arbol->producto.precio){
			insertarProducto(arbol->izquierdo,producto);
		}else{
			insertarProducto(arbol->derecho,producto);
		}
	}
}


void imprimirDatos(Nodo *&arbol){
	if(arbol == NULL){
	return;
	}else{
		imprimirDatos(arbol->derecho);
		cout<<arbol->producto.clave<<"\t"<<arbol->producto.nombre<<"\t\t"<<arbol->producto.precio<<"\t\t"<<arbol->producto.cantidad;
		imprimirDatos(arbol->izquierdo);
	}
}

bool stock()
