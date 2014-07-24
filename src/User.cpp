#include "User.hh"

const std::string &User::getMessage() const	{ return _message;}
const std::string &User::getUserName() const	{ return _userName;}
const std::string &User::getIp() const		{ return _ip;}
int   User::getId() const { return _id;}
bool  User::isBan() const { return _ban;}

void	User::addUser(User &user)
{
  for (const auto &u : _userList)
    if (u->getUserName() == user.getUserName())
      break;
  _userList.push_back(&user);
  this->notify();
}

void	User::setUsername(std::string &&userName) 
{
  _userName = userName;
  this->notify();
  }

void	User::setMessage(std::string &&message) 
{
  _message = message;
  this->notify();
}

void	User::setIp(std::string &&ip)
{
  _ip = ip;
  this->notify();
}

void	User::removeUser(User &user)
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
