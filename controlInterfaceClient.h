#ifndef CONTROLINTERFACECLIENT_H
#define CONTROLINTERFACECLIENT_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

class ControlInterfaceClient {
public:
    ControlInterfaceClient(const std::string& inPipe,
                           const std::string& outPipe);

    ~ControlInterfaceClient();

    bool connect();
    void disconnect();
    bool isConnected() const { return running; }

    // --- API ---
    bool ostart();
    bool ostop();
    bool setTempo(int bpm);
    bool ctoggle(int channel);
    std::vector<std::string> list_styles();
    bool select_style(int id);

private:
    int write_fd = -1;
    int read_fd  = -1;

    std::thread reader_thread;
    std::atomic<bool> running;

    // Antwort-Synchronisation
    std::mutex m;
    std::condition_variable cv;
    std::queue<std::string> responses;

    void reader_loop();

    // intern
    bool send_command(const std::string& cmd, std::string& response, int timeout);
};

#endif
