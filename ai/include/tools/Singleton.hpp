//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_PLAZZA_SINGLETON_HPP_
#define CPP_PLAZZA_SINGLETON_HPP_

#include <iostream>

template <typename T>
class Singleton
{
    static T &instance;
    static bool instantiation = true;

    T& operator=(const T&) = delete;

public:
    static T &getInstance()
    {
        if (instantiation)
        {
            static T _instance;
            instance = _instance;
            instantiation = false;
        }
        return instance;
    }

    template <typename U>
    static T &getInstance(U param1)
    {
        if (instantiation)
        {
            static T _instance(param1);
            instance = _instance;
            instantiation = false;
        }
        return instance;
    }

    template <typename U, typename V>
    static T &getInstance(U param1, V param2)
    {
        if (instantiation)
        {
            static T _instance(param1, param2);
            instance = _instance;
            instantiation = false;
        }
        return instance;
    }
};


#endif // !CPP_PLAZZA_SINGLETON_HPP_
