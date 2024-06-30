# MQTT example


## MQTT brokers
The demo is able to start 4 types of mqtt brokers:
- No TLS, Anonymous users allowed on port 1883
- No TLS, Only known users allowed (user, pass) on port 1883
- With TLS, Anonymous users allowed on port 8883
- With TLS  Only known users allowed (user, pass) on port 8883

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


## Example
To run one of the broker and test its funcitonality please refer to selected doc file and follow the instruction:
- [No TLS, Anonymous](./docs/No_tls_anonymous.md)
- [No TLS, User password](./docs/No_tls_user_pass.md)
- [TLS, Anonymous](./docs/Tls_anonymous.md)
- [TLS, User password](./docs/Tls_user_pass.md)