INCLUDES                = -I$(top_builddir) -I$(top_srcdir) \
-I$(top_builddir)/libzmq -I$(top_srcdir)/libzmq

include_HEADERS = zmq.hpp

pkginclude_HEADERS = \
    ./zmq/api_thread.hpp \
    ./zmq/atomic_ptr.hpp \
    ./zmq/atomic_bitmap.hpp \
    ./zmq/atomic_counter.hpp \
    ./zmq/bp_decoder.hpp \
    ./zmq/decoder.hpp \
    ./zmq/dispatcher.hpp \
    ./zmq/err.hpp \
    ./zmq/i_signaler.hpp \
    ./zmq/tcp_socket.hpp \
    ./zmq/wire.hpp \
    ./zmq/ypipe.hpp \
    ./zmq/ypollset.hpp \
    ./zmq/ysemaphore.hpp \
    ./zmq/ysocketpair.hpp \
    ./zmq/poll_thread.hpp \
    ./zmq/epoll_thread.hpp \
    ./zmq/devpoll_thread.hpp \
    ./zmq/kqueue_thread.hpp \
    ./zmq/bp_encoder.hpp \
    ./zmq/encoder.hpp \
    ./zmq/stdint.hpp \
    ./zmq/bp_engine.hpp \
    ./zmq/i_pollable.hpp \
    ./zmq/command.hpp \
    ./zmq/mux.hpp \
    ./zmq/demux.hpp \
    ./zmq/i_thread.hpp \
    ./zmq/pipe.hpp \
    ./zmq/bp_listener.hpp \
    ./zmq/locator.hpp \
    ./zmq/i_engine.hpp \
    ./zmq/scope.hpp \
    ./zmq/config.hpp \
    ./zmq/yqueue.hpp \
    ./zmq/tcp_listener.hpp \
    ./zmq/i_locator.hpp \
    ./zmq/raw_message.hpp \
    ./zmq/message.hpp \
    ./zmq/ip.hpp \
    ./zmq/i_poller.hpp \
    ./zmq/thread.hpp \
    ./zmq/mutex.hpp \
    ./zmq/platform.hpp \
    ./zmq/formatting.hpp \
    ./zmq/select_thread.hpp \
    ./zmq/export.hpp \
    ./zmq/server_protocol.hpp

lib_LTLIBRARIES = libzmq.la

libzmq_la_SOURCES = $(pkginclude_HEADERS) \
    tcp_socket.cpp \
    ysocketpair.cpp \
    ypollset.cpp \
    ysemaphore.cpp \
    dispatcher.cpp \
    err.cpp \
    bp_decoder.cpp \
    bp_encoder.cpp \
    api_thread.cpp \
    poll_thread.cpp \
    epoll_thread.cpp \
    devpoll_thread.cpp \
    kqueue_thread.cpp \
    bp_engine.cpp \
    mux.cpp \
    demux.cpp \
    pipe.cpp \
    bp_listener.cpp \
    locator.cpp \
    tcp_listener.cpp \
    ip.cpp \
    thread.cpp \
    select_thread.cpp

libzmq_la_LDFLAGS = -version-info 0:0:0
libzmq_la_CXXFLAGS = -Wall -pedantic

dist-hook:
		-rm $(distdir)/platform.hpp

