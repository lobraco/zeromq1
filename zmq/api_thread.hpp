/*
    Copyright (c) 2007-2008 FastMQ Inc.

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


#ifndef __ZMQ_API_THREAD_HPP_INCLUDED__
#define __ZMQ_API_THREAD_HPP_INCLUDED__

#include <vector>
#include <string>
#include <utility>

#include "export.hpp"
#include "config.hpp"
#include "i_thread.hpp"
#include "i_engine.hpp"
#include "i_locator.hpp"
#include "i_poller.hpp"
#include "message.hpp"
#include "dispatcher.hpp"
#include "mux.hpp"
#include "demux.hpp"
#include "ypollset.hpp"
#include "scope.hpp"
#include "zmq_server.hpp"
#include "select_thread.hpp"
#include "platform.hpp"

namespace zmq
{
    //  Thread object to be used as a proxy for client application thread.
    //  It is not thread-safe. In case you want to use 0MQ from several
    //  client threads create api_thread for each of them.

    class api_thread_t : private i_thread, private i_engine
    {
    public:

        //  Creates API thread and attaches it to the command dispatcher and
        //  resource locator.
        ZMQ_EXPORT static api_thread_t *create (dispatcher_t *dispatcher_,
            i_locator *locator_);

        //  Destroys API engine.
        ZMQ_EXPORT ~api_thread_t ();

        //  Creates new exchange, returns exchange ID.
        ZMQ_EXPORT int create_exchange (
            const char *exchange_, scope_t scope_ = scope_local,
            const char *interface_ = NULL, i_thread *listener_thread_ = NULL,
            int handler_thread_count_ = 0, i_thread **handler_threads_ = NULL);

        //  Creates new queue, returns queue ID.
        ZMQ_EXPORT int create_queue (
            const char *queue_, scope_t scope_ = scope_local,
            const char *interface_ = NULL, i_thread *listener_thread_ = NULL,
            int handler_thread_count_ = 0, i_thread **handler_threads_ = NULL);

        //  Binds an exchange to a queue.
        ZMQ_EXPORT void bind (const char *exchange_, const char *queue_,
            i_thread *exchange_thread_, i_thread *queue_thread_);

        //  Send a message to specified exchange. 0MQ takes responsibility
        //  for deallocating the message. If there are any pending pre-sent
        //  messages, flush them immediately.
        ZMQ_EXPORT void send (int exchange_id_, message_t &msg_);

        //  Presend the message. The message will be stored internally and
        //  sent only after 'flush' is called. In other respects it behaves
        //  the same as 'send' function.
        ZMQ_EXPORT void presend (int exchange_id_, message_t &msg_);

        //  Flush all the pre-sent messages.
        ZMQ_EXPORT void flush ();

        //  Receive a message. If 'block' argument is true, it'll block till
        //  message arrives. It returns ID of the queue message was retrieved
        //  from, 0 is no message was retrieved.
        ZMQ_EXPORT int receive (message_t *msg_, bool block_ = true);

    private:

        api_thread_t (dispatcher_t *dispatcher_, i_locator *locator_);

        //  i_thread implementation.
        dispatcher_t *get_dispatcher ();
        int get_thread_id ();
        void send_command (i_thread *destination_, const command_t &command_);

        //  i_engine implementation.
        engine_type_t type ();
        void process_command (const engine_command_t &command_);

        //  Processes single command.
        void process_command (const command_t &command_);

        //  Checks for signals and processes available commands.
        void process_commands ();

        //  Processes available commands. Signals are supplied by the caller.
        void process_commands (ypollset_t::integer_t signals_);

        //  Determines when we are going to poll in 'receive' function. See
        //  api_thread_poll_rate's description in config.hpp to get better
        //  understanding of the algorithm used.
        int ticks;

        //  Stored pointer to the dispatcher.
        dispatcher_t *dispatcher;

        //  Stored pointer to the locator.
        i_locator *locator;

        //  Thread ID assigned to this thread by dispatcher.
        int thread_id;

        //  Used to poll for signals coming from other threads.
        ypollset_t pollset;

        //  List of exchanges belonging to the API thread.
        typedef std::vector <std::pair <std::string, demux_t*> > exchanges_t;
        exchanges_t exchanges;

        //  List of queues belonging to the API thread.
        typedef std::vector <std::pair <std::string, mux_t*> > queues_t;
        queues_t queues;

        //  Current queue points to the queue to be used to retrieving
        //  next message.
        queues_t::size_type current_queue; 

#if (defined (__GNUC__) && (defined (__i386__) || defined (__x86_64__)))
        //  Time when last command processing was performed (in ticks).
        //  This optimisation requires RDTSC instruction and is thus
        //  available only on x86 platforms.
        uint64_t last_command_time;   
#endif

        api_thread_t (const api_thread_t&);
        void operator = (const api_thread_t&);
    };

}

#endif
