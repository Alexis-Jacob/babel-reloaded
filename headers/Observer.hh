#ifndef	__OBSERVER_HH__
#define __OBSERVER_HH__

#include <set>

class IObserver
{
public:
  virtual void update() = 0;
};


class Observable
{
private:
  std::set<IObserver*> _observersList;
 
public:
  void notify() const
  {
    for (const auto & observer : _observersList)
      observer->update();
  }
 
  void addObserver(IObserver* observer)
  {
    _observersList.insert(observer);
  }
 
  void removeObserver(IObserver* observer)
  {
    _observersList.erase(observer);
  }
};



#endif
