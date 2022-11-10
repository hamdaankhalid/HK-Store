# A Byte Based DB for my apps
- An in-memory hashmap with asynchronous persistence on disk.
- Clients are expected to send data in format where keys are strings and values have been serialized to a string. 
- Db only stores a dumb mapping of key, serialized val.
- Upon retrieval it is the client library which must de-serialize and send val to application layer after recieving from server.

## Overview
- Tcp based communication layer request response for set, get, delete.
- Persistence on separate thread that does not block req-resp  loop.

## Operations
### Set
```
SET KEY_SIZE VAL_SIZE KEY... VAL....
```
1. communication layer reads  cmd key serializedVal
2. forwards request to a thread from thread pool to handle.
3. handler then updates in memory hashmap, and returns true on success.
4. write response into buffer.

### Get
```
Request: GET KEY_SIZE KEY...
Response: VAL_SIZE VAL....
```
1. communication layer reads (string key)
2. forwards request to a thread from thread pool to handle.
3. handler then finds by key and returns
4. write response into buffer.
  
### Delete
```
DEL KEY_SIZE KEY...
```
1. communication layer reads (string key)
2. forwards request to a thread from thread pool to handle.
3. handler then deletes key and returns
4. write response into buffer.

### Get All Keys
```
ALL
```
1. communication layer reads (string key)
2. forwards request to a thread from thread pool to handle.
3. handler then gets all keys from the map and writes back a buffer in the below format
```
DATAPACKETSIZE KEY_SIZE KEY KEY_SIZE KEY....KEY_SIZE KEY
```

## Libraries
- **db_server**: This is the main library that is used in src/main. It provides access to the main database that takes the storage layer as a dependency.
- **concurrent_hashmap**: Threadsafe hashmap and interface for the expected storage layer it satisfies for our db found in db_server.
- **persistence**: Used primarily by db_server, this library is responsible for serializing and deserializing our database state to disk.
- Logger: Threadsafe logging library, used by multiple internal libraries.

## Example Client:
- Based on the above operations a client can be written to facilitate communication between our Db and applications. A python client has been written in the **end-to-end-tests** dir.
