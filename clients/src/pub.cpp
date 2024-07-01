#include <chrono>
#include <iostream>
#include <fstream>

#include <mqtt/client.h>

const std::string SERVER_ADDRESS { "mqtt://localhost:8883" };
const std::string CLIENT_ID { "sync_publish_cpp" };
const std::string TOPIC { "hello" };

const std::string KEY_STORE         { "brokers/certs/ClientJohn.key" };
const std::string TRUST_STORE       { "brokers/certs/ca.crt" };
const std::string CA_PATH           { "brokers/certs" };
const std::string PRIVATE_KEY       { "brokers/certs/ClientJohn.crt" };

const std::string PAYLOAD1 { "Hello World!" };

const char* PAYLOAD2 = "Hi there!";

const int QOS = 1;

/////////////////////////////////////////////////////////////////////////////
// Class to receive callbacks

class user_callback : public virtual mqtt::callback
{
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		std::cout << "\n\t[Delivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << "]" << std::endl;
	}

public:
};

// --------------------------------------------------------------------------

bool keys_available()
{
    std::ifstream tstore(TRUST_STORE);
    if (!tstore) {
        std::cerr << "The trust store file does not exist: " << TRUST_STORE << std::endl;
        return false;
    }

    std::ifstream kstore(KEY_STORE);
    if (!kstore) {
        std::cerr << "The key store file does not exist: " << KEY_STORE << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    mqtt::client cli(SERVER_ADDRESS, CLIENT_ID, nullptr);

    user_callback cb;
    cli.set_callback(cb);

    if(not keys_available()) return 1;

    auto sslopts = mqtt::ssl_options_builder()
                .trust_store(TRUST_STORE)
                .key_store(KEY_STORE)
                .private_key(PRIVATE_KEY)
                .ca_path(CA_PATH)
                .ssl_version(3)
                .error_handler([](const std::string& msg) {
                    std::cerr << "SSL Error: " << msg << std::endl;
                })
                .finalize();

    auto connOpts = mqtt::connect_options_builder()
        .keep_alive_interval(std::chrono::seconds(20))
        .clean_session()
        .ssl(sslopts)
        .finalize();

    try {
        cli.connect(connOpts);

        // First use a message pointer.

        mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, PAYLOAD1);
        pubmsg->set_qos(QOS);
        cli.publish(pubmsg);

        // Now try with itemized publish.

        cli.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1, 0, false);

        // Disconnect

        cli.disconnect();
    }
    catch (const mqtt::persistence_exception& exc) {
        std::cerr << "Persistence Error: " << exc.what() << " ["
            << exc.get_reason_code() << "]" << std::endl;
        return 1;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << " ["
            << exc.get_reason_code() << "]" << std::endl;
        return 1;
    }

    return 0;
}