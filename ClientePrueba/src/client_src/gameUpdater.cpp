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
	updatePlayer(anUpdate.playerUpdate);
	if(anUpdate.mapChangeAvailable == true)
		updateMap(anUpdate.mapChange);
}

void GameUpdater::updatePlayer(Player_t &p){
	// std::cout << "este es el ID de este jugador: " << anUpdate.playerUpdate.ID << std::endl;

	if(p.ID == player.getID()){
		player.updateInfo(p);
		return;
	}
	mapGame.updateEnemy(p);
}

void GameUpdater::updateMap(Map_change_t &aMapChange){
	mapGame.update(aMapChange);
}
