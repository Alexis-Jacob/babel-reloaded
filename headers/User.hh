#ifndef	__USER__
#define __USER__

#include <vector>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include "Observer.hh"
#include "Utils.hpp"

class	DataBase;

class User : public Observable
{
private:
  friend class boost::serialization::access;
  friend class Database;
  std::list<User* > _userList;
  bool		_ban;
  unsigned int	_id;
  std::string	_userName;
  std::string	_ip;
  std::string	_message;
  std::vector<char>	_password;
  //img

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    (void)version;
    ar & _userList;
    ar & _userName;
    ar & _message;
    ar & _ip;
    ar & _id;
    ar & _password;
  }
  

public:
  User(){}
  User(int id, std::string userName, std::string password): _ban(false), _id(id), _userName(userName)
  {
    _message = "";
    _ip = "0.0.0.0";
    _password = Utils::cryptPassword(Utils::stringToChar(password));
    for (auto c : _password)
      std::cout << c;
    std::cout << std::endl;
  }

  const std::string &getMessage() const;
  const std::string &getUserName() const;
  const std::string &getIp() const;
  unsigned int	    getId() const;
  bool	isBan() const;
  bool	checkPassword(std::string password) const;
  bool	addFriend(User &user);
  void	setUserName(std::string &&userName);
  void	setMessage(std::string &&message);
  void	setIp(std::string &&ip);
  bool	changePassword(std::string oldpassword, std::string newpassword);
  void	removeUser(User &user);

  friend std::ostream& operator<< (std::ostream &out, const User & user)
  {
    out << "id:" << user._id << " " << user._userName << " " << user._message << " " << user._ip << ":" << std::endl;
    if (user._userList.size() > 0)
      {
	for (const auto &u : user._userList)
	  std::cout << "\t-" << u->getUserName() << std::endl;
	std::cout << std::endl;
      }
    else
      std::cout << "And don't have any friend :(";
    return out;
  }

};

#endif
