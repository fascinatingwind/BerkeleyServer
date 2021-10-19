#ifndef BERKELEYSERVER_PORTHELPER_H
#define BERKELEYSERVER_PORTHELPER_H
namespace Network
{
    class PortHelper
    {
    public:
        PortHelper() = delete;
        ~PortHelper() = delete;

        inline static size_t TCP_PORT = 1001;
        inline static size_t UDP_PORT = 1002;
    };
}
#endif //BERKELEYSERVER_PORTHELPER_H
