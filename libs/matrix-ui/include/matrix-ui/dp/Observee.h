#ifndef PANELS_OBSERVEE_H
#define PANELS_OBSERVEE_H

#include "vector"

using namespace std;

class Observer;

class Observee {
public:

    virtual ~Observee() {};

    bool AddObserver(Observer *observer);

    bool RemoveObserver(Observer *observer);

    bool NotifyObservers();

protected:
    //constructor is protected because this class is abstract, it's only meant to be inherited!
    Observee() {};

private:
    vector<Observer *> m_ObserverVec;

    // -------------------------
    // Disabling default copy constructor and default assignment operator.
    // -------------------------
    Observee(const Observee &yRef);

    Observee &operator=(const Observee &yRef);
};

#endif //PANELS_OBSERVEE_H
