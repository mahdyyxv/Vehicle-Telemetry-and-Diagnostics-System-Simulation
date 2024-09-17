#pragma once
#include <boost/asio.hpp>
#include <string>

class Rpi {
public:
    static Rpi &getInstance();
    std::string getSensorsData(const std::string &what);

private:
    Rpi();
    std::string getDevices();
    bool initializeSerialPort(boost::asio::serial_port &serial,
                              const std::string &device);
    std::string devicePath;
    bool deviceExist = false;
};
