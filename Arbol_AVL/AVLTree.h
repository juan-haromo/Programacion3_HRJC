#ifndef AVL_TREE_H
#define AVL_TREE_H

#include<iostream>
#include<iomanip>
#include<algorithm>
#include<memory>

//Plantilla para el nodo, asi puede guardar cualquier dato
template <typename T>

//Clase anidada nodo
class Node {
public:
    T data; //Información que guarda el nodo
    int height; //Altura a la que se encuentra el nodo
    std::shared_ptr<Node<T>> left; //Puntero inteligente a su hijo izquierdo
    std::shared_ptr<Node<T>> right; //Puntero inteligente a su hijo derecho

    //Constructor explicito
    //Recibe un parámetro, data que se guarda en la variable data
    //El resto de datos quedan por defecto
    Node(T data) : data(data), height(1), left(nullptr), right(nullptr) {}
};

//Plantilla que el árbol puede recibir cualquier dato
template <typename T>

//Clase principal AVLTree 
class AVLTree {
public:
    std::shared_ptr<Node<T>> root; //Puntero inteligente al nodo raíz

    AVLTree(): root(nullptr) {} // Constructor implícito, guarda el puntero raíz como nulo


    //Agregar nodo
    //Se recibe la información a insertar como parámetro
    void add(T data) {
        //Llama al método privado insertar, para colocar el nodo en su posición
        root = insert(root, data);
    }

    //Eliminar nodo
    //Recibe información de un nodo, la cual si es encontrada borraran el nodo
    void remove(T data)  {
        //Llamada al método interno de borrar para encontrar y eliminar el nodo con la información si existiera
        root = deleteNode(root, data);
    }

    //Imprimir
    void print() {
        //Si el árbol no esta vació
        if (root != nullptr) {
            print(root, 0);
        } 
        //Si el árbol esta vació
        else {
            std::cout << "The tree is empty." << std::endl;
        }
    }

private:
    //Función recursiva para imprimir
    //Recibe un puntero a un nodo y una indentation
    void print(std::shared_ptr<Node<T>> node, int indent) {
        if(node) {
            //Sigue el camino del arbol derecho
            if(node->right) {
                print(node->right, indent + 8);
            }
            //Pone el indent antes de imprimir
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            //Imprime el camino del arbol derecho 
            if (node->right) {
                std::cout << " / (Right of " << node->data << ")\n" << std::setw(indent) << ' ';
            }
            std::cout << node->data << "\n" ;
            //Sigue e imprime el camino izquierdo del arbol
            if (node->left) {
                std::cout << std::setw(indent) << ' ' << " \\ (Left of " << node->data << ")\n";
                print(node->left, indent + 8);
            }
        }
    }

    //Funcion interna para crear un nodo
    std::shared_ptr<Node<T>> newNode(T data) {
        return std::make_shared<Node<T>>(data);
    }


    //Rotación derecha para rebalance
    //Recibe el nodo sub-raíz "y" a rebalance
    std::shared_ptr<Node<T>> rightRotate(std::shared_ptr<Node<T>> y) {
        
        std::shared_ptr<Node<T>> x = y->left; //Guardamos el hijo izquierdo de "y" con el nombre "x"
        std::shared_ptr<Node<T>> T2 = x->right; //Guardamos el hijo derecho de "x" con el nombre "T2"

        x->right = y; //Hacemos que el hijo derecho de "x" sea "y"
        y->left = T2; //Hacemos que el hijo izquierdo de "y" sea "T2"

        y->height = max(height(y->left), height(y->right))+1; //Actualizamos la altura de y
        x->height = max(height(x->left), height(x->right))+1; //Actualizamos la altura de x

        //Rebalances el árbol y regresamos el nuevo nodo sub-raíz "x"
        return x;
    }

    //Rotación izquierda para rebalance
    //Recibe el nodo sub-raíz "x" a rebalance
    std::shared_ptr<Node<T>> leftRotate(std::shared_ptr<Node<T>> x) {
        std::shared_ptr<Node<T>> y = x->right; //Guardamos el hijo derecho de "x" con el nombre "y"
        std::shared_ptr<Node<T>> T2 = y->left; //Guardamos el hijo izquierdo de "y" con el nombre "T2"

        y->left = x; //Hacemos que el hijo izquierdo de "y" sea "x"
        x->right = T2;//Hacemos que el hijo derecho de "x" sea "T2"

        x->height = max(height(x->left),height(x->right))+1; //Actualizamos la altura de x
        y->height = max(height(y->left),height(y->right))+1; //Actualizamos la altura de y

        //Rebalances el árbol y regresamos el nuevo nodo sub-raíz "y"
        return y;
    }

    //Regresa el factor de equilibrio de un nodo
    int getBalance(std::shared_ptr<Node<T>> N) {
        
        //Si el nodo es hoja su valor de equilibrio es 0
        if (N == nullptr){return 0; }

        //Si no lo es se obtiene con la altura del sub-árbol izquierdo menos la altura del sub-árbol derecho
        else{ return height(N->left) - height(N->right); }    
        
    }

    //Función interna Insertar
    std::shared_ptr<Node<T>> insert(std::shared_ptr<Node<T>> node, T data) {
        //Una vez llegado a un puntero nulo de un nodo hoja se crea un nuevo nodo con la información pasada
        if (node == nullptr){
            return (newNode(data));
        }

        //Si el nodo no es nulo y si información es menor a la del nodo se continua con una búsqueda recursiva por el nodo izquierdo
        if (data < node->data){
            node->left = insert(node->left, data);
        }

        //Si el nodo no es nulo y si información es mayor a la del nodo se continua con una búsqueda recursiva por el nodo derecho
        else if (data > node->data){
            node->right = insert(node->right, data);
        }

        //Si ya existe un nodo con dicha información se regresa ese nodo
        else{
            return node;
        }
            
        //Se calcula la altura del nodo
        node->height = 1 + max(height(node->left), height(node->right));

        //Se obtiene el factor de equilibrio del nuevo nodo
        int balance = getBalance(node);

        //Revision de equilibrio

        //Caso de desbalance izquierda-izquierda
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        //Caso de desbalance derecha-derecha
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        //Caso de desbalance izquierda-derecha
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left); //Realizamos una rotación izquierda en el hijo izquierdo de la sub-raíz
            return rightRotate(node); //Realizamos una rotación derecha en la sub-raíz
        }

        //Caso de desbalance derecha-izquierda
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right); //Realizamos una rotación derecha en el hijo derecho de la sub-raíz
            return leftRotate(node); //Realizamos una rotación izquierda en la sub-raíz
        }

        //No hay problema de balance
        return node;
    }

    //Buscar el nodo de menor valor
    std::shared_ptr<Node<T>> minValueNode(std::shared_ptr<Node<T>> node) {
        std::shared_ptr<Node<T>> current = node;

        //Se avanza continuamente por el nodo izquierdo hasta llegar a la hoja mas izquierda (valor mínimo del sub-árbol)
        while (current->left != nullptr){
            current = current->left;
        }
            
        //Se regresa el nodo encontrado
        return current;
    }

       //Buscar el nodo de mayor valor
    std::shared_ptr<Node<T>> maxValueNode(std::shared_ptr<Node<T>> node) {
        std::shared_ptr<Node<T>> current = node;

        //Se avanza continuamente por el nodo derecho hasta llegar a la hoja mas derecha (valor máximo del sub-árbol)
        while (current->right != nullptr){
            current = current->right;
        }
            
        //Se regresa el nodo encontrado
        return current;
    }

    //Eliminar nodo
    std::shared_ptr<Node<T>> deleteNode(std::shared_ptr<Node<T>> root, T data) {
        
        //Si no existe el nodo se regresa sin eliminar nada
        if (!root){ return root; }    

        //Busca el nodo a borrar por el sub-árbol izquierdo
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        }
        //Busca el nodo a borrar por el sub-árbol derecho
        else if(data > root->data) {
            root->right = deleteNode(root->right, data);
        }

        //Reacomodo de los nodos hijos
        else {
            //Si solo se tiene un hijo, ese hijo toma el lugar del padre
            if(!root->left || !root->right) {
                root = (root->left) ? root->left : root->right;
            }
            //Si tiene dos hijos, busca el nodo de mor valor en el sub árbol derecho y lo convierte en la nueva sub-raíz
            else {
                std::shared_ptr<Node<T>> temp = minValueNode(root->right);
                root->data = temp->data;
                //Elimina el nodo original que se convirtió en la nueva sub-raíz
                root->right = deleteNode(root->right, temp->data);
                temp.reset();
            }
        }

        //No se encontró nodo con la información solicitada, nada que borrar
        if(!root){ return root; }
            

        //Se calcula la altura del nodo
        root->height = 1 + max(height(root->left), height(root->right));

        //Se obtiene el factor de equilibrio del nuevo nodo
        int balance = getBalance(root);

        //Revision de equilibrio

        //Caso de desbalance izquierda-izquierda
        if (balance > 1 && getBalance(root->left) >= 0){
            return rightRotate(root);
        }

        //Caso de desbalance derecha-derecha
        if (balance < -1 && getBalance(root->right) <= 0){
            return leftRotate(root);
        }

        //Caso de desbalance izquierda-derecha
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left); //Realizamos una rotación izquierda en el hijo izquierdo de la sub-raíz
            return rightRotate(root); //Realizamos una rotación derecha en la sub-raíz
        }

        //Caso de desbalance derecha-izquierda
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);//Realizamos una rotación derecha en el hijo derecho de la sub-raíz
            return leftRotate(root); //Realizamos una rotación izquierda en la sub-raíz
        }

        //No hay problema de balance
        return root;
    }

    //Altura
    //Si el nodo existe regresa su altura
    //Si no existe regresa 0
    int height(std::shared_ptr<Node<T>> N) {
        if (N == nullptr){ return 0; }
        else{ return N->height; }        
    }

    //Función comparador
    //Regresa el mayor de los dos valores pasados
    int max(int a, int b) {
        return (a > b)? a : b;
    }
};

#endif /* AVL_TREE_H */