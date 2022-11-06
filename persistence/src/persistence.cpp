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
  std::ifstream inFile(dataFile, std::ios::binary);
  if (inFile.fail()) {
    inFile.close();
    return;
  }
  
  inFile.seekg(0, std::ios::end);
  size_t length = inFile.tellg();
  std::cout << length << std::endl;

  std::vector<unsigned char> buffer(length);
  inFile.read((char*)buffer.data(), length);
  // why is data not coming as anything meaningful
  for (auto c: buffer) {
    std::cout << c << ",";
  }
  std::cout << "\n";

  inFile.close();
}
