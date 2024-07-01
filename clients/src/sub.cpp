#include <iostream>
#include <chrono>
#include <vector>

#include <mqtt/client.h>

const std::string SERVER_ADDRESS    { "mqtt://localhost:8883" };
const std::string CLIENT_ID         { "subsriber" };

const std::string KEY_STORE         { "brokers/certs/ClientJohn.key" };
const std::string TRUST_STORE       { "brokers/certs/ClientJohn.crt" };

int main(int argc, char* argv[])
{
    mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

    auto sslopts = mqtt::ssl_options_builder()
                   .trust_store(TRUST_STORE)
                   .key_store(KEY_STORE)
                   .error_handler([](const std::string& msg) {
                       std::cerr << "SSL Error: " << msg << std::endl;
                   })
                   .finalize();

    auto connOpts = mqtt::connect_options_builder()
        .keep_alive_interval(std::chrono::seconds(30))
        .automatic_reconnect(std::chrono::seconds(2), std::chrono::seconds(30))
        .clean_session(false)
        .ssl(sslopts)
        .finalize();

    const std::vector<std::string> TOPICS { "hello", "command" };
    const std::vector<int> QOS { 1, 1 };

    try {
        std::cout << "Connecting to the MQTT server..." << std::flush;
        mqtt::connect_response rsp = cli.connect(connOpts);
        std::cout << "OK\n" << std::endl;

        if (!rsp.is_session_present()) {
            std::cout << "Subscribing to topics..." << std::flush;
            cli.subscribe(TOPICS, QOS);
            std::cout << "OK" << std::endl;
        }
        else {
            std::cout << "Session already present. Skipping subscribe." << std::endl;
        }

        while (true) {
            auto msg = cli.consume_message();

            if (msg) {
                std::cout << msg->get_topic() << ": " << msg->to_string() << std::endl;
            }
            else if (!cli.is_connected()) {
                std::cout << "Lost connection" << std::endl;
                while (!cli.is_connected()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                }
                std::cout << "Re-established connection" << std::endl;
            }
        }

        // Disconnect

        std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
        cli.disconnect();
        std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    return 0;
}

