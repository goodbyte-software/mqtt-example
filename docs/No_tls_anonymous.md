## Introduction
This file describe a simple test to check mqtt broker working withuot TLS encryption with enabled access for anonymous clients.

Broker operates at the localhost on port 1883.

## How to

1. Open first terminal and start selected broker broker

```
./brokers/start_broker_no_tls_anonymous.sh

```

2. Open second terminal and subscribe to the broker for all topics that starts with `DEVICE_ID`

```
mosquitto_sub -p 1883 -t "DEVICE_ID/#"
```
where:
- -p - port on which broker is listening
- -t - topic to be subscribed (or topics with wildcards)

3. Open third terminal and publish messages to broker on selected topics that starts with `DEVICE_ID`

```
mosquitto_pub -p 1883 -t "DEVICE_ID/DEBUG_MSG" -m "This is first debug message"
```

where:
- -p - port on which broker is listening
- -t - topic where the message will be published
- -m - message to be sent to broker

### Notes:
- Observe on the second terminal if message was received by subscriber.
- Transmission and tcp packets could be observed on wireshark