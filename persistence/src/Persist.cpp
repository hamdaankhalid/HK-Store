#include<concurrent-hashmap.hpp>
#include<memory>
#include <thread>
#include <fstream>
#include <vector>


DiskPersist::DiskPersist(std::shared_ptr<ConcurMap::MapStore> _store, std::string _snapshotFileLocation):
 store(state),
 snapshotFileLocation(_snapshotFileLocation) {}


/**
 * Non-blocking method that runs a background thread that stores the current state of our map
 * into a file periodically.
 * */
void DiskPersist::AsyncPersist() {
  std::thread bgPersist([&]() -> {
    
    while (true) {
      // if 15 mins since last time do the below
      
      //HOW TO RELEASE RESOURCE
      std::ofstream outFile(snapshotFileLocation);

      std::unordered_map<std::string, std::vector<unsigned char> > state = store->GetState();
      for (auto const& item: state) {
        // store .first and .second into a file
        std::string key = item.first;
        std::vector<unsigned char> val = item.second;

        // how do we serialize string and our vector such that they are still associated with each other

      }

      outFile.close();
    }
  });
  bgPersist.detach();
}


/**
 * Upon bootup look for snapshotFile and hydrate map with last saved values. If the file does
 * not exist just run it. We do not need to add values to our map
 * */
void DiskPersist::Hydrate() {

}
