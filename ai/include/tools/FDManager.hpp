//
// Created by Pierre Bougon on 23/06/17.
//

#ifndef CLIENTAI_FDMANAGER_HPP_
#define CLIENTAI_FDMANAGER_HPP_

#include <zconf.h>

namespace zappy
{
    class FDManager
    {
    public:
        enum FDType
        {
            READ,
            WRITE
        };
    public:
        FDManager();
        ~FDManager();

        void    manageFD(int fd);
        int     select(int i);
        bool    isFdSet(int fd, FDType);

        const timeval   &get_tv() const;
        void            set_tv(unsigned int usec);

    private:
        void reset_fds();

    private:
        fd_set  _rfds;
        fd_set  _wfds;
        timeval _tv;
    };
}


#endif // !CLIENTAI_FDMANAGER_HPP_
