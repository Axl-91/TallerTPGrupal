#include <iostream>
#include "Quadtree.h"
#include "QuadNode.h"
#include "Collidable.h"

//se crea cargando el mapa
Quadtree::Quadtree(int rows, int cols, std::vector<std::vector<int>> map, int cellWidth):
root(0, 0, cols*cellWidth, rows*cellWidth, "root", 1, cellWidth){
    int i,j;
    Collidable *maker;
    Collidable *aux;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            if(map[i][j]!=0){
                if((aux=maker->makeCollidable(j, i, cellWidth, map[i][j]))!=NULL)
                root.insert(aux);
            }
        }
    }
}

//elimina el elemento en contacto con el circulo
void Quadtree::erase(circle pPos){
    root.erase(pPos);
}

//elimina el elemento en el punto (x,y)
void Quadtree::erase(float x, float y){
    root.erase(x, y);
}



void Quadtree::insert(float x, float y, int cellWidth, int value){
    Collidable *maker;
    root.insert(maker->makeCollidable(x, y, cellWidth, value));
}


Quadtree::~Quadtree() {}


void Quadtree::detectCollision(circle &c, float dX, float dY, std::vector<Collidable*> &col){
    root.detectCollision(c,dX,dY,col);
}

void Quadtree::print(std::ostream &os){
    std::queue<QuadNode> q;
    q.push(root);

    while(q.empty()!=true)
    {
        if(q.front().isLeaf()==false){
            q.push(*(q.front().NW));
            q.push(*(q.front().NE));
            q.push(*(q.front().SW));
            q.push(*(q.front().SE));
        }
        os<<q.front();
        q.pop();
    }

}
