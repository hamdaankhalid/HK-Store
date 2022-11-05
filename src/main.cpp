#include <concurrent-hashmap.hpp>
#include <db-server.hpp>
#include <persistence.hpp>

#include <memory>

int main(int argc, char* argv[]) {
  auto storage = std::shared_ptr<ConcurMap::MapStore>(new ConcurMap::ConcurrentHashmap);
  DiskPersist persist(storage, "../data/");
  DbServer::Db dbserver(storage, 3000);
  persist.Hydrate();
  persist.AsyncPersist();
  dbserver.Listen();
}
