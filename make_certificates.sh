#!/bin/bash

# Create Certificate authoruty key and certificate
openssl genrsa -des3 -out ca.key 2048
openssl req -new -x509 -days 1826 -key ca.key -out ca.crt  -subj "/C=PL/ST=LowerSilesian/L=Wloclaw/O=GoodByte/CN=goodByteCA/emailAddress=ca@goodbyte.pl"

# Create key and certificate sign request for broker
openssl genrsa -out broker.key 2048
openssl req -new -out broker.csr -key broker.key -subj "/C=PL/ST=LowerSilesian/L=Wloclaw/O=GoodByte/CN=localhost/emailAddress=broker@goodbyte.pl"

# Sign broker certificate using CA certificate - self signed
openssl x509 -req -in broker.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out broker.crt -days 360

# Create key and certificate sign request for client John
openssl genrsa -out ClientJohn.key 2048
openssl req -new -out ClientJohn.csr -key ClientJohn.key -subj "/C=PL/ST=LowerSilesian/L=Wloclaw/O=GoodByte/CN=localhost/emailAddress=john@goodbyte.pl"
# Sign ClientJohn certificate using CA certificate - self signed
openssl x509 -req -in ClientJohn.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out ClientJohn.crt -days 360
# Convert crt and key into PEM format
openssl x509 -inform PEM -in ClientJohn.crt -out ClientJohn.crt.pem
openssl rsa -inform PEM -in ClientJohn.key -out ClientJohn.key.pem
# Create keystore.pem reuired by paho.mqtt.cpp library
cat ClientJohn.key.pem ClientJohn.crt.pem > ClientJohn_keystore.pem

# Create key and certificate sign request for client Alex
openssl genrsa -out ClientAlex.key 2048
openssl req -new -out ClientAlex.csr -key ClientAlex.key -subj "/C=PL/ST=LowerSilesian/L=Wloclaw/O=GoodByte/CN=localhost/emailAddress=alex@goodbyte.pl"
# Sign ClientAlex certificate using CA certificate - self signed
openssl x509 -req -in ClientAlex.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out ClientAlex.crt -days 360
# Convert crt and key into PEM format
openssl x509 -inform PEM -in ClientAlex.crt -out ClientAlex.crt.pem
openssl rsa -inform PEM -in ClientAlex.key -out ClientAlex.key.pem
# Create keystore.pem reuired by paho.mqtt.cpp library
cat ClientAlex.key.pem ClientAlex.crt.pem > ClientAlex_keystore.pem
