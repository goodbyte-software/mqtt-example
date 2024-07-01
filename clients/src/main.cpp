#include <chrono>
#include <iostream>

#include <mqtt/client.h>

const std::string SERVER_ADDRESS { "mqtt://localhost:1883" };
const std::string CLIENT_ID { "sync_publish_cpp" };
const std::string TOPIC { "hello" };

const std::string PAYLOAD1 { "Hello World!" };

const char* PAYLOAD2 = "Hi there!";
const char* PAYLOAD3 = "Is anyone listening?";

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

int main(int argc, char* argv[])
{
    mqtt::client cli(SERVER_ADDRESS, CLIENT_ID, nullptr);

    user_callback cb;
    cli.set_callback(cb);

    auto connOpts = mqtt::connect_options_builder()
        .keep_alive_interval(std::chrono::seconds(20))
        .clean_session()
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