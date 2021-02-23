#include "Quadtree.h"
#include "Collidable.h"
#include <iostream>
#include <math.h>
#include <vector>

//se creaa un nodo raiz vacio
QuadNode::QuadNode(int x_, int y_, int w_, int h_, std::string n, size_t l, int cW):
    bounds(x_,y_,w_,h_), data(0)
{
    cellWidth=cW;
    lvl=l;
    name=n;
    this->NW = nullptr;
    this->NE = nullptr;
    this->SE = nullptr;
    this->SW = nullptr;
}

QuadNode::~QuadNode(){
    for(int i=0; i<data.size(); i++){
        if(data[i]!=NULL){
            delete data[i];
            data[i]=NULL;
        }
    }
    if (NW != nullptr) delete NW;
    if (NE != nullptr) delete NE;
    if (SW != nullptr) delete SW;
    if (SE != nullptr) delete SE;
}

//si no fuera una hoja, ningun puntero podria ser nulo
bool QuadNode::isLeaf(){return NW==nullptr;}


bool QuadNode::insert(Collidable *point){//Método que inserta puntos en el árbol
    if(!bounds.contains(*point)){
        return false;
    }
    if(isLeaf()){  //Si es una hoja el punto se inserta en este nodo

        if (data.size() < capacity){
            data.push_back(point);
            return true;
        }
        split(); //Si el nodo alcanza su capacidad máxima se divide
    }
    //Si no es una hoja o se divide, inserta el punto en el primer punto que le sea posible
    if(NW->insert(point)){
        return true;
    }
    if(NE->insert(point)){
        return true;
    }
    if(SW->insert(point)){
        return true;
    }
    if(SE->insert(point)){
        return true;
    }
    
    return false;

}

void QuadNode::split(){ //método que divide el nodo en 4 subnodos
    int x= bounds.getxInit();
    int y= bounds.getyInit();
    int w= bounds.getxEnd();
    int h= bounds.getyEnd();
    int dX=(w - x)/2;
    int dY=(h - y)/2;
    std::vector<Collidable*> aux;

    if(dX%cellWidth!=0)
        dX = dX - dX%cellWidth + cellWidth;

    if(dY%cellWidth!=0)
        dY = dY - dY%cellWidth + cellWidth;

    //creacion de los 4 nodos hijos segun el limite de su respectivo cuadrante
    NW= new QuadNode( x, y, x + dX, y + dY, "NW", lvl+1, cellWidth);
    NE= new QuadNode( x + dX, y, w, y + dY, "NE", lvl+1, cellWidth);
    SW= new QuadNode( x, y + dY, x + dX, h, "SW", lvl+1, cellWidth);
    SE= new QuadNode( x + dX, y + dY, w, h, "SE", lvl+1, cellWidth);

    // encuentra un hijo en el cual incluir cada punto de los que estan en data[]
    for(int i = 0; i < data.size(); i++){
        if(NW->insert(data[i])){
            continue;
        }
        if(NE->insert(data[i])){
            continue;
        }
        if(SW->insert(data[i])){
            continue;
        }
        if(SE->insert(data[i])){
            continue;
        }
        aux.push_back(data[i]);
    }

    while(data.empty()!=true)
        data.pop_back();

    for(size_t i=0; i<aux.size();i++){
        data.push_back(aux[i]);
    }
}

bool QuadNode::erase(float x, float y){
    bool coll=false;
    if(bounds.contains(x,y)==false){
        return false;
    }

    for(int i=0; i<data.size(); i++){
        if(data[i]->detectCollision(x, y, 0, 0)==true){
            delete data[i];
            data.erase(data.begin()+i);
            coll=true;
        }
    }
    if(isLeaf()==false){
        coll= coll || NW->erase(x, y);
        coll= coll || NE->erase(x, y);
        coll= coll || SW->erase(x, y);
        coll= coll || SE->erase(x, y);
    }
    return coll;
}

bool QuadNode::erase(circle &pPos){
//    std::cout<<"erase col"<<std::endl;

    bool coll=false;
    if(bounds.contains(pPos)==false){
        return false;
    }

    for(int i=0; i<data.size(); i++){
        if(data[i]->detectCollision(pPos, 0, 0)==true){
//            std::cout<<"eliminado"<<std::endl;
            delete data[i];
            data.erase(data.begin()+i);
            coll=true;
        }
    }
    if(isLeaf()==false){
        coll= coll || NW->erase(pPos);
        coll= coll || NE->erase(pPos);
        coll= coll || SW->erase(pPos);
        coll= coll || SE->erase(pPos);
    }
    return coll;
}

bool QuadNode::detectCollision(circle &c, float dX, float dY, std::vector<Collidable*> &col){
    bool coll=false;
    
    circle auxC={c.x+dX,c.y+dY,c.radius};
    if(bounds.contains(auxC)==false){
        return false;
    }


    for(int i=0; i<data.size(); i++){
        if(data[i]->detectCollision(c, dX,dY)==true){
//            std::cout<<"colision detectada"<<std::endl;
            col.push_back(data[i]);
            coll=true;
        }
    }
    if(isLeaf()==false){
        coll= coll || NW->detectCollision(c, dX, dY, col);
        coll= coll || NE->detectCollision(c, dX, dY, col);
        coll= coll || SW->detectCollision(c, dX, dY, col);
        coll= coll || SE->detectCollision(c, dX, dY, col);
    }
    return coll;
}

std::ostream & operator<< (std::ostream &os, QuadNode &n){
    os<<"name: "<<n.name<<std::endl;
    os<<"lvl: "<<n.lvl<<std::endl;

    os<<"bounds: "<<std::endl;
    os<<n.bounds;

    os<<"data: "<<std::endl;
    for(int i=0;i<n.data.size(); i++){
        os<<"elemento: "<<i<<std::endl;
        os<<*n.data[i];
    }
    return os;
}
