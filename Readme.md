# A DB for my apps
- An in-memory hashmap with asynchronous persistence on disk.
- Clients are expected to send data in format: 
  ```CMD KEY_SIZE VAL_SIZE KEY VALUE```
  VAL_SIZE and VALUE are only there for certain commands/

- Key should be a string, and value should be a serialized json
- The validation and responsibility to serialize the json's is of the client implementation.
- Db only stores a dumb mapping of key, serialized val.
- Upon retrieval it is the client library which must de-serialize and send val to application layer after recieving from server.

## Overview
- Tcp based communication layer request response for set, get, delete.
- Persistence on separate thread that does not block req-resp  loop.

## Operations
### Set
1. communication layer reads  cmd key serializedVal
2. forwards request to a thread from thread pool to handle.
3. handler then updates in memory hashmap, and returns true on success.
4. write response into buffer.

### Get
1. communication layer reads (string key)
2. forwards request to a thread from thread pool to handle.
3. handler then finds by key and returns
4. write response into buffer.
  
### Delete
1. communication layer reads (string key)
2. forwards request to a thread from thread pool to handle.
3. handler then deletes key and returns
4. write response into buffer.

## Libraries
- DB this is the main library that is used in src/main.
- Concurrent hashmap: Threadsafe hashmap
- Persistence: takes contents from a map and serializes to disk
- Logger: logging library
