#include<string>
#include<vector>

/**
 * Register a file to poll that re-reads logs into a vector every few seconds
 * */
class FilePoller {
  public:
  FilePoller(std::string filename): file(filename){};
  void BeginPolling();
  std::vector<std::string> GetLog();
  private:
  std::string file;
  std::vector<std::string> logs;
};
