#include "AILua.h"


AILua::AILua(float x, float y, float a, size_t anID,
            std::vector<std::vector<int>> &lvl):
            mapPlayer(lvl){
    position.x=x;
    position.y=y;
    position.radius=16;
    ang=a;
    ID=anID;
    attackModeOn = false;
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
        // inventory.setAmmo(p.ammo);
        health = p.health;
        currentWeapon = p.currentWP;
        secondaryWeapon = p.secondaryWP;
        shootingState=p.shootingState;
}

void AILua::updateEnemy(Player_t &p){
    enemies[p.ID] = p;
}

void AILua::setGameMap(std::vector<std::vector<int> > &aVector){

}

void AILua::makeDecision(event_t &event){
    attackModeOn = false;
    Vector aux;
    if(checkForEnemiesInSight(event, aux) == true){
        Vector posPropia(position.x, position.y);
        float distance = posPropia.getDistance(aux);
        float relativeAng = posPropia.getAngle(aux);
        if(relativeAng < 0)
            relativeAng += 2*PI;
        if(relativeAng >= 2*PI)
            relativeAng -= 2*PI;

        std::cout << "posPerro " << posPropia << std::endl;
        std::cout << "posPlayer: " << aux << std::endl;
        std::cout << "relativeAng: " << relativeAng *180/PI << std::endl;
        std::cout << "angPerro: " << ang *180/PI << std::endl <<std::endl<< std::endl;

        follow(event, relativeAng, distance);
        // std::cout << "vi a alguien" << std::endl;
        attackModeOn = true;
        } 
        if(!attackModeOn){
            // noEnemyAtSight(event);
        }

    return;
}

void AILua::changeToAttackMode(){
    attackModeOn = true;
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
        // if (!objIsVisible(posObjeto)){
        //     continue;
        // }
        // Vector auxPos(enemy.second.x, enemy.second.y);
        // std::cout << "AI.Lua. 91. enemyID:" << enemy.second.ID << std::endl;
        addVectDist(vectorAux, enemy.second, pos);
    }
    return vectorAux;
}

bool AILua::checkForEnemiesInSight(event_t &event, Vector &auxVector){
    // std::cout << "AI.Lua. 97, tamño de enemies: " << enemies.size() << std::endl;
    renderRaycaster();
    int one = 1;
    Vector posPlayer = Vector(position.x, position.y);
    std::vector<Player_t> orderedEnemies;
    orderedEnemies = orderEnemies(posPlayer);
    for (int obj = 0; obj < orderedEnemies.size(); ++obj){
        Vector enemyPos(orderedEnemies[obj].x, orderedEnemies[obj].y);
        
        if (!lua.isVisible(posPlayer, enemyPos, ang)){
            // if(distObj < 60){
            //     event = PLAYER_START_ROTATING_RIGHT;
            // }
            continue;
        }

            // std::cout << "position.x: " << x << std::endl;
            // std::cout << "position.y: " << x << std::endl;
        Vector pos(position.x, position.y);
        float distance = pos.getDistance(enemyPos); 
        float anguloObj = pos.getAngle(enemyPos);
        float difAng = ang - anguloObj;

        if (difAng < -PI){
            difAng += 2*PI;
        }
        if (difAng > PI){
            difAng -= 2*PI;
        }
        if(difAng<0)
            difAng=-difAng;
        //se forma un triangulo rectangulo con posicion del jugador,
        //direccion de tiro y posicion del enemigo
        float op=sin(difAng)*distance; //cateto opuesto
        float ad=cos(difAng)*distance; //cateto adyacente
 
        // std::cout << "distbuffer[0]: " << distBuffer[0] << std::endl;

            // std::cout << "anguloObj: " << anguloObj << std::endl;
        int x = (int)(30*PI/180 + anguloObj- ang ) / 0.1875;
            // std::cout << "x: " << x << std::endl;
        if(distance < distBuffer[x] && distance < distBuffer[x+1]){
            // std::cout << "distance: " << distance << std::endl;
            // std::cout << "distbuffer[x]: " << distBuffer[x] << std::endl;
            // std::cout << "distbuffer[x+1]: " << distBuffer[x+1] << std::endl;
            float auxFloat = enemyPos.getX();
            auxVector.setX(auxFloat);
            auxFloat = enemyPos.getY();
            auxVector.setY(auxFloat);
            return true;
        }
        
            std::cout << "___________________________________" << std::endl;

    }
        return false;
    // noEnemyAtSight(event);
}

void AILua::noEnemyAtSight(event_t &event){
    // std::cout << "no hay nadie en vista" << std::endl;
    if(!rotating){
        event = PLAYER_START_ROTATING_RIGHT;
        rotating = true;    
    }
    else if(!moving){
        event = PLAYER_START_MOVING_FORWARD;
        moving = true;
    }    
}

void AILua::follow(event_t &event, float &relativeAng, float &dist){
    std::cout << "relativeAng - angPerro:" <<  (180/PI)*(relativeAng - ang) << std::endl;
    // if(dist < 100){

    //         event = PLAYER_SHOOT;
    //         return;
        
    // }
    // else 
    if(relativeAng-ang >= 15*PI/180){
        if(moving){
            event = PLAYER_STOP_MOVING;
            moving = false;
        } else{

            event = PLAYER_START_ROTATING_RIGHT;
            rotating = true;
        }
    }
    // else 
    else if(relativeAng-ang <= -15*PI/180){
        if(moving){
            event = PLAYER_STOP_MOVING;
            moving = false;
        } else{
            event = PLAYER_START_ROTATING_LEFT;
            rotating = true;
        }
    }
    else if(relativeAng-ang < 15*PI/180 && relativeAng-ang > -15*PI/180){
        std::cout << "entro a centro " << std::endl;
        if(rotating){
            event = PLAYER_STOP_ROTATING;
            rotating = false;
        }
        else{
            event = PLAYER_START_MOVING_FORWARD;
            moving = true;
        }
    }
    return;
}


void AILua::renderRaycaster(){
    Vector vectorPos(position.x, position.y);
    // std::cout << "x: " << position.x << std::endl;
    // std::cout << "y: " << position.y << std::endl;
    ShootingRaycaster raycaster(vectorPos, ang, mapPlayer);
    // svRaycaster raycaster(vectorPos, ang, mapPlayer);
    float angleRay = ang - PI/6;

    // std::cout << "angleray: " << angleRay << std::endl;
    // std::cout << "ang: " << ang << std::endl;

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
    // std::cout << "distBuffer[0]" << distBuffer[0] << std::endl; 
    // std::cout << "distBuffer[1]" << distBuffer[1] << std::endl; 
    // std::cout << "distBuffer[5]" << distBuffer[5] << std::endl; 
    // std::cout << "distBuffer[100]" << distBuffer[100] << std::endl; 
}
bool AILua::objIsVisible(Vector &posEnemy){
    /*Visibilidad hacia izq y derecha en radiales
    serian 30 grados pero agrego 5 mas para que
    se vea mas el sprite del objeto */
    float gVis = 35.0/180.0;
    float visible = PI * gVis;

    float dx = posEnemy.getX() - position.x;
    float dy = posEnemy.getY() - position.y;

    float angleObj = atan2(dy, dx);
    float difAng = ang - angleObj;

    if (difAng < -PI){
        difAng += 2*PI;
    }
    if (difAng > PI){
        difAng -= 2*PI;
    }
    bool res = (difAng < visible);
    res &= (difAng > -visible);

    return res;
}

//Usa trigonometria para definir la proporcion de daño que le sacara al enemigo
//de acuerdo a la distancia (ad=adyacente) y angulo (op=opuesto)
void AILua::getDamageCoefficient(Player_t &enemy, float &coef, float wallDist){
    Vector enemyPos(enemy.x,enemy.y);
    Vector pos(position.x, position.y);
    float distance = pos.getDistance(enemyPos); 
    float anguloObj = pos.getAngle(enemyPos);
    float difAng = ang - anguloObj;

    if (difAng < -PI){
        difAng += 2*PI;
    }
    if (difAng > PI){
        difAng -= 2*PI;
    }
    if(difAng<0)
        difAng=-difAng;
    //se forma un triangulo rectangulo con posicion del jugador,
    //direccion de tiro y posicion del enemigo
    float op=sin(difAng)*distance; //cateto opuesto
    float ad=cos(difAng)*distance; //cateto adyacente
    if(ad>wallDist || op > SHOOTING_SIZE){
        coef=0;
        return;
    }
    float coefDistance = COEF_SHOOTING_DISTANCE_OFFSET+exp(-ad/COEF_SHOOTING_DISTANCE_DIVISOR);
    float coefAng= exp(-op/COEF_SHOOTING_ANGLE_DIVISOR);
    coef=coefDistance*coefAng;
    if(coef>1)
        coef=1;

}