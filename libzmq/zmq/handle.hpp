/*
    Copyright (c) 2007-2009 FastMQ Inc.

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_HANDLE_HPP_INCLUDED__
#define __ZMQ_HANDLE_HPP_INCLUDED__

#include <assert.h>
#include <zmq/fd.hpp>

namespace zmq
{

    //  Class to encapsulate union {fd_t, *void} for polling mechanisms.
    class handle_t
    {
    public:

        handle_t () {
            has_fd = false;
            has_ptr = false;
        };

        handle_t (void *ptr_) {
            has_ptr = true;
            handle.ptr = ptr_;
        };

        handle_t (fd_t fd_) {
            has_fd = true;
            handle.fd = fd_;
        }

        void fd (fd_t fd_) {
            has_ptr = false;
            has_fd = true;
            handle.fd = fd_;
        }

        fd_t fd () {
            assert (has_fd);
            return handle.fd;
        };

        void *ptr () {
            assert (has_ptr);
            return handle.ptr;
        };

        void ptr (void *ptr_) {
            has_fd = false;
            has_ptr = true;
            handle.ptr = ptr_;
        };

        bool operator == (const handle_t &other_) const {
            assert (this->has_fd || this->has_ptr);
            assert (other_.has_fd || other_.has_ptr);

            if (this->has_fd) {
                assert (other_.has_fd);
                return this->handle.fd == other_.handle.fd;
            }
            
            if (this->has_ptr) {
                assert (other_.has_ptr);
                return this->handle.ptr == other_.handle.ptr;
            }
           
            return (false);
        };

        bool operator != (const handle_t &other_) const {
            return !(*this == other_);
        };

    private:
        union
        {
            fd_t fd;
            void *ptr;
        } handle;

        bool has_fd;
        bool has_ptr;
    };

}
#endif
