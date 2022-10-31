#include <db-server.hpp>

int main(int argc, char* argv[]) {
  DbServer::Db db(3000);
  db.Listen();
}
