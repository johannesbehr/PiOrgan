#include "controlInterfaceClient.h"

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <poll.h>

using json = nlohmann::json;

ControlInterfaceClient::ControlInterfaceClient(const std::string& outPipe, const std::string& inPipe)
{
   
}

ControlInterfaceClient::~ControlInterfaceClient() {
    disconnect();
}

bool ControlInterfaceClient::connect() {
    running = true;
    reader_thread = std::thread(&ControlInterfaceClient::reader_loop, this);

    return true;
}

void ControlInterfaceClient::disconnect() {
    running = false;

    if (reader_thread.joinable())
        reader_thread.join();

    if (write_fd >= 0) close(write_fd);
    if (read_fd >= 0) close(read_fd);
}

//
// READER
//

void ControlInterfaceClient::reader_loop() {


    char buffer[1024];
    std::string line;

     // ACHTUNG:
    // Client schreibt in "inPipe" (Server liest dort)
    std::cout << "ControlInterfaceClient: Connecting to pipes..." << std::endl;
    read_fd  = open("/tmp/stygmorgan_out", O_RDONLY | O_NONBLOCK);
    write_fd = open("/tmp/stygmorgan_in", O_WRONLY);

    struct pollfd pfd;
    pfd.fd = read_fd;
    pfd.events = POLLIN;
    
    if(write_fd >= 0 ){
        std::string msg = "\n";
        write(write_fd, msg.c_str(), msg.size());
    }

    std::cout << "ControlInterfaceClient: Connected!" << std::endl;
 
    while (running) {

        int ret = poll(&pfd, 1, 100); // 100ms timeout
        if (ret <= 0) continue;
        if (pfd.revents & POLLIN) {
            ssize_t n = read(read_fd, buffer, sizeof(buffer)-1);
            if (n <= 0) continue;

            buffer[n] = '\0';
            line += buffer;
            //std::cout << "ControlInterfaceClient: Read data: " << buffer << std::endl; 

            size_t pos;
            while ((pos = line.find('\n')) != std::string::npos) {
                std::string msg = line.substr(0, pos);
                line.erase(0, pos + 1);

                // 👉 hier unterscheiden wir response vs event
                if (msg.find("\"event\"") != std::string::npos) {
                    // optional: Event-Callback später
                    continue;
                }

                {
                    std::cout << "ControlInterfaceClient: Push response " << msg << std::endl; 
                    std::lock_guard<std::mutex> lock(m);
                    responses.push(msg);
                }
                cv.notify_one();
            }
        }
    }

/* struct pollfd pfd;
    pfd.fd = read_fd;
    pfd.events = POLLIN;

    char buffer[1024];
    std::string line;

    while (running) {

        int ret = poll(&pfd, 1, 100); // 100ms timeout

        if (ret <= 0) continue;

        if (pfd.revents & POLLIN) {
            ssize_t n = read(read_fd, buffer, sizeof(buffer)-1);
            if (n <= 0) continue;

            buffer[n] = '\0';
            line += buffer;

            size_t pos;
            while ((pos = line.find('\n')) != std::string::npos) {
                std::string cmd = line.substr(0, pos);
                line.erase(0, pos + 1);

                process_input(cmd);
            }
        }
    }
*/

}

//
// CORE SEND
//

bool ControlInterfaceClient::send_command(const std::string& cmd,
                                          std::string& response,
                                          int timeout = 2000)
{
    std::string msg = cmd + "\n";

    // 🔒 optional: write absichern
    ssize_t n = write(write_fd, msg.c_str(), msg.size());
    if (n <= 0) {
        return false;
    }
    std::cout<< "ControlInterfaceClient: Sent command: " << cmd << std::endl;

    std::unique_lock<std::mutex> lock(m);

    // ⏱️ Timeout-Wait
    bool got_response = cv.wait_for(
        lock,
        std::chrono::milliseconds(timeout),
        [&]{ return !responses.empty(); }
    );

    if (!got_response) {
        // ❌ Timeout
        std::cout << "ControlInterfaceClient: Timeout waiting for response to command: " << cmd << std::endl;
    }


    response = responses.front();
    responses.pop();

    return true;
}
//
// API
//

bool ControlInterfaceClient::ostart() {
    json j;
    j["cmd"] = "ostart";

    std::string resp;
    if (!send_command(j.dump(), resp)) {
        return false;
    }

    try{
        auto jr = json::parse(resp);
        return jr["status"] == "ok";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return false;
    }
}

bool ControlInterfaceClient::ostop() {
    json j;
    j["cmd"] = "ostop";

    std::string resp;
    if (!send_command(j.dump(), resp)) {
        return false;
    }

    try{
        auto jr = json::parse(resp);
        return jr["status"] == "ok";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return false;
    }
}

bool ControlInterfaceClient::setTempo(int bpm) {
    json j;
    j["cmd"] = "tempo";
    j["value"] = bpm;

    std::string resp;
    if (!send_command(j.dump(), resp)) {
        return false;
    }

    try{
        auto jr = json::parse(resp);
        return jr["status"] == "ok";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return false;
    }
}


bool ControlInterfaceClient::ctoggle(int channel) {
    json j;
    j["cmd"] = "ctoggle";
    j["channel"] = channel;

    std::string resp;
    if (!send_command(j.dump(), resp)) {
        return false;
    }

    try{
        auto jr = json::parse(resp);
        return jr["status"] == "ok";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return false;
    }
}


std::vector<std::string> ControlInterfaceClient::list_styles() {
    json j;
    j["cmd"] = "list_styles";

    std::string resp;
    if (!send_command(j.dump(), resp)) {

        std::cout << "Command returned false / failed." << std::endl;
        return {};
    }

    std::cout << "Command successfull, response:" << resp << std::endl;

    
    try {
        auto jr = json::parse(resp);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return {};
    }

    std::vector<std::string> styles;
    json jr;

    try {
        jr = json::parse(resp);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return {};
    }

    if (jr.contains("styles")) {
        for (auto& s : jr["styles"]) {
            styles.push_back(s);
        }
    }

    return styles;
}

bool ControlInterfaceClient::select_style(int id) {
    json j;
    j["cmd"] = "select_style";
    j["id"] = id;

    std::string resp;
    if (!send_command(j.dump(), resp)) {
        return false;
    }

    try{
        auto jr = json::parse(resp);
        return jr["status"] == "ok";
    } catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
        return false;
    }
}
