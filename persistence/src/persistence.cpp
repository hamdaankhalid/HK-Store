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
      std::unordered_map<std::string, std::vector<unsigned char> > state = store->GetState();
      std::string temporaryFile = snapshotFileLocation+tempFileLocation;
      std::ofstream outFile(temporaryFile, std::ios::out | std::ios::binary);
  
      for (auto const& item: state) {
        auto key = item.first;
        auto val = item.second;

        outFile.write(key.c_str(), key.size());
        outFile.write(&keyValSeparator, sizeof(char));
        outFile.write((char*)val.data(), val.size());
        outFile.write(recordSeparator.c_str(), recordSeparator.size());
      }
      outFile.close();

      auto dataFile = snapshotFileLocation+primaryFileLocation;
      // rename our temp file to primary file
      const std::filesystem::path from = temporaryFile;
      const std::filesystem::path to = dataFile;
      std::filesystem::rename(from, to);

      std::this_thread::sleep_for(interval);
    }
  });

  bgPersist.detach();
}


/**
 * Blocking methof which should look for snapshotFile and hydrate db state with last saved values. 
 * If the file does no values are added.
 * */
void DiskPersist::Hydrate() {
  auto dataFile = snapshotFileLocation+primaryFileLocation;
  std::ifstream inFile(dataFile);
  if (inFile.fail()) {
    inFile.close();
    return;
  }
  
  char byte;
  bool keyStringReadingCompleted = false;
  std::stringstream keystream;
  std::vector<unsigned char> val;

  while (inFile.get(byte)) {
    if (byte == '\n') {
      std::string key = keystream.str();
      store->Set(key, val);

      keystream.str( std::string() );
      keystream.clear();
      val.clear();
      keyStringReadingCompleted = false;
    }

    if (byte == keyValSeparator) {
      keyStringReadingCompleted = true;
      // skip over the useless byte
      continue;
    }

    if (!keyStringReadingCompleted && byte != '\n') {
      keystream << byte;
    } else if (keyStringReadingCompleted && byte != '\n') {
      val.push_back(byte);
    }
  }
  inFile.close();
}
