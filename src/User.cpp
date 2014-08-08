#include "User.hh"

const std::string &User::getMessage() const	{ return _message;}
const std::string &User::getUserName() const	{ return _userName;}
const std::string &User::getIp() const		{ return _ip;}
unsigned int	  User::getId() const		{ return _id;}
bool  User::isBan() const { return _ban;}

bool	User::checkPassword(std::string password) const
{
  return (Utils::stringToPassword(password) == _password);
}

bool	User::addFriend(User &user)
{
  if (user.getId() == _id)
    return false;
  for (const auto &u : _userList)
    if (u->getId() == user.getId())
      return false;
  _userList.push_back(&user);
  this->notify();
  return true;
}

void	User::setUserName(std::string &&userName) 
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

bool	User::changePassword(std::string oldpassword, std::string newpassword)
{
  if (Utils::stringToPassword(oldpassword) == _password)
    {
      _password = Utils::stringToPassword(newpassword);
      return true;
    }
  return false;
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
