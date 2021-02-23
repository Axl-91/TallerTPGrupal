#include "match.h"
#include <algorithm>
#include <chrono>

Match::Match(std::string &matchName,
                    int &numberOfPlayers, int &numberOfBots,
                    std::vector<std::vector<int>>& lvls):
    is_running(true),
    name(matchName),
    lvl1(lvls),
    connectionNumber(1),
    game(players, lvl1, uQ, missileUQ),
    playersOnMap(0),
    matchEventReader(players, q)
{
    initializeInitPosition(lvl1);

    for(int i = 0; i < numberOfBots ; i++){
        initPos auxPos;
        
        auxPos = initPositions.at(connectionNumber % playersOnMap);

        ServerPlayer auxPlayer(auxPos.x, auxPos.y, 0, connectionNumber);
        players.emplace(connectionNumber, std::move(auxPlayer));

        Bot* bot = new Bot(q, auxPos.x, auxPos.y, 0, 0, lvl1);
        bot->setID(connectionNumber);
        bots[connectionNumber] = bot;
        connectionNumber++;
    }

    matchEventReader();
}

void Match::initializeInitPosition(std::vector<std::vector<int>> &map){
    int	rows=map.size();
	int cols=map[0].size();

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>INITIAL_PLAYER_POS_OFFSET && map[i][j]<MAX_PLAYERS){
                initPos pos={j*64+32, i*64+32};
                initPositions.emplace(map[i][j], pos);
                playersOnMap++;
            }
        }
    }
}

Match::~Match(){
    q.close();
    for (auto user:users){
        if(user.second->hasStarted()){
            user.second->stop();
            user.second->join();    
        }
        delete(user.second);
    }
    for (auto bot:bots){
        delete(bot.second);
    }
    if(!matchEventReader.isDead()){
        matchEventReader.stop();
    }
    matchEventReader.join();
}

void Match::operator()(){
    this->start();
}

void Match::run(){
    long timeStep = 1000/60;
    try{
        while(is_running){
            auto initial = std::chrono::high_resolution_clock::now();
            for(auto &bot:bots)
                bot.second->makeDecision();
            game.update();
            updateUsers();
            
            auto final = std::chrono::high_resolution_clock::now();
            auto loopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
            long sleepTime = timeStep - loopDuration.count();
            if (sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en Match.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void Match::updateUsers(){
    while (uQ.empty()==false){
        for(auto user:users)
            user.second->update(uQ.front());
        for(auto bot:bots)
            bot.second->update(uQ.front());
        uQ.pop();
    }
    while (missileUQ.empty()==false){
        for(auto user:users)
            user.second->updateMissile(missileUQ.front());
        missileUQ.pop();
    }
}

void Match::stop(){
    q.close();
    matchEventReader.stop();
    is_running = false;
}

// Le manda al usuario su información inicial
void Match::welcomeUser(User* user){
    update_tag_t aTag = TAG_PLAYER_INFO;
    user->sendGameUpdate(aTag);

    Player_t auxPlayer;
    players.at(connectionNumber).getPlayerInfo(auxPlayer);
    user->sendPlayerInfo(auxPlayer);

    aTag = TAG_MAP_INIT;    
    user->sendGameUpdate(aTag);
    user->sendMap(lvl1);
}

// Carga al usuario y sus atributos iniciales al contenedor
void Match::addUser(User* user){
    initPos auxPos;
    auxPos = initPositions.at(connectionNumber% playersOnMap);

    ServerPlayer auxPlayer(auxPos.x, auxPos.y, 0, connectionNumber);
    players.emplace(connectionNumber, std::move(auxPlayer));
    user->setProtectedMatchEventQueue(&q);
    user->setID(connectionNumber);
    users[connectionNumber] = user;

    user->start();

    welcomeUser(user);
    connectionNumber++;

}

std::string Match::getName(){
    return name;
}

bool Match::started(){
    return gameStarted;
}

bool Match::isUserNameAvailable(std::string aName){
    for(auto user:users){
        if(user.second->getName() == aName)
            return false;
    }
    return true;
}
