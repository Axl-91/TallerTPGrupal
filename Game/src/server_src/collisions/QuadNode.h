#ifndef _QUADNODE_H_
#define _QUADNODE_H_

#include <string>
#include "Collidable.h"
#include "Rectangle.h"
#include "../../common_src/types.h"

#define CAP 16 //Capacidad de nodos y arbol

class QuadNode{
    std::string name;
    size_t lvl;
    static const int capacity = CAP;
    int cellWidth;
    Rectangle bounds; //rectangulo del perimetro del qt
    std::vector<Collidable*> data; //arreglo con los puntos almacenados en el QuadTree

public:
    QuadNode *NW; //nodo hijo noroeste
    QuadNode *NE; //nodo hijo noreste
    QuadNode *SW; //nodo hijo suroeste
    QuadNode *SE; //nodo hijo sureste
    
    QuadNode(){}

    QuadNode(int x_, int y_, int w_, int h_, std::string n,size_t l, int cW);
    ~QuadNode();
    bool insert(Collidable *point); // Método que inserta un punto en el quadtree
    bool isLeaf();
    void query_colision();
    bool detectCollision(circle &c, float dX, float dY, std::vector<Collidable*> &col);
    friend std::ostream & operator<<(std::ostream &os, QuadNode &n);

    bool erase(float x, float y);
    bool erase(circle &pPos);


private:
    void split();
};



#endif
