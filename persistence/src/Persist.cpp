#include<concurrent-hashmap.hpp>
#include<memory>
#include <thread>
#include <fstream>
#include <vector>


DiskPersist::DiskPersist(std::shared_ptr<ConcurMap::MapStore> state, std::string _snapshotFileLocation):
 store(state),
 snapshotFileLocation(_snapshotFileLocation) {}


/**
 * Runs a background thread that stores the current state of our map into a file periodically
 * */
void DiskPersist::AsyncPersist() {
  std::thread bgPersist([&]() -> {
    
    //HOW TO RELEASE RESOURCE
    std::ofstream outFile(snapshotFileLocation);

    std::unordered_map<std::string, std::vector<unsigned char> > state = store->GetState();
    for (auto const& item: state) {
      // store .first and .second into a file
      std::string key = item.first;
      std::vector<unsigned char> val = item.second;
    }
  });
}


/**
 * Upon bootup look for snapshotFile and hydrate map with last saved values
 * */
void DiskPersist::Hydrate() {}
