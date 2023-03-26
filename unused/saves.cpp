
//EVOLUTION SAVES
int Evolution::saveGame(snakesList *thisSnakes)
{
    
    sqlite3_stmt *stmt;

    std::string request = "INSERT INTO straight_network_sessions ( "
                                "generation, best_score, turns_to_death, count_of_snakes, snake_length, count_of_food, "
                                "count_of_borders, first_layer_neuron_count, last_layer_neuron_count, output_layer_neuron_count, "
                                "count_of_best, count_of_worst, mutation_chance, game_sub_mode_id "
                            ") values ("
                                "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, (SELECT ID FROM game_sub_modes WHERE name='Straight Network') "
                            ")";

    int result = sqlite3_prepare_v2(database.ppDb, request.c_str(), -1, &stmt, NULL);
    if (result) {
        printf("Error executing sql statement\n");
        sqlite3_close(database.ppDb);
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, evolutionParameters.generation);
    sqlite3_bind_int(stmt, 2, evolutionParameters.theBestScore);
    sqlite3_bind_int(stmt, 3, evolutionParameters.turnsToDeath);
    sqlite3_bind_int(stmt, 4, evolutionParameters.countOfSnakes);
    sqlite3_bind_int(stmt, 5, evolutionParameters.snakeLength);
    sqlite3_bind_int(stmt, 6, evolutionParameters.countOfFood);
    sqlite3_bind_int(stmt, 7, evolutionParameters.countOfBorders);
    sqlite3_bind_int(stmt, 8, evolutionParameters.firstLayerNeuronCount);
    sqlite3_bind_int(stmt, 9, evolutionParameters.lastLayerNeuronCount);
    sqlite3_bind_int(stmt, 10, evolutionParameters.outputLayerNeuronCount);
    sqlite3_bind_int(stmt, 11, evolutionParameters.countOfBest);
    sqlite3_bind_int(stmt, 12, evolutionParameters.countOfWorst);
    sqlite3_bind_int(stmt, 13, evolutionParameters.mutationChance);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    sqlite3_exec(database.ppDb, "SELECT MAX(ID) FROM straight_network_sessions", saveSnakes, thisSnakes, &(database.errmsg));

    return 0;

}


int Evolution::saveSnakes(void *NotUsed, int argc, char **argv, char **azColName)
{
    snakesList *snakesListTmp = nullptr;
    snakesListTmp = (snakesList*)NotUsed;
    while(snakesListTmp->nextSnake){
        snakesListTmp->currentSnake->network.saveNetwork(argv[0]);
        snakesListTmp = snakesListTmp->nextSnake;
    }
    snakesListTmp = nullptr;
    return 0;
}


int Evolution::loadGame(snakesList *thisSnakes)
{
    std::string request = "SELECT * FROM straight_network_sessions WHERE generation=(SELECT MAX(generation) FROM straight_network_sessions)";

    int result = sqlite3_exec(database.ppDb, request.c_str(), loadSession, thisSnakes, &(database.errmsg));
    if (result) {
        printf("%s\n", sqlite3_errmsg(database.ppDb));
        printf("Error executing sql statement\n");
        sqlite3_close(database.ppDb);
        exit(1);
    }

    return 0;

}


int Evolution::loadSession(void *NotUsed, int argc, char **argv, char **azColName)
{
    std::string session_ID;

    for(int count=0; count<argc; count++){
        if (strcmp(azColName[count], "ID") == 0) {
            session_ID = argv[count];
        } else if (strcmp(azColName[count], "generation") == 0) {
            evolutionParameters.generation = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "best_score") == 0) {
            evolutionParameters.theBestScore = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "turns_to_death") == 0) {
            evolutionParameters.turnsToDeath = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "count_of_snakes") == 0) {
            evolutionParameters.countOfSnakes = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "snake_length") == 0) {
            evolutionParameters.snakeLength = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "count_of_food") == 0) {
            evolutionParameters.countOfFood = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "count_of_borders") == 0) {
            evolutionParameters.countOfBorders = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "first_layer_neuron_count") == 0) {
            evolutionParameters.firstLayerNeuronCount = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "last_layer_neuron_count") == 0) {
            evolutionParameters.lastLayerNeuronCount = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "output_layer_neuron_count") == 0) {
            evolutionParameters.outputLayerNeuronCount = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "count_of_best") == 0) {
            evolutionParameters.countOfBest = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "count_of_worst") == 0) {
            evolutionParameters.countOfWorst = std::stoi(argv[count]);
        } else if (strcmp(azColName[count], "mutation_chance") == 0) {
            evolutionParameters.mutationChance = std::stoi(argv[count]);
        }   
    }

    snakesList *snakesListTmp = nullptr;
    snakesListTmp = (snakesList*)NotUsed;
    while(snakesListTmp->nextSnake){
        std::string request = "SELECT * FROM straight_network_snakes WHERE straight_network_sessions_id=" + session_ID;

        int result = sqlite3_exec(database.ppDb, request.c_str(), loadSnake, &(snakesListTmp->currentSnake->network.layersList), &(database.errmsg));
        if (result) {
            printf("%s\n", sqlite3_errmsg(database.ppDb));
            printf("Error executing sql statement\n");
            sqlite3_close(database.ppDb);
            exit(1);
        }
        snakesListTmp = snakesListTmp->nextSnake;
    }
    snakesListTmp = nullptr;

    return 0;

}


int Evolution::loadSnake(void *NotUsed, int argc, char **argv, char **azColName)
{
    std::string snake_ID;
    int count_of_layers;

    for(int count=0; count<argc; count++){
        if (strcmp(azColName[count], "ID") == 0) {
            snake_ID = argv[count];
        } else if (strcmp(azColName[count], "count_of_layers") == 0) {
            count_of_layers = std::stoi(argv[count]);
        }
    }

    StraightNetwork::LayersList *layersListTmp = (StraightNetwork::LayersList*)NotUsed;

    for(int layer = 0; layer < count_of_layers; layer++){
        std::string request = "SELECT * FROM straight_network_layers WHERE straight_network_snakes_id=" + snake_ID  + " AND layer_number=" + std::to_string(layer+1);

        int result = sqlite3_exec(database.ppDb, request.c_str(), loadNeurons, layersListTmp, &(database.errmsg));
        if (result) {
            printf("%s\n", sqlite3_errmsg(database.ppDb));
            printf("Error executing sql statement\n");
            sqlite3_close(database.ppDb);
            exit(1);
        }
        if (layer != (count_of_layers - 1))
            layersListTmp = layersListTmp->nextLayer;
    }

    return 0;
}


int Evolution::loadNeurons(void *NotUsed, int argc, char **argv, char **azColName)
{
    std::string snake_ID;
    int paramCount = 20;
    StraightNetwork::LayersList *layersListTmp = (StraightNetwork::LayersList*)NotUsed;
    StraightNetwork::NeuronsList *tmpNeuron = layersListTmp->currentNeuronsList;


    for(int neuron = 0; neuron < (argc / paramCount); neuron += paramCount){
        

        if (neuron < (argc - paramCount))
            tmpNeuron = tmpNeuron->nextNeuron;
    }

    StraightNetwork::LayersList *layersListTmp = (StraightNetwork::LayersList*)NotUsed;



    for(int neuron = 0; neuron < (argc / 20); neuron += 8){
        std::string request = "SELECT * FROM straight_network_layers WHERE straight_network_snakes_id=" + snake_ID  + " AND layer_number=" + std::to_string(layer+1);

        int result = sqlite3_exec(database.ppDb, request.c_str(), loadNeurons, layersListTmp, &(database.errmsg));
        if (result) {
            printf("%s\n", sqlite3_errmsg(database.ppDb));
            printf("Error executing sql statement\n");
            sqlite3_close(database.ppDb);
            exit(1);
        }
        if (layer != (count_of_layers - 1))
            layersListTmp = layersListTmp->nextLayer;
    }

    return 0;
}













//STRAIGHT NETWORK SAVES
int StraightNetwork::saveNetwork(char *session_id)
{
    sqlite3_stmt *stmt;
    std::string id = session_id;

    std::string request = "INSERT INTO straight_network_snakes ( "   
                                "snake_number, count_of_layers, straight_network_sessions_id "
                            ") values ( "
                                "?, ?, ?"
                            ")";

    int result = sqlite3_prepare_v2(database.ppDb, request.c_str(), -1, &stmt, NULL);
    if (result) {
        printf("%s\n", sqlite3_errmsg(database.ppDb));
        printf("Error executing sql statement\n");
        sqlite3_close(database.ppDb);
        exit(1);
    }

    evolutionParameters.snakeIdCounter++;
    if (evolutionParameters.snakeIdCounter > 100) {
        evolutionParameters.snakeIdCounter = 1;
    }

    sqlite3_bind_int(stmt, 1, evolutionParameters.snakeIdCounter);
    sqlite3_bind_int(stmt, 2, 2);
    sqlite3_bind_int(stmt, 3, stoi(id));

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);


    //NeuronsList *tempLayer = nullptr;

    layersListTmp = layersList;
    evolutionParameters.layerIdCounter = 1;
    while(layersListTmp){
        sqlite3_exec(database.ppDb, "SELECT MAX(ID) FROM straight_network_snakes", saveLayer, layersListTmp->currentNeuronsList, &(database.errmsg));
        layersListTmp = layersListTmp->nextLayer; 
    }

    return 0;
}



int StraightNetwork::saveLayer(void *NotUsed, int argc, char **argv, char **azColName)
{
    sqlite3_stmt *stmt;
    std::string id = argv[0];
    int neurons_count;

    std::string request = "INSERT INTO straight_network_layers ( "   
                                "layer_number, count_of_neurons, straight_network_snakes_id "
                            ") values ( "
                                "?, ?, ?"
                            ")";

    int result = sqlite3_prepare_v2(database.ppDb, request.c_str(), -1, &stmt, NULL);
    if (result) {
        printf("%s\n", sqlite3_errmsg(database.ppDb));
        printf("Error executing sql statement\n");
        sqlite3_close(database.ppDb);
        exit(1);
    }


    if (evolutionParameters.layerIdCounter == 1) {
        neurons_count = evolutionParameters.firstLayerNeuronCount;
    } else {
        neurons_count = evolutionParameters.outputLayerNeuronCount;
    } 

    sqlite3_bind_int(stmt, 1, evolutionParameters.layerIdCounter);
    sqlite3_bind_int(stmt, 2, neurons_count);
    sqlite3_bind_int(stmt, 3, stoi(id));


    evolutionParameters.layerIdCounter++;
    if (evolutionParameters.layerIdCounter > 2) {
        evolutionParameters.layerIdCounter = 1;
    }

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    NeuronsList *tempLayer = (NeuronsList *)NotUsed;
    evolutionParameters.neuronIdCounter = 1;

    while(tempLayer){
        sqlite3_exec(database.ppDb, "SELECT MAX(ID) FROM straight_network_layers", saveNeuron, tempLayer->currentNeuron, &(database.errmsg));
        tempLayer = tempLayer->nextNeuron; 
    }

    return 0;
}



int StraightNetwork::saveNeuron(void *NotUsed, int argc, char **argv, char **azColName)
{
    sqlite3_stmt *stmt;
    std::string id = argv[0];
    StraightNeuron *currentNeuron = (StraightNeuron *)NotUsed;

    std::string request = "INSERT INTO straight_network_neurons ( "   
                                "neuron_number, count_of_connections, "
                                "food_reaction_up,  food_reaction_down,  food_reaction_left,  food_reaction_right, "
                                "wall_reaction_up,  wall_reaction_down,  wall_reaction_left,  wall_reaction_right, "
                                "free_reaction_up,  free_reaction_down,  free_reaction_left,  free_reaction_right, "
                                "snake_reaction_up, snake_reaction_down, snake_reaction_left, snake_reaction_right, "
                                "straight_network_layers_id "
                            ") values ( "
                                "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?"
                            ")";

    int result = sqlite3_prepare_v2(database.ppDb, request.c_str(), -1, &stmt, NULL);
    if (result) {
        printf("%s\n", sqlite3_errmsg(database.ppDb));
        printf("Error executing sql statement\n");
        sqlite3_close(database.ppDb);
        exit(1);
    }

    sqlite3_bind_int(stmt, 1, evolutionParameters.neuronIdCounter);
    sqlite3_bind_int(stmt, 2, 1);
    sqlite3_bind_int(stmt, 3, currentNeuron->foodReaction->up);
    sqlite3_bind_int(stmt, 4, currentNeuron->foodReaction->down);
    sqlite3_bind_int(stmt, 5, currentNeuron->foodReaction->left);
    sqlite3_bind_int(stmt, 6, currentNeuron->foodReaction->right);
    sqlite3_bind_int(stmt, 7, currentNeuron->wallReaction->up);
    sqlite3_bind_int(stmt, 8, currentNeuron->wallReaction->down);
    sqlite3_bind_int(stmt, 9, currentNeuron->wallReaction->left);
    sqlite3_bind_int(stmt, 10, currentNeuron->wallReaction->right);
    sqlite3_bind_int(stmt, 11, currentNeuron->freeReaction->up);
    sqlite3_bind_int(stmt, 12, currentNeuron->freeReaction->down);
    sqlite3_bind_int(stmt, 13, currentNeuron->freeReaction->left);
    sqlite3_bind_int(stmt, 14, currentNeuron->freeReaction->right);
    sqlite3_bind_int(stmt, 15, currentNeuron->snakeReaction->up);
    sqlite3_bind_int(stmt, 16, currentNeuron->snakeReaction->down);
    sqlite3_bind_int(stmt, 17, currentNeuron->snakeReaction->left);
    sqlite3_bind_int(stmt, 18, currentNeuron->snakeReaction->right);
    sqlite3_bind_int(stmt, 19, stoi(id));


    evolutionParameters.neuronIdCounter++;
    if (evolutionParameters.neuronIdCounter > evolutionParameters.firstLayerNeuronCount) {
        evolutionParameters.layerIdCounter = 1;
    }

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

   /* NeuronsList *tempLayer = (NeuronsList *)NotUsed;

    while(tempLayer){
        sqlite3_exec(database.ppDb, "SELECT MAX(ID) FROM straight_network_layers", saveNeuron, tempLayer->currentNeuron, &(database.errmsg));
        tempLayer = tempLayer->nextNeuron; 
    }

    return 0;
}