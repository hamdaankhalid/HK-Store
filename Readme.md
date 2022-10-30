# A DB for my apps
- An in-memory hashmap with asynchronous persistence on disk.

## Overview
- Tcp based communication layer request response for set, get, delete.
- Persistence on separate thread that does not block req-resp  loop.

## Operations
### Set
1. communication layer reads (string key, char[] serialized val)
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
- Concurrent hashmap: DB runs a tcp server that uses this lib.
- Persistence: takes contents from a map and serializes to disk
- Logger: logging library

