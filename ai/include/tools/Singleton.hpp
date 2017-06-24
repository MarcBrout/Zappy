//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_ZAPPY_SINGLETON_HPP_
#define CPP_ZAPPY_SINGLETON_HPP_

#include <iostream>
#include <vector>

template <typename T>
class Singleton
{
    T& operator=(const T&) = delete;

public:
    static T &getInstance()
    {
        static T instance;
        return instance;
    }
};

#endif // !CPP_ZAPPY_SINGLETON_HPP_
