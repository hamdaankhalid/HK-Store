#pragma once

#include<concurrent-hashmap.hpp>


// write an interface so later we could switch persistence/backups being created remotely as well
class Persist {
  public:
  ~Persist(){};
  void AsyncPersist() virtual = 0;
  void Hydrate() virtual = 0;
}

/**
 * Holds a reference to db or store underneath db
 * */
class DiskPersist : public Persist {
  std::shared_ptr<ConcurMap::MapStore> store;
  std::string snapshotFileLocation;

  public:
  DiskPersist(std::shared_ptr<ConcurMap::MapStore> _store, std::string _snapshotFileLocation);
  void AsyncPersist();
  void Hydrate();
}
