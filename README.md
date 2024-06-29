# MQTT example


## MQTT brokers
The demo is able to start 4 types of mqtt brokers:
- No TLS, Anonymous users allowed on port 1883
- No TLS, Only known users allowed (user, pass) on port 1884
- With TLS, Anonymous users allowed on port 8883
- With TLS  Only known users allowed (user, pass) on port 8884

Each of them have its own dedicated config file.
- [brokers/cfg_no_tls_anonymous.conf](./brokers/cfg_no_tls_anonymous.conf)
- [brokers/cfg_no_tls_user_pass.conf](./brokers/cfg_no_tls_user_pass.conf)
- [brokers/cfg_tls_anonymous.conf](./brokers/cfg_tls_anonymous.conf)
- [brokers/cfg_tls_user_pass.conf](./brokers/cfg_tls_user_pass.conf)

### Users and passwords for test purposes
For the testing purposes 2 users were created.

| User | Password |
|------|--------- |
| John | Doe      |
| Alex | Pass123  |

User credentials are stored in the file [brokers/users/passwd](./brokers/users/passwd)`. the file has an encrypted passwords and was created using steps presented below:
1. Create passwd file `touch passwd_path`
2. Add first user and password `mosquitto_passwd -b passwd_path John Doe`
3. Add next user and password `mosquitto_passwd -b passwd_path Alex Pass123`
