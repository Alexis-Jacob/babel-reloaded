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

void DataBase::update()
{
#ifdef _DEBUG
  std::cout << "Changement chez un utilisateur" << std::endl;
#endif
}

bool	DataBase::addUser(std::string userName, std::string password)
{
  for (const auto &u : _userList)
    if (u->getUserName() == userName)
      return false;
  User *user = new User(_maxId++, userName, password);
  _userList.push_back(user);
  user->addObserver(this);
  update();
  return true;
}

void	DataBase::save() const 
{
  std::ofstream os(_name);
  boost::archive::text_oarchive oa(os);
  
  oa << *this;
  os.close();
}

void	DataBase::load()
  {
    std::ifstream is(_name);
    try
      {
	boost::archive::text_iarchive ia(is);
        ia >> *this;
      }
    catch (boost::archive::archive_exception){}
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

void	DataBase::removeUser(unsigned int id)
{
  for (auto it = _userList.begin();it != _userList.end();++it)
    {
      if ((*it)->getId() == id)
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

User *DataBase::getUser(unsigned int id)
{
  for (auto user : _userList)
    if (user->getId() == id)
      return user;
  return nullptr;
}

bool testDb() {

  std::cout << "######" << std::endl << "Debut test DB" << std::endl;

  DataBase *db = DataBase::getDataBase("filename"); //init singleton
  if (db == nullptr)
    {
      std::cerr << "Error nullptr singleton" << std::endl;
      return false;
    }
  db->addUser("Alexis", "alexis06") && db->addUser("user1", "password");

  User *user1 = db->getUser(1);
  User *user0 = db->getUser(0);
  
  if (user1 == nullptr || user0 == nullptr)
    {
      std::cerr << "Error getUser" << std::endl;
      return false;
    }

  user1->setIp("127.0.0.1");
  if (user1->getIp() != "127.0.0.1")
    {
      std::cerr << "Error get/set ip" << std::endl;
      return false;
    }

  user1->setMessage("message test");
  if (user1->getMessage() != "message test")
    {
      std::cerr << "Error get/set message" << std::endl;
      return false;
    }


  user1->setUserName("UserName test");
  if (user1->getUserName() != "UserName test")
    {
      std::cerr << "Error get/set UserName" << std::endl;
      return false;
    }

  user0->addFriend(*user1);

  std::cout << user0->checkPassword("alexis06") << std::endl;
  std::cout << user0->checkPassword("password") << std::endl;
  std::cout << user0->getUserName() << std::endl;

  db->save();
  db->displayUser();
  
  std::cout << "DB ok!" << std::endl << "######" << std::endl;
  return 0;
}

int	main()
{
  testDb();
}
