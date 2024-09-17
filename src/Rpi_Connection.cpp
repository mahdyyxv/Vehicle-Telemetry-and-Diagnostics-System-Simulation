#include "Rpi_Connection.hpp"
#include "Logger.hpp" // Assume Logger class is included
#include "common.hpp"
#include <memory>
#include <vector>

Rpi::Rpi() {
  devicePath = getDevices();
  if (!devicePath.empty()) {
    deviceExist = true;
  } else {
    deviceExist = false;
  }
}

Rpi &Rpi::getInstance() {
  static Rpi Instance;
  return Instance;
}

std::string Rpi::getDevices() {
  std::string devicLocation = common::execCommand("ls /dev/ttyACM* ");

  if (devicLocation.find("cannot") != std::string::npos) {
    Logger::getInstance().log("No devices found.");
    return "";
  }

  std::vector<std::string> devices;
  std::istringstream stream(devicLocation);
  std::string word;

  while (stream >> word) {
    devices.push_back(word);
  }

  for (auto &device : devices) {
    try {
      boost::asio::io_service io;
      std::unique_ptr<boost::asio::serial_port> serial(
          new boost::asio::serial_port(io));

      if (!initializeSerialPort(*serial, device)) {
        continue;
      }

      std::string command = "Pico ?\n";
      boost::asio::write(*serial, boost::asio::buffer(command));

      boost::asio::streambuf response;
      boost::asio::read_until(*serial, response, '\n');
      std::istream response_stream(&response);
      std::string response_str;
      std::getline(response_stream, response_str);

      if (response_str == "Yes") {
        Logger::getInstance().log("Device found: " + device);
        serial->close();
        return device;
      }

      serial->close();
    } catch (boost::system::system_error &error) {
      Logger::getInstance().log("Error accessing device " + device + ": " +
                                error.what());
    }
  }

  return "";
}

bool Rpi::initializeSerialPort(boost::asio::serial_port &serial,
                               const std::string &device) {
  try {
    serial.open(device);

    serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
    serial.set_option(boost::asio::serial_port_base::character_size(8));
    serial.set_option(boost::asio::serial_port_base::parity(
        boost::asio::serial_port_base::parity::none));
    serial.set_option(boost::asio::serial_port_base::stop_bits(
        boost::asio::serial_port_base::stop_bits::one));
    serial.set_option(boost::asio::serial_port_base::flow_control(
        boost::asio::serial_port_base::flow_control::none));

    return true;
  } catch (const std::exception &e) {
    Logger::getInstance().log("Failed to initialize serial port: " +
                              std::string(e.what()));
    return false;
  }
}

std::string Rpi::getSensorsData(const std::string &what) {
  if (!deviceExist) {
    Logger::getInstance().log("No device connected.");
    return "NULL";
  }

  try {
    boost::asio::io_service io;
    std::unique_ptr<boost::asio::serial_port> serial(
        new boost::asio::serial_port(io));

    if (!initializeSerialPort(*serial, devicePath)) {
      Logger::getInstance().log("Failed to open serial port.");
      return "NULL";
    }

    std::string command = what + "\n";
    boost::asio::write(*serial, boost::asio::buffer(command));

    boost::asio::streambuf response;
    boost::asio::read_until(*serial, response, '\n');
    std::istream response_stream(&response);
    std::string response_str;
    std::getline(response_stream, response_str);

    Logger::getInstance().log("Sensor data received: " + response_str);
    serial->close();
    return response_str;
  } catch (boost::system::system_error &error) {
    Logger::getInstance().log("Error: " + std::string(error.what()));
  }

  return "NULL";
}
