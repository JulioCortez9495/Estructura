#include<iostream> // Biblioteca principal
#include<string> // Permite la cadena de caracteres
#include<locale.h> // Para seleccionar el idioma español.
#include<stdio.h> // Permite almacenar los datos proporcionados en la ejecución.
#include<conio.h>// Para ocultar la contraseña.
#include <iomanip> // Permite que el programa de la precisión decimal de números.
#include <sstream> // Incluimos la biblioteca sstream para usar stringstream.
#include <cstdlib> // Incluimos la librería cstdlib para usar exit.
#include <fstream> // Para manejo de archivos.
#include<windows.h> // Incluir esta biblioteca para manejar colores en Windows

using namespace std;

#define DEFAULT_COLOR 7   // Blanco
#define MENU_COLOR 10     // Verde
#define ERROR_COLOR 12    // Rojo
#define BLUE_COLOR 9 // Azul

// ----------------------------------------------------------

float IGV = 0.18;

struct producto{
    int codigo;
    string nombre;
    string categoria;
    int cantidades;
    float precio;
};
// int& es para que se vincule de manera general en el codigo usando funciones y que se cambie la variable sin problemas.
void usuario(int a);
void menu_admin(producto[], int&, int&);
void menu_emple(producto[], int&, int&);

int RegistrarProducto(producto[], int&);
void MostrarLista(producto[], int);
int RealizarVenta(producto[], int, int&);
int QuitarProducto(producto[], int&);

void Informe(producto[], int, int&);

// Función para establecer color en la consola
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// ----------------------------------------------------------

int main(){
    setlocale(LC_ALL, "spanish");
    
    producto prod[50];
    
    int op;
    int n = 1;
    int ventato = 0;

    bool repetir = true;
    
    while(repetir){
        system("cls");
        setColor(MENU_COLOR);
    	cout << "Seleccione su perfil:" << endl;
    	cout << "1. Administrador" << endl;
    	cout << "2. Empleado" << endl;
    	cout << endl;
    	cout << "Ingrese su opción: ";
    	setColor(DEFAULT_COLOR);
        cin>>op;
        
        usuario(op);
        
        bool activa = true;
        
        while(activa){
            switch(op){
                case 1:
                    menu_admin(prod, n, ventato);
                    activa = false; // Salir del menú de admin
                break;
                
                case 2:
                    menu_emple(prod, n, ventato);
                    activa = false; // Salir del menú de empleado
                break;
                
                default:
                	setColor(ERROR_COLOR);
                    cout << "[ ERROR ] OPCIÓN NO VÁLIDA. INTENTE NUEVAMENTE" << endl;
                    cout << endl;
                    
                    setColor(MENU_COLOR);
                    cout << "Por favor, seleccione su perfil:" << endl;
    				cout << "1. Administrador" << endl;
    				cout << "2. Empleado" << endl;
    				cout << endl;
    				cout << "Ingrese su opción: ";
    				setColor(DEFAULT_COLOR);
                    cin.clear(); // Limpiar estado de cin
                    cin >> op; // Volver a leer la opción
                    usuario(op); // Volver a validar la opción
                break;
            }
        }
    }
    
    return 0;
}

// ----------------------------------------------------------

void usuario(int a){
    setlocale(LC_ALL, "spanish");
    
    system("cls");
    
    string input;
    char contra;
    
    switch(a){
        case 1:
            do{
                system("cls");
                setColor(DEFAULT_COLOR);
                cout << "                    SEGURIDAD                " << endl << endl;
                cout << "Ingrese su contrasena: ";
                
                while ((contra = _getch()) != '\r') {
                    cout << "*";
                    input += contra;
                }
                
                if(input != "ADMIN"){
                    cout<<endl;
                    setColor(ERROR_COLOR);
                    cout << "[ ERROR ] CONTRASENA INCORRECTA. VUELVA A INTENTAR" << endl;
                    setColor(DEFAULT_COLOR);
                    system("pause");
                    input.clear();
                }
            }while("ADMIN" != input);
            
            cout << endl;
            setColor(BLUE_COLOR);
            cout << "Hola Bienvenido al Sistema" << endl;
			setColor(DEFAULT_COLOR); 
        break;
        
        case 2:
            do{
                system("cls");
                setColor(DEFAULT_COLOR);
                cout << "                    SEGURIDAD                " << endl << endl;
                cout << "Ingrese su contrasena: ";
                
                while ((contra = _getch()) != '\r') {
                    cout << "*";
                    input += contra;
                }
                
                if(input != "12345"){
                    cout<<endl;
                    setColor(ERROR_COLOR);
                    cout<<"[ ERROR ] CONTRASENA INCORRECTA. VUELVA A INTENTAR"<<endl;
                    setColor(DEFAULT_COLOR);
                    system("pause");
                    input.clear();
                }
            }while("12345" != input);
            
            cout<<endl;
            setColor(BLUE_COLOR);
            cout<<"Hola Bienvenido al Sistema"<<endl;
			setColor(DEFAULT_COLOR); 
        break;
    }
}

// ----------------------------------------------------------

void menu_admin(producto prod[], int &n, int &ventato){
	setlocale(LC_ALL, "spanish");
    int opm;
    bool rep = true;
    
    while(rep){
        system("cls");
        setColor(MENU_COLOR);
        cout << "                    MENÚ PRINCIPAL                " << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Mostrar lista de productos" << endl;
        cout << "3. Quitar producto" << endl;
        cout << "4. Informe del día" << endl;
        cout << "5. Cambiar de usuario" << endl;
        cout << "6. Salir" << endl;
        setColor(DEFAULT_COLOR);
        cout << "Ingrese una opción: ";
        cin >> opm;
        
        switch(opm){
            case 1:
                RegistrarProducto(prod, n);
                system("pause");
            break;
            
            case 2:
                if (n > 1) {
                    MostrarLista(prod, n);
                } else {
                	setColor(ERROR_COLOR);
                    cout << "[ ERROR ] NO HAY NINGUN PRODUCTO REGISTRADO" << endl << endl;
                    setColor(DEFAULT_COLOR);
                }
                system("pause");
            break;
            
            case 3:
                if (n > 1) {
                    QuitarProducto(prod, n);
                } else {
                	setColor(ERROR_COLOR);
                    cout << "[ ERROR ] NO HAY NINGUN PRODUCTO REGISTRADO" << endl << endl;
                    setColor(DEFAULT_COLOR);
                }
                system("pause");
            break;
            
            case 4:
                Informe(prod, n, ventato);
                system("pause");
            break;
            
            case 5:
                rep = false;
            break;
            
            case 6:
                rep = false;
                exit(0);
            break;
        }
    }
}

// ----------------------------------------------------------

void menu_emple(producto prod[], int &n, int &ventato){
    setlocale(LC_ALL, "spanish");
    int opm;
    bool rep = true;
    
    while(rep){
        system("cls");
        setColor(MENU_COLOR);
        cout << "                    MENÚ PRINCIPAL                " << endl;
        cout << "1. Mostrar lista de productos" << endl;
        cout << "2. Realizar Venta" << endl;
        cout << "3. Cambiar de usuario" << endl;
        cout << "4. Salir" << endl;
        setColor(DEFAULT_COLOR);
        cout << "Ingrese una opcion: ";
        cin >> opm;
                
        switch(opm){
            case 1:
                if (n > 1) {
                    MostrarLista(prod, n);
                } else {
                	setColor(ERROR_COLOR);
                    cout << "[ ERROR ] NO HAY NINGUN PRODUCTO REGISTRADO" << endl;
                    setColor(DEFAULT_COLOR);
                }
                system("pause");
            break;
            
            case 2:
                if (n > 1) {
                    RealizarVenta(prod, n, ventato);
                } else {
                	setColor(ERROR_COLOR);
                    cout << "[ ERROR ] NO HAY NINGUN PRODUCTO REGISTRADO" << endl;
                    setColor(DEFAULT_COLOR);
                }
                system("pause");
            break;
                
            case 3:
                rep = false;
            break;
            
            case 4:
                rep = false;
                exit(0);
            break;
        }
    }    
}

// ----------------------------------------------------------

int RegistrarProducto(producto prod[], int &n) {
    setlocale(LC_ALL, "spanish");
    char conf;
    do {
        system("cls");
        setColor(MENU_COLOR);
        cout << "Agregar Producto" << endl << endl;
        cout << "\tAsignarle un código al producto: ";
        cin >> prod[n].codigo;
        cin.ignore();
        cout << "\tNombre del producto: ";
        getline(cin, prod[n].nombre);
        cout << "\tCategoria del producto: ";
        getline(cin, prod[n].categoria);
        cout << "\tCantidades disponibles: ";
        cin >> prod[n].cantidades;
        cin.ignore();  // Ignora el carácter de nueva línea después de la entrada del precio
        cout << "\tPrecio unitario: ";
        cin >> prod[n].precio;
        cin.ignore();  // Ignora el carácter de nueva línea que queda en el búfer de entrada
        cout << endl;
        setColor(BLUE_COLOR);
        cout << "SE REGISTRO: " << endl << endl;
        cout << "\tNombre:\t\t" << prod[n].nombre << endl;
        cout << "\tCategoria:\t" << prod[n].categoria << endl;
        cout << "\tCantidades:\t" << prod[n].cantidades << endl;
        cout << "\tPrecio:\t\t" << prod[n].precio << endl << endl;
        setColor(MENU_COLOR);
        cout << "\nEs correcta la informacion (S/N): ";
        setColor(DEFAULT_COLOR);
        cin >> conf;
        cin.ignore();  // Ignora el carácter de nueva línea después de leer el carácter conf
        
         // Almacenar en archivo
        ofstream productosFile("productos.csv", ios::app);
        if (productosFile.is_open()) {
            productosFile << prod[n].codigo << ","
                          << prod[n].nombre << ","
                          << prod[n].categoria << ","
                          << prod[n].cantidades << ","
                          << prod[n].precio << endl;
            productosFile.close();
        }
        
    } while (conf != 'S' && conf != 's');
    n = n + 1;
    return n;
}

// ----------------------------------------------------------

void MostrarLista(producto prod[], int n) {
    setlocale(LC_ALL, "spanish");
    int i;
    system("cls");
    if (n > 2) {
        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j <= (n - i - 1); j++) {
                if (prod[j].codigo > prod[j + 1].codigo) {
                    producto aux = prod[j];
                    prod[j] = prod[j + 1];
                    prod[j + 1] = aux;
                }
            }
        }
    }
    setColor(MENU_COLOR);
    cout << "Mostrar productos" << endl << endl;
    setColor(DEFAULT_COLOR);
    
    setColor(BLUE_COLOR);
    for (i = 1; i < n; i++) {
        cout << "\tCódigo:\t\t" << prod[i].codigo << "\t\tNombre: " << prod[i].nombre << "\t\tCantidades: " << prod[i].cantidades << endl;
    }
    cout << endl;
    setColor(DEFAULT_COLOR);
}

// ----------------------------------------------------------

int RealizarVenta(producto prod[], int n, int &ventato) {
    setlocale(LC_ALL, "spanish");
    string codOnom;
    char conf;
    int i, cen = 0, cant;
    float preigv, valor;
    system("cls");
    setColor(MENU_COLOR);
    cout << "Vender productos" << endl << endl;
    setColor(DEFAULT_COLOR);
    cout << "\tIngrese nombre o codigo del producto: ";
    cin >> codOnom;

    for (i = 1; i < n; i++) {
        stringstream ss;
        ss << prod[i].codigo;
        string codigo_str = ss.str();
        
        if (codOnom == codigo_str || codOnom == prod[i].nombre) {
        	cen = 1;
            do {
                cout << "\tCantidad vendida: ";
                cin >> cant;

                if (cant > prod[i].cantidades) {
                	cout << endl;
                	setColor(ERROR_COLOR);
                    cout << "\t[ ERROR ] LA CANTIDAD INGRESADA SUPERA LA CANTIDAD DISPONIBLE DEL PRODUCTO" << endl;
                    setColor(DEFAULT_COLOR);
                    cout << "\tCantidad disponible: " << prod[i].cantidades << endl;
                    cout << endl;
                }
            } while (cant > prod[i].cantidades);
        	
            valor = cant * prod[i].precio;
            preigv = valor + (valor * IGV);
            cout << endl;
            setColor(BLUE_COLOR);
            cout << "\tPrecio sin igv: " << fixed << setprecision(2) << valor << " soles" << endl;
            cout << "\tPrecio con igv: " << fixed << setprecision(2) << preigv << " soles" << endl << endl;
            setColor(MENU_COLOR);
            cout << "Realizar venta? (S/N):";
            setColor(DEFAULT_COLOR);
            cin >> conf;
            if (conf == 'S' || conf == 's') {
                prod[i].cantidades = prod[i].cantidades - cant;
                ventato = ventato + valor;
                setColor(BLUE_COLOR);
                cout << "SE REALIZO LA VENTA EXITOSAMENTE" << endl << endl;
                setColor(DEFAULT_COLOR);
                
                // Actualizar archivo después de la venta
                ofstream productosFile("productos.csv");
                if (productosFile.is_open()) {
                    for (int j = 1; j < n; j++) {
                        productosFile << prod[j].codigo << ","
                                      << prod[j].nombre << ","
                                      << prod[j].categoria << ","
                                      << prod[j].cantidades << ","
                                      << prod[j].precio << endl;
                    }
                    productosFile.close();
                }
            }
        }
    }
    if (cen == 0) {
    	setColor(ERROR_COLOR);
        cout << "\t[ ERROR ] NO SE ENCONTRO EL PRODUCTO." << endl << endl;
        setColor(DEFAULT_COLOR);
    }
    return ventato;
}

// ----------------------------------------------------------

int QuitarProducto(producto prod[], int &n) {
    setlocale(LC_ALL, "spanish");
    int cen = 0, i, pos, j;
    string codOnom;
    char conf;
    system("cls");
    cout << "Quitar productos" << endl << endl;
    setColor(MENU_COLOR);
    cout << "\tIngrese nombre o codigo del producto a quitar: ";
    setColor(DEFAULT_COLOR);
    cin >> codOnom;

	// Convertimos codigo a string utilizando stringstream
    for (i = 1; i < n; i++) {
        stringstream ss;
        ss << prod[i].codigo;
        string codigo_str = ss.str();
        
        if (codOnom == codigo_str || codOnom == prod[i].nombre) {
            pos = i;
            cen = 1;
            setColor(MENU_COLOR);
            cout << "Quitar producto? (S/N):";
            setColor(DEFAULT_COLOR);
            cin >> conf;
            if (conf == 'S' || conf == 's') {
                for (j = pos; j < n; j++) {
                    prod[j] = prod[j + 1];
                }
                n = n - 1;
                setColor(BLUE_COLOR);
                cout << "SE ELIMINO EL PRODUCTO EXITOSAMENTE" << endl << endl;
                setColor(DEFAULT_COLOR);
                
                // Actualizar archivo después de quitar producto
            ofstream productosFile("productos.csv");
            if (productosFile.is_open()) {
                for (int j = 1; j < n; j++) {
                    productosFile << prod[j].codigo << ","
                                  << prod[j].nombre << ","
                                  << prod[j].categoria << ","
                                  << prod[j].cantidades << ","
                                  << prod[j].precio << endl;
                }
                productosFile.close();
            }

            }
        }
    }
    if (cen == 0) {
    	setColor(ERROR_COLOR);
        cout << "\t[ ERROR ] NO SE ENCONTRO EL PRODUCTO" << endl << endl;
        setColor(DEFAULT_COLOR);
    }
    return n;
}

// ----------------------------------------------------------

void Informe(producto prod[], int n, int &ventato) {
	setlocale(LC_ALL, "spanish");
	setColor(DEFAULT_COLOR);
    cout << endl << "Informe del día" << endl << endl;
    
    setColor(BLUE_COLOR);
    cout << "\tRecaudación total del día: " << fixed << setprecision(2) << ventato << endl;
    cout << "\tIGV acumulado del día: " << fixed << setprecision(2) << ventato * IGV << endl;
    cout << endl;
    cout << "NOTA: El IGV es independiente a las ventas " << endl;
    setColor(DEFAULT_COLOR);
    
     // Almacenar en archivo
    ofstream informeFile("informe_dia.csv", ios::app);
    if (informeFile.is_open()) {
        informeFile << "Recaudación total del día: " << fixed << setprecision(2) << ventato << " soles" << endl;
        informeFile << "IGV acumulado del día: " << fixed << setprecision(2) << ventato * IGV << " soles" << endl;
        informeFile << "----------------------------------------------" << endl;
        informeFile.close();
    }
}

