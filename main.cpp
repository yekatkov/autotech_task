#include <cassert>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "Application/Public/XYReceiver.h"
#include "Application/Public/XYTransmitter.h"
#include "Utils/ThreadSafeLogger.h"

// Visit black magic
template <class... Ts>
struct overload : Ts... { using Ts::operator()...; };
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

using namespace std;

void receiveRoutine(uint16_t deviceId, vector<ApplicationLayer::XY>& receivedData)
{
    using namespace ApplicationLayer;
    auto& logger = Utils::ThreadSafeLogger::getImpl();

    XYReceiver xyReceiver(deviceId);

    bool stop{false};
    while (!stop)
    {
        auto packet = xyReceiver.receive();

        visit(overload{
                  [&logger, &deviceId, &receivedData](const XY& xy)
                  {
                      ostringstream msg;
                      msg << "[DeviceId: " << deviceId
                          << "] was received: [" << xy.getX() << ", " << xy.getY() << "]" << endl;
                      logger.writeLog(msg.str());
                      receivedData.push_back(xy);
                  },
                  [&stop, &logger](const Protocol::Command& command)
                  {
                      switch (command)
                      {
                      case Protocol::Command::Stop:
                          {
                              ostringstream msg;
                              msg << "Stop was received" << endl;
                              logger.writeLog(msg.str());
                              stop = true;
                              break;
                          }
                      default:
                          {
                              ostringstream msg;
                              msg << "Wrong command: " << static_cast<size_t>(command) << endl;
                              logger.writeLog(msg.str());
                          }
                      }
                  }
              }, packet);
    }
};

int main()
{
    using namespace ApplicationLayer;
    const auto& logger = Utils::ThreadSafeLogger::getImpl();

    // Add this vectors for the test purpose. We will fill them with transmitted and received data and
    // compare them at the end.
    vector<XY> receivedData, transmittedData;

    constexpr uint16_t deviceId{123};

    thread receiver(receiveRoutine, deviceId, std::ref(receivedData));

    XY xy;
    XYTransmitter xyTransmitter(deviceId);
    // We will use this transmitter for checking that our receiver filters data by deviceId properly
    XYTransmitter fakeXyTransmitter(1);

    for (size_t i = 0; i < 100; ++i)
    {
        // For test purposes mix transmitters with different deviceIds
        bool useMainTransmitter = i % 2 == 0;
        auto& usedTransmitter =  useMainTransmitter ? xyTransmitter : fakeXyTransmitter;

        usedTransmitter.send(xy);
        if(useMainTransmitter)
        {
            transmittedData.push_back(xy);
        }

        ostringstream msg;
        msg << "[DeviceId: " << usedTransmitter.getDeviceId()
            << "] was sent: [" << xy.getX() << ", " << xy.getY() << "]" << endl;
        logger.writeLog(msg.str());

        xy.modify(1, -1);

        // Comment this line for add more concurency!
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Send command that threre aren't more packets.
    xyTransmitter.send(Protocol::Command::Stop);

    receiver.join();

    if(receivedData == transmittedData)
    {
        logger.writeLog("Test passed!");
    }
    else
    {
        logger.writeLog("Test failed!");
    }

    return 0;
}
