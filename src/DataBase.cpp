#include <fstream>
#include <exception>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "User.hh"
#include "DataBase.hh"

DataBase	*databasePtr = nullptr; //delete /todo smartPtr
// Singleton //

DataBase *DataBase::getDataBase()
{
  if (databasePtr == nullptr)
    throw std::runtime_error("database not initialised");
  return databasePtr;
}

DataBase *DataBase::getDataBase(std::string name)
{
  if (databasePtr == nullptr)
    databasePtr = new DataBase(name);
  return databasePtr;
}
  
DataBase::~DataBase()
{
}

void DataBase::update()
{
  //std::cout << "Changement chez un utilisateur" << std::endl;
  //sauver la bdd
}

void	DataBase::addUser(User &user)
{
  for (const auto &u : _userList)
    if (u->getUserName() == user.getUserName())
      break;
  _userList.push_back(&user);
  user.addObserver(this);
  update();
}

void	DataBase::save()
{
  std::ofstream os(_name);
  boost::archive::text_oarchive oa(os);
  
  oa << *this;
  os.close();
}

void	DataBase::load()
  {
    std::ifstream is(_name);
    boost::archive::text_iarchive ia(is);
    
    ia >> *this;
    is.close();
  }

void	DataBase::removeUser(User &user)
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

void DataBase::displayUser() const
{
  for (const auto & user : _userList)
    {
      std::cout << *user << std::endl;
    }
}


int main() {
  DataBase::getDataBase();
  // User	user(std::string("Alexis"));
  // User	user2(std::string("Tom"));

  
  // user.addUser(user2);

  // DataBase	db("filename");
  
  // db.addUser(user);
  // db.addUser(user2);
  
  // user.addUser(user2);

  // db.save();
  
  // DataBase     db2("filename");
  
  // db2.load();
  // db2.displayUser();
  
  return 0;
}
