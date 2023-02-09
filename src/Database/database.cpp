#include "database.h"

Database::Database()
{
  errmsg = 0;

  FILE *fp = fopen("saves.db", "r");

  int result = sqlite3_open(filename, &ppDb);
  if (result) {
      std::cout << "Database failed to open" << std::endl;
      sqlite3_close(ppDb);
      exit(1);
  }

  if(fp != NULL){
    fclose(fp);
  } else {
    createDatabase();
  }
}


Database::~Database()
{
  int result = sqlite3_close(ppDb);
  if (result) {
    std::cout << "Database failed to close" << std::endl;
    exit(1);
  }

  delete errmsg;
}


int Database::createDatabase()
{  
  createGameModesTable();
  createGameSubModesTable();
  createStandartNetworkSessionTable();

  return 0;
}


int Database::dropDatabase()
{
  int result;

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS straight_network_connections;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS straight_network_neurons;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS straight_network_layers;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS straight_network_snakes;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS straight_network_sessions;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS game_sub_modes;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  result = sqlite3_exec(ppDb, "DROP TABLE IF EXISTS game_modes;", nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to drop " << errmsg <<  std::endl;
  }

  return 0;
}


int Database::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}


int Database::createGameModesTable()
{
  int result;
  std::string request = "CREATE TABLE IF NOT EXISTS game_modes( "
                          "ID          INTEGER  NOT NULL Primary key AUTOINCREMENT, "
                          "name        CHAR(25) NOT NULL, "
                          "description TEXT     NOT NULL"
                        ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg <<  std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }

  sqlite3_stmt *stmt;
  
  result = sqlite3_prepare_v2(ppDb, "INSERT INTO game_modes (name, description) values(?, ?)", -1, &stmt, NULL);
  if (result) {
      printf("Error executing sql statement\n");
      sqlite3_close(ppDb);
      exit(1);
  }

  sqlite3_bind_text(stmt, 1, "Snake", -1, NULL);
  sqlite3_bind_text(stmt, 2, "Casual single player snake game", -1, NULL);

  sqlite3_step(stmt);

  sqlite3_reset(stmt);

  sqlite3_bind_text(stmt, 1, "Evolution", -1, NULL);
  sqlite3_bind_text(stmt, 2, "Training a neural network with an evolutionary algorithm", -1, NULL);

  sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  return 0;
}


int Database::createGameSubModesTable()
{
  int result;

  std::string request = "CREATE TABLE IF NOT EXISTS game_sub_modes( "
                          "ID           INTEGER  NOT NULL Primary key AUTOINCREMENT, "
                          "name         CHAR(25) NOT NULL, "
                          "description  TEXT     NOT NULL, "
                          "game_mode_id INTEGER  NOT NULL, "
                          "FOREIGN KEY (game_mode_id) REFERENCES game_mode(ID) "
                        ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg << std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }

  sqlite3_stmt *stmt;

  
  result = sqlite3_prepare_v2(ppDb, "INSERT INTO game_sub_modes (name, description, game_mode_id) values(?, ?, (SELECT ID FROM game_modes WHERE name=?))", -1, &stmt, NULL);
  if (result) {
      printf("Error executing sql statement\n");
      sqlite3_close(ppDb);
      exit(1);
  }

  sqlite3_bind_text(stmt, 1, "Standart Network", -1, NULL);
  sqlite3_bind_text(stmt, 2, "Custom neural network. Actually, doesn't working. For now.", -1, NULL);
  sqlite3_bind_text(stmt, 3, "Evolution", -1, NULL);

  sqlite3_step(stmt);

  sqlite3_reset(stmt);

  sqlite3_bind_text(stmt, 1, "Straight Network", -1, NULL);
  sqlite3_bind_text(stmt, 2, "Network without hidden layers, all activated neurons making their influens on the output.", -1, NULL);
  sqlite3_bind_text(stmt, 3, "Evolution", -1, NULL);

  sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  return 0;
}

int Database::createStandartNetworkSessionTable()
{
  int result;

  std::string request = "CREATE TABLE IF NOT EXISTS straight_network_sessions( "
                          "ID                         INTEGER   NOT NULL Primary key AUTOINCREMENT, "
                          "generation                 BIGINT    NOT NULL, "
                          "best_score                 BIGINT    NOT NULL, "
                          "turns_to_death             BIGINT    NOT NULL, "
                          "count_of_snakes            BIGINT    NOT NULL, "
                          "snake_length               BIGINT    NOT NULL, "
                          "count_of_food              BIGINT    NOT NULL, "
                          "count_of_borders           BIGINT    NOT NULL, "
                          "first_layer_neuron_count   BIGINT    NOT NULL, "
                          "last_layer_neuron_count    BIGINT    NOT NULL, "
                          "output_layer_neuron_count  BIGINT    NOT NULL, "
                          "count_of_best              BIGINT    NOT NULL, "
                          "count_of_worst             BIGINT    NOT NULL, "
                          "mutation_chance            BIGINT    NOT NULL, "
                          "created_at                 TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                          "game_sub_mode_id           INTEGER   NOT NULL, "
                          "FOREIGN KEY (game_sub_mode_id) REFERENCES game_sub_mode(ID) "
                        ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg << std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }

  request.erase();

  request = "CREATE TABLE IF NOT EXISTS straight_network_snakes( "
              "ID                          INTEGER   NOT NULL Primary key AUTOINCREMENT, "
              "snake_number                BIGINT    NOT NULL, "
              "count_of_layers             BIGINT    NOT NULL, "
              "straight_network_sessions_id INTEGER   NOT NULL, "
              "FOREIGN KEY (straight_network_sessions_id) REFERENCES straight_network_sessions(ID) "
            ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg << std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }


  request.erase();

  request = "CREATE TABLE IF NOT EXISTS straight_network_layers( "
              "ID                          INTEGER   NOT NULL Primary key AUTOINCREMENT, "
              "layer_number                BIGINT    NOT NULL, "
              "count_of_neurons            BIGINT    NOT NULL, "
              "straight_network_snakes_id INTEGER   NOT NULL, "
              "FOREIGN KEY (straight_network_snakes_id) REFERENCES straight_network_snakes(ID) "
            ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg << std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }

  request.erase();

  request = "CREATE TABLE IF NOT EXISTS straight_network_neurons( "
              "ID                          INTEGER   NOT NULL Primary key AUTOINCREMENT, "
              "neuron_number               BIGINT    NOT NULL, "
              "count_of_connections        BIGINT    NOT NULL, "
              "food_reaction_up            INTEGER   NOT NULL, "
              "food_reaction_down          INTEGER   NOT NULL, "
              "food_reaction_left          INTEGER   NOT NULL, "
              "food_reaction_right         INTEGER   NOT NULL, "
              "wall_reaction_up            INTEGER   NOT NULL, "
              "wall_reaction_down          INTEGER   NOT NULL, "
              "wall_reaction_left          INTEGER   NOT NULL, "
              "wall_reaction_right         INTEGER   NOT NULL, "
              "free_reaction_up            INTEGER   NOT NULL, "
              "free_reaction_down          INTEGER   NOT NULL, "
              "free_reaction_left          INTEGER   NOT NULL, "
              "free_reaction_right         INTEGER   NOT NULL, "
              "snake_reaction_up           INTEGER   NOT NULL, "
              "snake_reaction_down         INTEGER   NOT NULL, "
              "snake_reaction_left         INTEGER   NOT NULL, "
              "snake_reaction_right        INTEGER   NOT NULL, "
              "straight_network_layers_id  INTEGER   NOT NULL, "
              "FOREIGN KEY (straight_network_layers_id) REFERENCES straight_network_layers(ID) "
            ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg << std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }

  request.erase();

  request = "CREATE TABLE IF NOT EXISTS straight_network_connections( "
              "ID           INTEGER  NOT NULL Primary key AUTOINCREMENT, "
              "from_neuron  INTEGER  NOT NULL, "
              "to_neuron    INTEGER  NOT NULL, "
              "FOREIGN KEY (from_neuron) REFERENCES straight_network_neurons(ID), "
              "FOREIGN KEY (to_neuron)   REFERENCES straight_network_neurons(ID) "
            ");";

  result = sqlite3_exec(ppDb, request.c_str(), nullptr, 0, &errmsg);
  if (result) {
    std::cout << "Failed to create " << errmsg << std::endl;
    sqlite3_close(ppDb);
    exit(1);
  }

  return 0;
}


int Database::show()
{
  printf("\n\n\n\n @@@@@\ngame_modes\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM game_modes", callback, 0, &errmsg);

  printf("\n\n\n\n@@@@@\n game_sub_modes\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM game_sub_modes", callback, 0, &errmsg);

  printf("\n\n\n\n@@@@@\n straight_network_sessions\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM straight_network_sessions", callback, 0, &errmsg);

  printf("\n\n\n\n@@@@@\n straight_network_snakes\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM straight_network_snakes", callback, 0, &errmsg);

  printf("\n\n\n\n@@@@@\n straight_network_layers\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM straight_network_layers", callback, 0, &errmsg);

  printf("\n\n\n\n@@@@@\n straight_network_neurons\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM straight_network_neurons", callback, 0, &errmsg);

  printf("\n\n\n\n@@@@@\n straight_network_connections\n@@@@@\n\n");
  sqlite3_exec(ppDb, "SELECT * FROM straight_network_connections", callback, 0, &errmsg);

  return 0;
}