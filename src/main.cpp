#include <concurrent-hashmap.hpp>
#include <db-server.hpp>
#include <memory>

int main(int argc, char* argv[]) {
  auto storage = std::shared_ptr<ConcurMap::MapStore>(new ConcurMap::ConcurrentHashmap);
  DbServer::Db dbserver(storage, 3000);
  dbserver.Listen();
}
