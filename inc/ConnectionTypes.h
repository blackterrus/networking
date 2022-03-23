#ifndef CONNECTIONTYPES_H_
#define CONNECTIONTYPES_H_

enum ConnectionType
{
    UDP_CONN,
    TCP_CONN,
    MAX_CONN_TYPES
};

enum ConnectionRole
{
    XMIT_SEND, // Can only send
    XMIT_RECV, // Can only recv
    XMIT_DUAL, // Can do both
    MAX_ROLES
};

#endif