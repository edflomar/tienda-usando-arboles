#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int NUM=20;
//estructura tienda 
struct Tienda{
	int clave;//clave del producto 
	string nombre;//nombre del producto
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
	int folio;
	double total;
	int claveP[NUM];
	string nombre[NUM];
	double precio[NUM];
	int cantidad[NUM];
};

struct Nodo2{
	Nodo2 *siguiente;
	Cliente carrito;
};

void menu();
void menu2();
void agregarProducto(Tienda &,int &);
void insertarProducto(Nodo *&,Tienda);
void venta(Nodo *&,int &);
void imprimirDatos(Nodo *&);
Nodo *nDinamico(Tienda);
bool buscar(Nodo *,int,int &);
void agregarCarrito(Nodo *,Cliente &,int,int);
void eliminarProducto(Cliente &,int);
void insertarCliente(Nodo2 *&,Cliente,int,double &);
void restar(Cliente &,int,int);
void cancelar(Cliente &);
void mostrarCarrito(Cliente &);
void mostrarCliente(Nodo2 *&,int &);
void rellenar(Cliente &);

int main(){
	Nodo *arbol=NULL;
	Nodo2 *lista=NULL;
	Cliente carrito;
	Tienda producto;
	char opcion;//variable para el switch
	double caja=0;
	int clave;
	char opcion2;
	int cantidad;
	int claveP=1;
	int auxCantidad=0;
	int claveC;
	int auxFolio=1;
	
	do{
		menu();
		cin>>opcion;
		fflush(stdin);//vacia el buffer
    	switch(opcion){
	    	case '1':
		    	agregarProducto(producto,claveP);//llamando a funcion para agregar productos
		    	insertarProducto(arbol,producto);//llamando funcion para insertar los nodos a la cola
		    	claveP +=1;
			    break;
    		case '2':
    			rellenar(carrito);
    			do{
    				Nodo *auxArbol=NULL;
    				auxArbol = arbol;
    				menu2();
    				cin>>opcion2;
    				fflush(stdin);
    				switch(opcion2){
    					case '1':
    						cout<<"\nIngresar clave del producto: "; cin>>claveC;
						    if(buscar(auxArbol,claveC,auxCantidad) == true){
						    	cout<<"\nCantidad de producto disponible: "<<auxCantidad<<endl;
						    	cout<<"\nIngresar la cantidad de produto a vender: "; cin>>cantidad;
						    	if(cantidad<=auxCantidad){
						    		agregarCarrito(auxArbol,carrito,claveC,cantidad);
						    		
								}else{
									cout<<"\nProducto en stock insuficiente."<<endl;
								}
							}else{
								cout<<"\nError."<<endl;
							}
							//mostrarCarrito(carrito);
							break;
    					case '2':
    						//mostrarCarrito(carrito);
    						cout<<"\nIngresar clave del producto a quitar: "; cin>>claveC;
    						eliminarProducto(carrito,claveC);
						    break;
    					case '3':
    						//mostrarCarrito(carrito);
    						cout<<"\nIngresar la clave del producto: "; cin>>clave;
    						fflush(stdin);
    						cout<<"\nIngresar cantidad a restar del producto: "; cin>>cantidad;
    						restar(carrito,clave,cantidad);
						    break;
    					case '4': 
    					    //mostrarCarrito(carrito);
						    if(carrito.claveP[0] !=0){
						    	insertarCliente(lista,carrito,auxFolio,caja);
							}else{
								cout<<"\nCarrito vacio."<<endl;
							}
						    break;
    					case '5': 
					    	cancelar(carrito);
					    	cout<<"\nVenta cancelada"<<endl;
						    break;
						case '6':
							cout<<"\nSalio de ventas, su carrito se guardara hasta que cancele la compra."<<endl;
							break;
    					defalut:  //
						    break;
					}
				}while(opcion2 !='5'&&opcion2 !='6'&&opcion2 !='4');
    			
		    	break;
    		case '3':
    			cout<<"CLAVE\t"<<"NOMBRE\t\t"<<"PRECIO\t\t"<<"CANTIDAD"<<endl;
    			imprimirDatos(arbol);
				cout<<"\nDinero en caja: "<<caja;//imprime dinero en caja
		    	break;
   	        case '4':
   	        	cout<<"\nIngresar folio del cliente: "; cin>>claveC;
   	        	mostrarCliente(lista,claveC);
   	        	break;
   	        case '5':
   	        	cout<<"\nSalio del programa correctamente."<<endl;
   	        	break;
      	    default:
      	    	cout<<"\nOpcion invalida."<<endl;
      	    	break;
    	}
    	getch();//pausa para evitar que se limpie pantalla sin que el usuario la vea
    	system("cls");//Limpia pantalla
    }while(opcion !='5');
	return 0;//retorna un 0 si no hay errores
}

//funcion que muestra menu al usuario
void menu(){
	cout<<"\nBienvenido"<<endl
	    <<"1.Ingresar producto."<<endl
	    <<"2.Vender producto."<<endl
	    <<"3.Mostrar productos."<<endl
	    <<"4.Buscar registro de un cliente."<<endl
	    <<"5.Salir"<<endl
	    <<"Ingresar una opcion del menu: ";
}

void menu2(){
	cout<<"\nMenu"<<endl
	    <<"1.Agregar a carrito."<<endl
	    <<"2.Quitar del carrito."<<endl
	    <<"3.Restar cantidad de un producto."<<endl
	    <<"4.Finalizar venta."<<endl
	    <<"5.Cancelar venta."<<endl
	    <<"6.Salir de ventas."<<endl
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
void agregarProducto(Tienda &producto,int &claveP){
	producto.clave=claveP;
    cout<<"\nIngresar nombre del producto: "; cin>>producto.nombre;
   	cout<<"\nIngresar precio del producto: "; cin>>producto.precio;
   	cout<<"\nIngresar cantidad del producto: "; cin>>producto.cantidad;
}

//Inserta los nodos y agrega un nuevo nodo
void insertarProducto(Nodo *&arbol ,Tienda producto){
	if(arbol==NULL){
	Nodo *nNodo = nDinamico(producto);
	arbol = nNodo;
	}else{
		if(producto.clave < arbol->producto.clave){
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
		cout<<arbol->producto.clave<<"\t"<<arbol->producto.nombre<<"\t\t"<<arbol->producto.precio<<"\t\t"<<arbol->producto.cantidad<<endl;
		imprimirDatos(arbol->izquierdo);
	}
}

bool buscar(Nodo *arbol,int clave,int &auxCantidad){
	
	if(arbol ==NULL){
		return false;
	}else if(arbol->producto.clave==clave){
		auxCantidad=arbol->producto.cantidad;
		return true;
	}else if(clave < arbol->producto.clave){
		return buscar(arbol->izquierdo,clave,auxCantidad);
	}else{
		return buscar(arbol->derecho,clave,auxCantidad);
	}
}

void agregarCarrito(Nodo *arbol,Cliente &carrito,int clave,int cantidad){
	int auxClave = arbol->producto.clave;
	if(arbol ==NULL){
	    return;
	}else if(arbol->producto.clave==clave){
		cantidad=arbol->producto.cantidad;
		for(int i=0; i<NUM; i++){
		if(carrito.claveP[i]==-1){
			carrito.claveP[i]=arbol->producto.clave;
			carrito.nombre[i]=arbol->producto.nombre;
			carrito.precio[i]=arbol->producto.precio;
			carrito.cantidad[i]=cantidad;
			carrito.total=carrito.total+(arbol->producto.precio*cantidad);
			return;
		}
	}
	}else if(clave < auxClave){
		agregarCarrito(arbol->izquierdo,carrito,clave,cantidad);
	}else{
		agregarCarrito(arbol->derecho,carrito,clave,cantidad);
	}
}

void eliminarProducto(Cliente &carrito,int claveC){
	for(int i=0; i<NUM; i++){
		if(carrito.claveP[i]==claveC){
			carrito.claveP[i]=-1;
			carrito.nombre[i]='0';
			carrito.total=carrito.total-(carrito.precio[i]*carrito.cantidad[i]);
			carrito.precio[i]=0;
			carrito.cantidad[i]=0;
			cout<<"\nEl producto ha sido eliminado"<<endl;
			return;
		}
	}
	cout<<"\nProducto no encontrado."<<endl;
}

void insertarCliente(Nodo2 *&lista,Cliente carrito,int auxFolio,double &caja){
	carrito.folio=auxFolio;
	caja +=carrito.total;
	Nodo2 *nNodo = new Nodo2;
	nNodo->carrito = carrito;
	Nodo2 *aux1 = lista;
	Nodo2 *aux2;
	while((aux1 !=NULL)&&(aux1->carrito.claveP<carrito.claveP)){
		aux2 = aux1;
		aux1 = aux1->siguiente;
	}
	if(lista == aux1){
		lista = nNodo;
	}else{
		aux2->siguiente = nNodo;
	}
	nNodo->siguiente = aux1;
	cout<<carrito.folio;
	auxFolio +=1;
}

void restar(Cliente &carrito,int clave,int cantidad){
	for(int i=0; i<NUM; i++){
		if(carrito.claveP[i]==clave){
			if(carrito.cantidad[i]<cantidad){
				carrito.total=carrito.total-(carrito.precio[i]*cantidad);
				carrito.cantidad[i]=carrito.cantidad[i]-cantidad;
				return;
			}else if(carrito.cantidad[i]==cantidad){
				eliminarProducto(carrito,clave);
				return;
			}else{
				cout<<"\nLa cantidad ingresada es mayor a la cantidad de producto en el carrito"<<endl;
				return;
			}
		}
	}
}

void cancelar(Cliente &carrito){
	for(int i=0; i<20; i++){
		carrito.cantidad[i]=0;
		carrito.claveP[i]=0;
		carrito.nombre[i]='0';
		carrito.precio[i]=0;
	}
	carrito.total=0;
}

void mostrarCarrito(Cliente &carrito){
	int x=0;
	cout<<"CLAVE\t"<<"NOMBRE\t\t"<<"PRECIO\t\t"<<"CANTIDAD"<<endl;
	while(carrito.claveP[x] !=-1){
		cout<<carrito.claveP[x]<<"\t"<<carrito.nombre<<"\t\t"<<carrito.precio<<"\t\t"<<carrito.cantidad<<endl;
		x +=1;
	}
	if(x !=0) cout<<"\nTOTAL: "<<carrito.total<<endl;
}

void mostrarCliente(Nodo2 *&lista,int &clave){
	Nodo2 *auxlista = new Nodo2();
	auxlista=lista;
	if(auxlista==NULL){
		cout<<"\nSin ningun registro"<<endl;
		return;
	}else{
		while((auxlista !=NULL)&&(auxlista->carrito.folio !=clave)){
			auxlista=auxlista->siguiente;
		}
		if(auxlista==NULL){
			cout<<"\nNo se encontro el registro."<<endl;
			return;
		}else{
			int x=0;
			cout<<"\nFOLIO DEL CLIENTE: "<<auxlista->carrito.folio<<endl;
			cout<<"CLAVE\t"<<"NOMBRE\t\t"<<"PRECIO\t\t"<<"CANTIDAD"<<endl;
			for(int i=0; i<NUM; i++){
				if(auxlista->carrito.claveP[i] !=-1){
					cout<<auxlista->carrito.claveP[i]<<"\t"<<auxlista->carrito.nombre[i]<<"\t\t"<<auxlista->carrito.precio[i]<<"\t\t"<<auxlista->carrito.cantidad[i]<<endl;
				}
			}
			cout<<"\nTOTAL DE COMPRA: "<<auxlista->carrito.total<<endl;
			return;
		}
	}
	
}

void rellenar(Cliente &carrito){
	for(int i=0; i<20; i++){
		carrito.claveP[i]=-1;
	}
}
