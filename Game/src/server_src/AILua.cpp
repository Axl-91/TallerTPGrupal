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
    if(!attackModeOn){
        switch(decision){
        case 1:
            // event = PLAYER_START_ROTATING_LEFT;
            decision++;
            break;
        case 0:
            event = PLAYER_START_MOVING_FORWARD;
            decision++;
            break;
        case 2:
            event = PLAYER_START_ROTATING_RIGHT;
            decision++;
            break;
        case 3:
            event = PLAYER_STOP_MOVING;
            decision++;
            break;
        default:
            decision=0;
        }
    }
    checkForEnemiesInSight(event);
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
        if (!objIsVisible(posObjeto)){
            continue;
        }
        // Vector auxPos(enemy.second.x, enemy.second.y);
        // std::cout << "AI.Lua. 91. enemyID:" << enemy.second.ID << std::endl;
        addVectDist(vectorAux, enemy.second, pos);
    }
    return vectorAux;
}

void AILua::checkForEnemiesInSight(event_t &event){
    // std::cout << "AI.Lua. 97, tamño de enemies: " << enemies.size() << std::endl;
    renderRaycaster();
    int one = 1;
    Vector posPlayer = Vector(position.x, position.y);
    std::vector<Player_t> orderedEnemies;
    // orderedEnemies=mapPlayer.orderEnemies(posPlayer);
    orderedEnemies = orderEnemies(posPlayer);
    // std::cout << "AI.Lua. 104" << std::endl;

    for (int obj = 0; obj < orderedEnemies.size(); ++obj){
        Vector posObjeto(orderedEnemies[obj].x, orderedEnemies[obj].y);
        if (!objIsVisible(posObjeto)){
            continue;
        }
        // int tipoObj = mapPlayer.getTipoObj(obj);
        float distObj = posPlayer.getDistance(posObjeto);

        //Coordenadas en Y
        //Coordenadas en X
        float dx = position.x - posObjeto.getX();
    // std::cout << "AI.Lua. 118 dx:" << dx << std::endl;
        float dy = position.y - posObjeto.getY();
    // std::cout << "AI.Lua. 120 dy:" << dy << std::endl;
        float angObj = atan2(dy, dx) - ang; // distancia relativa del obj desde centro de vision
    // std::cout << "angObj:" << angObj << std::endl;
        float distProyPlane = (LONG_SCREEN/2) / tan(PI/6);
        float xo = tan(angObj) * distProyPlane;
    // std::cout << "xo:" << xo << std::endl;

        float x = round((LONG_SCREEN/2) + xo);
        int longTiles = mapPlayer.getLongTiles();
        float sizeObj = (longTiles * LONG_SCREEN) / distObj;
        float longObj = sizeObj / longTiles;

        int count = 0;
        for (int i = 0; i < longTiles; ++i){
            for (int j = 0; j < longObj; ++j){
                int z = round(x)+((i)*longObj)+j;
                if (distBuffer[z] > distObj){
                    event = PLAYER_SHOOT;
                    // std::cout << "_______________________________AI.Lua. 137" << std::endl;
                    // std::cout << "Veo a " << orderedEnemies[obj].ID << count << std::endl;
                    changeToAttackMode();
                    follow(event, xo);
                    return;
                }
            }
        }
        attackModeOn = false;
    }
}

void AILua::follow(event_t &event, float &xo){
    if(xo <= -100){
        event = PLAYER_START_ROTATING_LEFT;
        rotating = true;
    }
    else if(xo > 100){
        event = PLAYER_START_ROTATING_RIGHT;
        rotating = true;
    }
    else {
        if(!rotating)
            event = PLAYER_STOP_MOVING;
        event = PLAYER_STOP_ROTATING;
    }
    return;
}

void AILua::renderRaycaster(){
    Vector vectorPos(position.x, position.y);
    svRaycaster raycaster(vectorPos, ang, mapPlayer);
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
bool AILua::objIsVisible(Vector &posObj){
    /*Visibilidad hacia izq y derecha en radiales
    serian 30 grados pero agrego 5 mas para que
    se vea mas el sprite del objeto */
    float gVis = 35.0/180.0;
    float visible = PI * gVis;

    float dx = posObj.getX() - position.x;
    float dy = posObj.getY() - position.y;

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