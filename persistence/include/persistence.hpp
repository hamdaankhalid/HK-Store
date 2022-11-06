#pragma once

#include <concurrent-hashmap.hpp>

#include <string>
#include <chrono>

// write an interface so later we could switch persistence/backups being created remotely as well
class Persist {
  public:
  ~Persist(){};
  virtual void AsyncPersist() = 0;
  virtual void Hydrate() = 0;
};

/**
 * Holds a reference to db or store underneath db
 * */
class DiskPersist : public Persist {
  const std::string tempFileLocation = "temp";
  const std::string primaryFileLocation = "hk_db_state";
  const std::string keyValSeparator = "~";
  const std::string recordSeparator = "\n";

  std::shared_ptr<ConcurMap::MapStore> store;
  std::string snapshotFileLocation;
  std::chrono::seconds interval = std::chrono::seconds(10);

  public:
  DiskPersist(std::shared_ptr<ConcurMap::MapStore> _store, std::string _snapshotFileLocation);
  void AsyncPersist();
  void Hydrate();
};
