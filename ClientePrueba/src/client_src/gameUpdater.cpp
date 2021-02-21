#include "gameUpdater.h"

GameUpdater::GameUpdater(Player &p, ProtectedQueue<Update_t> &aQueue, Map &m, std::mutex &mut):
    is_running(false),
    player(p),
    uQ(aQueue),
    mapGame(m),
    m(mut)
{
	// }

}

void GameUpdater::operator()(){
    this->start();
}
void GameUpdater::run(){
    is_running = true;
    try{
        while(is_running == true){            
			update();
        }
    } catch (const std::exception &e){
        std::cerr << "Excepcion en client.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
}
void GameUpdater::stop(){
    is_running = false;
}

void GameUpdater::update(){
	Update_t anUpdate;
	uQ.pop(anUpdate);

    std::unique_lock<std::mutex> lock(m);
	if(anUpdate.type == MISSILE_UPDATE){
    	updateMissile(anUpdate.missileUpdate);
    }

	if(anUpdate.type == PLAYER_UPDATE){
    	updatePlayer(anUpdate.playerUpdate);
    }
	if(anUpdate.type == MAP_CHANGE){
    	updatePlayer(anUpdate.playerUpdate);
		updateMap(anUpdate.mapChange);
    }
}

void GameUpdater::updateMissile(Missile_t &m){
    mapGame.updateMissile(m);
}


void GameUpdater::updatePlayer(Player_t &p){
	if(p.ID == player.getID()){
		player.updateInfo(p);
		return;
	}
	mapGame.updateEnemy(p);
}

void GameUpdater::updateMap(Map_change_t &aMapChange){
	mapGame.update(aMapChange);
}
