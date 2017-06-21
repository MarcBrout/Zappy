//
// Created by Pierre Bougon on 24/04/17.
//

#ifndef CPP_PLAZZA_SERIALIZABLE_HPP_
#define CPP_PLAZZA_SERIALIZABLE_HPP_

#include <string>

class ISerializable
{
public:
    virtual ~ISerializable(){}

    virtual std::string serialize() const = 0;
    virtual bool deserialize(std::string const &serialized) = 0;
};

#endif // !CPP_PLAZZA_SERIALIZABLE_HPP_
