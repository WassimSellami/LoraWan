# LoraWan
Deploiement d'un réseau IoT lorawan Multitenant sur le technopole ElGhazala
# Project Description
Deployment of a Lorawan Multitenant IoT network on the ElGhazala technopole
This involves installing 3 gateways connected to the ChirpStack network server.
For a user to exploit the network simply ask the admin to create a tenant on Chirpstack
and assign it as admin to that tenant. The admin adds the gateways to each tenant.
Now the user can create applications and add the end-devices associated with this application.
This project targets all students, PhD students and teachers of Sup'Com as well as professionals in partnership.

Installation des serveurs ChirpStack 
Installing ChirpStack Servers 
# Installation of ChirpStack servers 
v3:https://www.chirpstack.io/project/guides/debian-ubuntu/
v4: https://www.chirpstack.io/docs/getting-started/debian-ubuntu.html

# Gateway 
[link of gateway's Seeeduino](https://wiki.seeedstudio.com/LoRa_LoRaWan_Gateway_Kit/)
[link of gateway’s Seeeduino](https://wiki.seeedstudio.com/LoRa_LoRaWan_Gateway_Kit/)
installation of gateway and registration to TTN https://www.cytron.io/tutorial/lora-gateway-setup-for-rhf0m301-raspberry-pi-with-basic-station

# Technologie LoraWan
The LoRaWAN protocol is a Low Power Wide Area Networking (LPWAN) communication protocol that functions on LoRa. The LoRaWAN specification is open so anyone can set up and operate a LoRa network.

LoRa is a wireless audio frequency technology that operates in a license-free radio frequency spectrum. LoRa is a physical layer protocol that uses spread spectrum modulation and supports long-range communication at the cost of a narrow bandwidth. It uses a narrow band waveform with a central frequency to send data, which makes it robust to interference.
![image](https://user-images.githubusercontent.com/60314904/226999754-2b9d428d-7b7b-4ab7-8c82-604922331b71.png)


# Architecture ChirpStack
The gateway contains the UDP packet forwarder that forwards packets coming from the lora physical layer to the chorpstack gateway bridge and next to the MQTT broker that communicates with the network server.
The network server can exchange events with the client application through integrations(HTTP, MQTT, InfluxDB...).
![image](https://user-images.githubusercontent.com/60314904/226999641-904224c3-7c43-4159-9ca5-77e4e7651852.png)

# Seeeduino lorawan gateway kit
This kit provides all the basic elements you need: a Raspberry Pi 3, a Seeeduino LoRaWAN with GPS and a gateway & local server that allows you to collect and transfer data among all your LoRa nodes.
https://wiki.seeedstudio.com/LoRa_LoRaWan_Gateway_Kit/

# Testing on local server
Using the built in network server of the gateway we managed to connect and end device(APB mode) and send some data to the application.

# Testing on local Chirpstack server.
We've installed chirpstack V4.0 on a Docker container in our pc to test the connectivity.
For that we made a test application and we've successfully linked the gateway's packet forwarder to the neetwork server(IP Address/port),
We've also created a device (OTAA mode) and sent some testing data (even with a script and an actual sensor).

# OTAA vs APB
They are both device activation modes.
-Over-The-Air-Activation (OTAA) - the most secure and recommended activation method for end devices. Devices perform a join procedure with the network, during which a dynamic device address is assigned and security keys are negotiated with the device.
-Activation By Personalization (ABP) - requires hardcoding the device address as well as the security keys in the device. ABP is less secure than OTAA and also has the downside that devices can not switch network providers without manually changing keys in the device.

These are the parameters used in each mode:
-OTAA:
Each device has 64-bit DEV-EUI(public/unique/comes with the manufacturer) and an app-key(private/chosen by user) that must be kept secret. They are both shared to the device and to the server.
-APB:
Each device has 64-bit DEV-EUI and an app-session-key(chosen by user), dev_address(chosen by user) and network-session-key(chosen by user), they are all
shared to the device and to the server manually.
NB: In both modes there is also App-EUI but it is not used by Chirpstack.

For further details about the activation process for both modes you can visit this link:
https://www.thethingsnetwork.org/docs/lorawan/end-device-activation/

# Deployment of Chirpstack 4.0 in the Sup'Com server (VPN)
 
