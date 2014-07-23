
#ifndef	__DATABASE__
#define __DATABASE__

#include <fstream>
#include "User.hh"
#include "Observer.hh"

class	DataBase : public IObserver
{
private:
  friend class boost::serialization::access;
  std::list<User* >	_userList;
  std::string		_name;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    (void)version;
    ar & _userList;
  }

  DataBase(std::string name) : _name(name){}
  DataBase(){}

public:
  static DataBase *getDataBase();
  static DataBase *getDataBase(std::string name);
  ~DataBase();
  virtual void update();
  void	addUser(User &user);
  void	save(); //const ? 
  void	load(); 
  void	removeUser(User &user);
  void displayUser() const;
};

#endif
