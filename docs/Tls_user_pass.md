## Introduction
This file describe a simple test to check mqtt broker working with TLS encryption with access only for the predefined set of users identified by user and password.

Broker operates at the localhost on port 8883.

## Ready to use
For the test purposes all certificates were generated for localhost operations.
The process of certificae creation could be observed in file [make_certificates.sh](../make_certificates.sh).
Please be aware that all of the certificates are self-signed (with password `1234`)

## How to

1. Open first terminal and start selected broker broker

```
./brokers/start_broker_tls_user_pass.sh

```

2. Open second terminal and subscribe to the broker for all topics that starts with `DEVICE_ID`

```
mosquitto_sub -p 8883 -t "DEVICE_ID/#" -u John -P Doe -cafile /repo/brokers/certs/ca.crt --cert /repo/brokers/certs/ClientJohn.crt --key /repo/brokers/certs/ClientJohn.key --tls-version tlsv1.3
```
where:
- -p - port on which broker is listening
- -t - topic to be subscribed (or topics with wildcards)
- -u - User name
- -P - User password
- --cafile - path to the certificate authority file
- --cert - path to the client certificate file (required only when `require_certificate` is set to true in broker configuration)
- --key - path to the client private key file (required only when `require_certificate` is set to true in broker configuration)
- --tls-version - version of tls encryption to be used

3. Open third terminal and publish messages to broker on selected topics that starts with `DEVICE_ID`

```
mosquitto_pub -p 8883 -t "DEVICE_ID/DEBUG_MSG" -m "This is first debug message" -u Alex -P Pass123 -cafile /repo/brokers/certs/ca.crt --cert /repo/brokers/certs/ClientAlex.crt --key /repo/brokers/certs/ClientAlex.key --tls-version tlsv1.3
```

where:
- -p - port on which broker is listening
- -t - topic where the message will be published
- -m - message to be sent to broker
- -u - User name
- -P - User password
- --cafile - path to the certificate authority file
- --cert - path to the client certificate file (required only when `require_certificate` is set to true in broker configuration)
- --key - path to the client private key file (required only when `require_certificate` is set to true in broker configuration)
- --tls-version - version of tls encryption to be used


### Notes:
- Observe on the second terminal if message was received by subscriber.
- Transmission and tcp packets could be observed on wireshark
