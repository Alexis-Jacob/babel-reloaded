
#ifndef	__DATABASE__
#define __DATABASE__

#include <fstream>
#include "User.hh"
#include "Observer.hh"

class	DataBase : public IObserver
{
private:
  friend class boost::serialization::access;
  std::list<User*>	_userList;
  std::string		_name;
  unsigned int		_userCount;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    (void)version;
    ar & _userList;
  }

  DataBase(std::string name) : _name(name)
  {
    load();
    _userCount = _userList.size();
  }

public:
  static DataBase *getDataBase();
  static DataBase *getDataBase(std::string name);
  ~DataBase(){}
  virtual void update();
  bool	addUser(std::string userName);
  void	load(); 
  void	removeUser(User &user);
  void	displayUser() const;
  void	save() const;
};

#endif
