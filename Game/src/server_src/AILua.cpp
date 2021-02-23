#include "AILua.h"


AILua::AILua(float x, float y, float a, size_t anID,
            std::vector<std::vector<int>> &lvl):
            mapPlayer(lvl){
    position.x=x;
    position.y=y;
    position.radius=16;
    ang=a;
    ID=anID;
    moving = false;
    rotating = false;
}

void AILua::update(Player_t &p){
    if(p.ID == ID){
        updatePlayerInfo(p);
    } else {
        updateEnemy(p);
    }
}


void AILua::setID(size_t anID){
    ID = anID;
}
void AILua::updatePlayerInfo(Player_t &p){
        position.x = p.x;
        position.y = p.y;
        ang = p.ang;
        lifes = p.lifes;
        score = p.score;
        health = p.health;
        currentWeapon = p.currentWP;
        secondaryWeapon = p.secondaryWP;
        shootingState=p.shootingState;
}

void AILua::updateEnemy(Player_t &p){
    enemies[p.ID] = p;
}

void AILua::makeDecision(event_t &event){
    Vector aux;
    if(checkForEnemiesInSight(event, aux) == true){
        Vector posPropia(position.x, position.y);
        float distance = posPropia.getDistance(aux);
        float anguloObj = posPropia.getAngle(aux);
        if(anguloObj < 0)
            anguloObj += 2*PI;
        if(anguloObj >= 2*PI)
            anguloObj -= 2*PI;

        lua.getEvent(event, ang, anguloObj, distance, shooting, rotating, moving);
    } else{
        lua.getIdleEvent(event, rotating, moving);
    }
    return;
}

void addVectDist(std::vector<Player_t> &v, Player_t &p, Vector &pos){
    Vector auxV(p.x, p.y);
    float dist = pos.getDistance(auxV);
    for (auto i = v.begin(); i != v.end(); ++i){
        Player_t objVec = *i;
        Vector auxVec(p.x, p.y);
        float distV = pos.getDistance(auxVec);
        if (dist > distV){
            v.insert(i, p);
            return;
        }
    }
    v.push_back(p);
}

std::vector<Player_t> AILua::orderEnemies(Vector &pos){
    std::vector<Player_t> vectorAux;

    for (auto enemy : enemies){
        Vector posObjeto(enemy.second.x, enemy.second.y);
        addVectDist(vectorAux, enemy.second, pos);
    }
    return vectorAux;
}

bool AILua::checkForEnemiesInSight(event_t &event, Vector &auxVector){
    renderRaycaster();
    int one = 1;
    Vector posPlayer = Vector(position.x, position.y);
    std::vector<Player_t> orderedEnemies;
    orderedEnemies = orderEnemies(posPlayer);
    for (int obj = 0; obj < orderedEnemies.size(); ++obj){
        Vector enemyPos(orderedEnemies[obj].x, orderedEnemies[obj].y);
        
        if (!lua.isVisible(posPlayer,enemyPos, ang)){
            continue;
        }

        Vector pos(position.x, position.y);
        float distance = pos.getDistance(enemyPos); 
        float anguloObj = pos.getAngle(enemyPos);

        if(anguloObj < 0)
            anguloObj += 2*PI;
        if(anguloObj >= 2*PI)
            anguloObj -= 2*PI;

        float difAng = ang - anguloObj;

        if(difAng < 0)
            difAng += 2*PI;
        if(difAng >= 2*PI)
            difAng -= 2*PI;

        //se forma un triangulo rectangulo con posicion del jugador,
        //direccion de tiro y posicion del enemigo
        float op=sin(difAng)*distance; //cateto opuesto
        float ad=cos(difAng)*distance; //cateto adyacente
 
        int x = (int)(30*PI/180 + anguloObj- ang ) / 0.1875;
        if(distance < distBuffer[x] && distance < distBuffer[x+1]){
            float auxFloat = enemyPos.getX();
            auxVector.setX(auxFloat);
            auxFloat = enemyPos.getY();
            auxVector.setY(auxFloat);
            return true;
        }
    }
        return false;
}

void AILua::renderRaycaster(){
    Vector vectorPos(position.x, position.y);
    ShootingRaycaster raycaster(vectorPos, ang, mapPlayer);
    float angleRay = ang - PI/6;

    for (int pos=0; pos < LONG_SCREEN; ++pos){

        if (angleRay < 0){
            angleRay += 2*PI;
        } else if (angleRay > 2*PI){
            angleRay -=2*PI;
        }
        raycaster.makeRay(angleRay);
        distBuffer[pos] = raycaster.getDistance();
        angleRay += PI/960;
    }
}