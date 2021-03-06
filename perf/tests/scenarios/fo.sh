#!/bin/sh
#
# Copyright (c) 2007-2009 FastMQ Inc.
#
# This file is part of 0MQ.
#
# 0MQ is free software; you can redistribute it and/or modify it under
# the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# 0MQ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Lesser GNU General Public License for more details.
#
# You should have received a copy of the Lesser GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

GL_IP="127.0.0.1"
GL_PORT=5555

REC_IP="127.0.0.1"
REC_PORT=5672

MSG_SIZE_START=1
MSG_SIZE_STEPS=10

RUNS=3

TEST_TIME=5000

LOCAL_BIN="./local_fo"
REMOTE_BIN="./remote_fo"

######################## Do not edit below this line ##########################

if [ $# -lt 2 ]; then
    echo "Usage: fo.sh [local number_of_subscribers | remote subs_id]"
    exit 1
fi

if [ $1 != "local" -a $1 != "remote" ]; then
    echo "Usage: fo.sh [local number_of_subscribers |remote subs_id]"
    exit 1
fi


SYS_LAT_DEN=100
SYS_SLOPE=0.55
SYS_OFF=110
SYS_BREAK=1024

SYS_SLOPE_BIG=0.89
SYS_OFF_BIG=0

if [ $1 = "local" ]; then
    echo "running local (sender)"    
    while [ $RUNS -gt 0 ]; do
        for i in `seq 0 $MSG_SIZE_STEPS`;
        do
            let MSG_SIZE=2**$i

            if [ $MSG_SIZE -lt $SYS_BREAK ]; then
                MSG_COUNT=`echo "($TEST_TIME * 100000 ) / ($SYS_SLOPE * $MSG_SIZE + $SYS_OFF)" | bc`
            else
                MSG_COUNT=`echo "($TEST_TIME * 100000 ) / ($SYS_SLOPE_BIG * $MSG_SIZE + $SYS_OFF_BIG)" | bc`
            fi

            $LOCAL_BIN $GL_IP $GL_PORT $REC_IP $REC_PORT $MSG_SIZE $MSG_COUNT $2
        done
        let RUNS=RUNS-1 
    done
else
    echo "running remote (receiver)"
    while [ $RUNS -gt 0 ]; do
        for i in `seq 0 $MSG_SIZE_STEPS`;
        do
            let MSG_SIZE=2**$i

            if [ $MSG_SIZE -lt $SYS_BREAK ]; then
                MSG_COUNT=`echo "($TEST_TIME * 100000 ) / ($SYS_SLOPE * $MSG_SIZE + $SYS_OFF)" | bc`
            else
                MSG_COUNT=`echo "($TEST_TIME * 100000 ) / ($SYS_SLOPE_BIG * $MSG_SIZE + $SYS_OFF_BIG)" | bc`
            fi

            $REMOTE_BIN $GL_IP $GL_PORT $MSG_SIZE $MSG_COUNT $2
            sleep 1
        done
        let RUNS=RUNS-1 
    done
    echo
fi
