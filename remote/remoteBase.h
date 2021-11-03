#ifndef REMOTEBASE_H
#define REMOTEBASE_H
#include "remote.h"
#include "remoteUDP.h"
#include "remoteTCP.h"

Remote* RemoteAuto(QString type);

#endif // REMOTEBASE_H
