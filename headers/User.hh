#ifndef	__USER__
#define __USER__

#include <vector>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include "Observer.hh"

class User : public Observable
{
private:
  friend class boost::serialization::access;
  std::list<User* > _userList;  
  std::string	_ip;
  std::string	_userName;
  std::string	_message;
  //img

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    (void)version;
    ar & _userList;
    ar & _userName;
    ar & _message;
    ar & _ip;
  }
  
public:
  User(std::string &&userName): _userName(userName)
  {
    _message = "";
    _ip = "0.0.0.0";
  }
  
  const std::string &getMessage() { return _message;}
  const std::string &getUserName(){ return _userName;}
  const std::string &getIp(){ return _ip;}

  void	addUser(User &user)
  {
    for (const auto &u : _userList)
      if (u->getUserName() == user.getUserName())
	break;
    _userList.push_back(&user);
    this->notify();
  }

  void	setUsername(std::string &&userName) 
  {
    _userName = userName;
    this->notify();
  }
  
  void	setMessage(std::string &&message) 
  {
    _message = message;
    this->notify();
  }
  
  void	setIp(std::string &&ip)
  {
    _ip = ip;
    this->notify();
  }
  
  void	removeUser(User &user)
  {
    for (auto it = _userList.begin();it != _userList.end();++it)
      {
	if ((*it)->getUserName() == user.getUserName())
	  {
	    _userList.erase(it);
	    this->notify();
	    break;
	  }
      }
  }

  User(){}

  friend std::ostream& operator<< (std::ostream &out, const User & user)
  {
    out << user._userName << " " << user._message << " " << user._ip << ":" << std::endl;
    if (user._userList.size() > 0)
      {
	for (const auto &u : user._userList)
	  std::cout << u->getUserName() << " ";
	std::cout << std::endl;
      }
    else
      std::cout << "And don't have any friend :(";
    return out;
  }

};
  









#endif
