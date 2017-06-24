//
// Created by Pierre Bougon on 23/06/17.
//

#include "tools/FDManager.hpp"

zappy::FDManager::FDManager()
{
    reset_fds();
}

void zappy::FDManager::reset_fds()
{
    FD_ZERO(&_rfds);
    FD_ZERO(&_wfds);
}

zappy::FDManager::~FDManager()
{

}

void zappy::FDManager::manageFD(int fd)
{
    reset_fds();
    if (fd > -1)
    {
        FD_SET(fd, &_wfds);
        FD_SET(fd, &_rfds);
    }
}

int zappy::FDManager::select(int fd)
{
    if (fd == -1)
        return (0);
    return (::select(fd + 1, &_rfds, &_wfds, NULL, &_tv));
}

const timeval &zappy::FDManager::get_tv() const
{
    return _tv;
}

void zappy::FDManager::set_tv(unsigned int usec)
{
    FDManager::_tv.tv_usec = usec;
}

bool zappy::FDManager::isFdSet(int fd, zappy::FDManager::FDType fdType)
{
    if (fdType == READ)
        return FD_ISSET(fd, &_rfds);
    else
        return FD_ISSET(fd, &_wfds);
}
