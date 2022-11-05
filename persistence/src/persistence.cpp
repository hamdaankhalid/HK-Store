#include <memory>
#include <thread>
#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>

#include <concurrent-hashmap.hpp>
#include <persistence.hpp>


DiskPersist::DiskPersist(std::shared_ptr<ConcurMap::MapStore> _store, std::string _snapshotFileLocation): store(_store), snapshotFileLocation(_snapshotFileLocation) {}


/**
 * Non-blocking method that runs a background thread that stores the current state of our map
 * into a file periodically.
 * */
void DiskPersist::AsyncPersist() {
  std::thread bgPersist([&]() -> void {
    while (true) {
      std::this_thread::sleep_for(interval);
      std::unordered_map<std::string, std::vector<unsigned char> > state = store->GetState();

      std::string temporaryFile = snapshotFileLocation+tempFileLocation;


      std::ofstream outFile(temporaryFile, std::ios::out | std::ios::binary);
      for (auto const& item: state) {
        auto key = item.first;
        
        auto val = item.second;

        outFile << key << keyValSeparator;
        outFile.write((char*)val.data(), val.size());
        outFile << recordSeparator;
      }
      outFile.close();

      auto dataFile = snapshotFileLocation+primaryFileLocation;
      // rename our temp file to primary file
      const std::filesystem::path from = temporaryFile;
      const std::filesystem::path to = dataFile;
      std::filesystem::rename(from, to);
    }
  });

  bgPersist.detach();
}


/**
 * Upon bootup look for snapshotFile and hydrate map with last saved values. If the file does
 * not exist just run it. We do not need to add values to our map
 * */
void DiskPersist::Hydrate() {
  auto dataFile = snapshotFileLocation+primaryFileLocation;
  // if dataFile exists open it read it and hydrate our store
  std::ifstream inFile(dataFile, std::ios::out | std::ios::binary);
  std::string record; 
  while (getline(inFile, record)) {
    std::cout << record;
  }
  inFile.close();
}
