/*
    Copyright (c) 2007 FastMQ Inc.

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_BP_ENCODER_HPP_INCLUDED__
#define __ZMQ_BP_ENCODER_HPP_INCLUDED__

#include <stddef.h>
#include <assert.h>

#include "encoder.hpp"

namespace zmq
{

    class bp_encoder_t : public encoder_t <bp_encoder_t>
    {
    public:

        bp_encoder_t (dispatcher_proxy_t *proxy_, int source_thread_id_,
            size_t chunk_size_);

    protected:

        bool size_ready ();
        bool message_ready ();

        unsigned char tmpbuf [9];
    };

}

#endif