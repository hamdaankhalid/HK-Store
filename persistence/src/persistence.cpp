#include <memory>
#include <thread>
#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>

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

        outFile.write(key.c_str(), key.size());
        outFile.write(keyValSeparator.c_str(), keyValSeparator.size());
        outFile.write((char*)val.data(), val.size());
        outFile.write(recordSeparator.c_str(), recordSeparator.size());
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
  std::ifstream inFile(dataFile);
  if (inFile.fail()) {
    inFile.close();
    return;
  }
  
  unsigned char byte = 0;
  // TODO: PARSE AND SET
  while (inFile.get(byte)) {
    std::cout << byte << "-";
  }

  std::cout << "\n";

  inFile.close();
}
