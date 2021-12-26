#include "../../include/danya_server.h"

int main(int argc, char* argv[]) {
    Server myServer(3000);
    myServer.sendData();
    myServer.startServer();
    return 0;
}

