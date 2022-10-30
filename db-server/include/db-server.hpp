#pragma once

namespace DbServer {
  class Db {
    int Start();
    void Listen();
    void Stop();
  }
};
