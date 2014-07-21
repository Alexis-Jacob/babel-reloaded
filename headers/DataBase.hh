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

  
public:
  DataBase(std::string && name) : _name(name)
  { 
  }
  
  DataBase(){}

  ~DataBase()
  {
  }

  virtual void update()
  {
    //std::cout << "Changement chez un utilisateur" << std::endl;
    //sauver la bdd
  }

  void	addUser(User &user)
  {
    for (const auto &u : _userList)
      if (u->getUserName() == user.getUserName())
	break;
    _userList.push_back(&user);
    user.addObserver(this);
    update();
  }

  void	save()
  {
    std::ofstream os(_name);
    boost::archive::text_oarchive oa(os);

    oa << *this;
    os.close();
  }

  void	load()
  {
    std::ifstream is(_name);
    boost::archive::text_iarchive ia(is);
    
    ia >> *this;
    is.close();
 }

  void	removeUser(User &user)
  {
    for (auto it = _userList.begin();it != _userList.end();++it)
      {
	if ((*it)->getUserName() == user.getUserName())
	  {
	    _userList.erase(it);
	    break;
	  }
      }
    save();
  }

  void displayUser() const
  {
    for (const auto & user : _userList)
      {
	std::cout << *user << std::endl;
      }
  }

};

#endif
