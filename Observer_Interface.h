//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_OBSERVER_INTERFACE_H
#define FINAL_PROJECT_OBSERVER_INTERFACE_H
#include <iostream>
#include <vector>

class I_Observer
{
public:

    virtual void ObserverUpdate(std::string str) = 0;
};

class I_Subject
{
public:
    virtual void Attach(I_Observer*) = 0;
    virtual void Detach(I_Observer*) = 0;
    virtual void Notify(std::string str) = 0;
};


class Gen_Subject : public I_Subject
{
public:
    void Attach(I_Observer* obs) { observers.push_back(obs); };
    void Detach(I_Observer* obs)
    {
        for (size_t i = 0; i < observers.size();)
        {
            if (obs == observers[i])
            {
                delete observers[i];
                observers.erase(observers.begin() + i);
                return;
            }
            else { i++; };
        }
    };
    void Notify(std::string str) { for (auto itr : observers) { itr->ObserverUpdate(str); } };
private:
    std::vector<I_Observer*> observers;
};

#endif //FINAL_PROJECT_OBSERVER_INTERFACE_H
