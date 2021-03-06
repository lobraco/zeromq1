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

#ifndef __ZMQ_LOAD_BALANCER_HPP_INCLUDED__
#define __ZMQ_LOAD_BALANCER_HPP_INCLUDED__

#include <vector>

#include <zmq/i_demux.hpp>

namespace zmq
{

    //  Object to distribute messages to outbound pipes.

    class load_balancer_t : public i_demux
    {
    public:

        load_balancer_t ();

        //  i_demux interface implementation.
        ~load_balancer_t ();
        void send_to (pipe_t *pipe_);
        bool write (message_t &msg_);
        void flush ();
        void gap ();
        bool empty ();
        void release_pipe (pipe_t *pipe_);
        void initialise_shutdown ();

        bool load_balancing ()
        {
            return true;
        }

    private:

        //  The list of outbound pipes.
        typedef std::vector <pipe_t*> pipes_t;
        pipes_t pipes;

        //  Index of the pipe that will receive next message.
        unsigned current;

        load_balancer_t (const load_balancer_t&);
        void operator = (const load_balancer_t&);
    };

}

#endif
