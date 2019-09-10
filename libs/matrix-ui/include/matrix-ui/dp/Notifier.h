#ifndef PANELS_NOTIFIER_H
#define PANELS_NOTIFIER_H

#include <matrix-ui/dp/Observer.h>

class Notifier {
public:
    Notifier(Observee *observee) : m_pObservee(observee) {}

    void operator()(Observer *observer) {
        observer->Notify(m_pObservee);
    }

private:
    Observee *m_pObservee;
};

#endif //PANELS_NOTIFIER_H
