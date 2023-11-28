#include <iostream>
#include <string>
using namespace std;

template<class T>
class LSLSE;

class SocioClub {
public:
    int numSocio;
    string nomSocio;
    string domicilio;
    int fechaIng;

    SocioClub(int nSocio, string nomSocio, string domc, int fIng) {
        numSocio = nSocio;
        nomSocio = nomSocio;
        domicilio = domc;
        fechaIng = fIng;
    }
    SocioClub() {
        numSocio = 0;
        nomSocio = "NULL";
        domicilio = "NULL";
        fechaIng = 0;
    }

    SocioClub& operator=(const SocioClub& x)
    {
        if (this != &x)
        {
            numSocio = x.numSocio;
            nomSocio = x.nomSocio;
            domicilio = x.domicilio;
            fechaIng = x.fechaIng;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& o, SocioClub& socio) {
        o << "\t\nNumero del socio: " << socio.numSocio << "\t\nNombre del socio: " << socio.nomSocio << "\t\nDomicilio del socio: " << socio.domicilio << "\t\nAnyo de ingreso: " << socio.fechaIng << "\n" << endl;
        return o;
    }

    friend std::istream& operator>>(std::istream& o, SocioClub& socio) {
        std::cout << "Ingresa el numero del socio: ";o >> socio.numSocio;cin.ignore();
        std::cout << "Ingresa el nombre del socio: ";getline(o, socio.nomSocio);
        std::cout << "Ingresa el domicilio del socio: ";getline(o, socio.domicilio);
        std::cout << "Ingresa el anyo de ingreso del socio: ";o >> socio.fechaIng;cin.ignore();
        return o;
    }

    bool operator ==(SocioClub& socio) {
        return ((numSocio == socio.numSocio) && (domicilio == socio.domicilio));
    }

    bool operator !=(SocioClub& socio) {
        return ((numSocio != socio.numSocio) && (domicilio != socio.domicilio));
    }

    SocioClub operator+(const SocioClub& sum) const {
        SocioClub resultado(numSocio + sum.numSocio, nomSocio + sum.nomSocio, domicilio + sum.domicilio, fechaIng + sum.fechaIng);
        return resultado;
    }

    bool operator<(const SocioClub& menq) const {
        return numSocio < menq.numSocio;
    }

    bool operator>(const SocioClub& mayq) const {
        return numSocio > mayq.numSocio;
    }

    bool operator<=(const SocioClub& meniq) const {
        return numSocio <= meniq.numSocio;
    }

    bool operator>=(const SocioClub& mayiq) const {
        return numSocio >= mayiq.numSocio;
    }
};

template<class T>
class node {
private:
    T data;
    node<T>* sig;
public:
    node() :sig(nullptr) {};
    friend class LSLSE<T>;
};

template<class T>
class LSLSE {
private:
    node<T>* lista;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);

public:
    LSLSE() :lista(nullptr) {};
    bool vacia()const;
    void enqueue(T elem);
    void dequeue();
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    node <T>* buscar(SocioClub soc)const;
    
    void imprimir()const;
    int total()const;
};

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = lista->sig;
    }
    else {
        anterior(pos)->sig = pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem) {
    node<T>* aux = new node<T>;
    aux->data = elem;
    if (pos == nullptr) {
        aux->sig = lista;
        lista = aux;
    }
    else {
        aux->sig = pos->sig;
        pos->sig = aux;
    }
}

template<class T>
void LSLSE<T>::enqueue(T elem) {
    insertar(ultimo(), elem);
}

template<class T>
void LSLSE<T>::dequeue() {
    eliminar(lista);
}

template<class T>
void LSLSE<T>::imprimir()const {
    node<T>* aux = lista;
    while (aux != nullptr) {
        std::cout << aux->data;
        aux = aux->sig;
    }
}

template<class T>
int LSLSE<T>::total()const {
    node<T>* aux = lista;
    int cont = 0;
    while (aux != nullptr) {
        cont++;
        aux = aux->sig;
    }
    return cont;
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux != nullptr && aux->sig != pos) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero()const {
    if (vacia()) {
        return nullptr;
    }
    return lista;
}


template<class T>
node<T>* LSLSE<T>::ultimo()const {
    if (vacia()) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
bool LSLSE<T>::vacia()const {
    if (lista == nullptr)
        return true;
    return false;
}

template<class T>
node<T>* LSLSE<T>::buscar(SocioClub soc)const {
    node<T>* aux;
    aux = lista;
    while (aux != nullptr) {
        if (soc == aux->data) {
            return aux;
        }
        aux = aux->sig;
    }
    return nullptr;
}

int main()
{
    LSLSE<SocioClub> milista;
    SocioClub x, aux;
    string tmpDom;
    int opc, nSocios = 0, tmpNum;
    while (1) {
        system("cls");
        cout << "\t\tSistema de administracion de Socios\n\tSelecciona la operacion a realizar del siguiente menu" << endl;
        cout << "1. Registrar Socio\n2. Dar de baja a Socio\n3. Reporte de Socios\n4. Busqueda de Socio\n5. Total de Socios\n6. Salir\n\tTu seleccion: ";cin >> opc;cin.ignore();

        switch (opc) {
        case 1:system("cls");
            std::cout << "\tREGISTRAR SOCIO:\n";cin >> x;

            milista.enqueue(x);nSocios++;
            cout << "Socio registrado con exito" << endl;
            system("PAUSE");
            break;

        case 2:system("cls");
            std::cout << "\tDAR DE BAJA A SOCIO:\n";;
            if (!milista.vacia())
            {
                milista.dequeue();
                std::cout << "\nSocio eliminado con exito" << endl;
            }
            else
            {
                cout << "ERROR: Lista vacia" << endl;
            }
            system("PAUSE");
            break;

        case 3:
            system("cls");cout << "LISTA Y DATOS DE SOCIOS: " << endl;
            if (!milista.vacia())
            {
                milista.imprimir();
            }
            else
            {
                cout << "ERROR: Lista vacia" << endl;
            }
            system("PAUSE");
            
            break;

        case 4:system("cls");
            std::cout << "\tBUSQUEDA DE SOCIO:\n";
            cout << "Ingresa el numero del socio: ";cin >> aux.numSocio;cin.ignore();
            cout << "Ingresa el domicilio del socio: ";cin >> aux.domicilio;cin.ignore();
            if (milista.buscar(aux) != nullptr)
            {
                cout << "El Socio si se encuentra registrado" << endl;
            }
            else
            {
                cout << "Socio no encontrado" << endl;
            }
            system("PAUSE");
            break;

        case 5:system("cls");
            cout << "TOTAL DE SOCIOS REGISTRADOS: " << milista.total() << endl;
            system("PAUSE");
            break;

        case 6:exit(0);break;
        default: std::cout << "Ingresa una opcion valida";system("PAUSE");
        }
    }
    return 0;
}