// write an interface so later we could switch persistence/backups being created remotely as well
class Persist {
  public:
  ~Persist(){};
  void AsyncPersist() virtual = 0;
}

/**
 * Holds a reference to db or store underneath db
 * */
class DiskPersist : Persist {

}

