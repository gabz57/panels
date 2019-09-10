#ifndef PANELS_OBSERVER_H
#define PANELS_OBSERVER_H

#pragma once

#include <vector>

using namespace std;

class Observee;

class Observer {
public:
    virtual ~Observer() {}
    virtual void Notify(Observee *observee) = 0;

    Observer() {}

private:
//    // -------------------------
//    // Disabling default copy constructor and default
//    // assignment operator.
//    // -------------------------
//    Observer(const Observer &yRef);
//
//    Observer &operator=(const Observer &yRef);
};

#endif //PANELS_OBSERVER_H
