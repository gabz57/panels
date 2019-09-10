#include "matrix-ui/dp/Observee.h"
#include "matrix-ui/dp/Notifier.h"
#include <algorithm>


//this method adds an observer to the vector of observers
bool Observee::AddObserver(Observer *observer) {
    auto temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
    //Return false if the observer is already in the vector. This is not expected. But there is nothing really wrong either
    if (temp != m_ObserverVec.end()) {
        return false;
    }
    m_ObserverVec.push_back(observer);
    return true;
}

//This method removes an observer from the vector
bool Observee::RemoveObserver(Observer *observer) {
    auto temp = find(m_ObserverVec.begin(), m_ObserverVec.end(), observer);
    //Return false if the observer could not be found (and evidently can�t be removed.
    if (temp == m_ObserverVec.end()) {
        return false;
    } else {
        m_ObserverVec.erase(remove(m_ObserverVec.begin(), m_ObserverVec.end(), observer));
    }
    return true;


}

//This Method is very important, it triggers all Notify() methods of all observers.
//The specific code in each class that inherits from observer will be executed
bool Observee::NotifyObservers() {
//    for (auto itr = m_ObserverVec.begin(); itr != m_ObserverVec.end(); ++itr) {
//        Observer *observer = *itr;
//        observer->Notify(this);
//    }
    for_each(m_ObserverVec.begin(), m_ObserverVec.end(), Notifier(this));
    return true;
}
