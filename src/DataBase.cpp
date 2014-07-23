#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "User.hh"
#include "DataBase.hh"

int main() {
  User	user(std::string("Alexis"));
  User	user2(std::string("Tom"));

  
  user.addUser(user2);

  DataBase	db("filename");
  
  db.addUser(user);
  db.addUser(user2);
  
  user.addUser(user2);

  db.save();
  
  DataBase     db2("filename");
  
  db2.load();
  db2.displayUser();
  
  return 0;
}
