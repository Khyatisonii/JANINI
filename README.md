# JANINI 
Just A Nested Integrated Novelle Innovation

One can quickly access and efficiently operate electrical appliances (such as fans, led lights, washing machines, etc.) via home automation. Making people's life simple, efficiently managed, and more technologically oriented is the core goal of home automation.
While many home automation systems work well, they are only effective over short distances. For instance, turning on electronic devices like A.C. or T.V one needs to operate its remote within a certain range.

This presents a significant challenge/risk of an electric disaster (such as a fire outbreak) to people who were outside the immediate vicinity of their appliance and who accidentally left their appliances on or off and were unable to switch them off or on in time to avoid risk. This could result in energy waste for appliances that were left connected to the mains for longer than necessary. So, to tackle this problem, it will be necessary to develop a reliable method of remotely managing household appliances from a distance.
As a result, our project J.A.N.A.N.I will use a home automation system that is based on the GSM (Global System for Mobile communication) to address the aforementioned problems.
To remotely turn on and off electrical devices connected to the common node, this system sends commands via SMS. System development entails both programming the system controller and implementing the many hardware modules (such as the GSM module, Arduino, relay modules, LED bulb, Kettle, and other required components) that make up the system.


Our proposed GSM-based home automation system is full of unique features that set it apart from many existing innovations including: 

Password-protected control for all outputs: This will ensure that only authorized users can access it. For password protection, we shall rely on fingerprint and password pins. Thus, any form of misuse could be avoided. A mobile phone with a functioning SIM card is required for the user to apply this security mechanism. For the GSM shield to have the ability to receive and send text messages, another SIM card is also required. Also, another additional feature would be that in case of false password input i.e, during any unauthorized activity, a warning message would be sent to the owner.

Automatic restoration after a power failure: Since power outages can occur unexpectedly for some reason, when power is restored, the proposed home automation circuit will remember which devices were on before a power outage and will switch those items back ON.
The EEPROM on the ATmega328P microcontroller Chip is used to accomplish this. The data on the microcontroller or Arduino won't be lost when the power is cut off because EEPROM is a non-volatile memory.
 
SMS acknowledgment to the user, so that if in our case the user is a carer looking after elderly people or some physically disabled person, whatever the need (like turning on/off the fan, boiling water, etc.) of the disabled person can be fulfilled too without moving away from them.

Displaying current state:Additionally, anything that is being done, such as changes in the state of the devices and the most recent action taken by the user, as well as the current time, will be shown to the user (in this case, the caretaker) too.
In-depth information about any message that is sent or received will be displayed there.

Voice activation command:If the user doesn't want to type the message, an additional feature would also be available as an option in which they can speak their command to the device i.e, voice-automated. The Arduino will then send that message through GSM after using a python library to convert the voice message into the text to complete the task.

Remote access:GSM can be used in locations without internet access, such as in some isolated highland areas and other places because it doesn't require a computer or the internet. Thus users from areas having no or minimal network/internet coverage could also control their devices.

Also, we'll look at automating SMS commands so the user can schedule them to run automatically without their involvement.
A simple GSM-based phone or any smartphone may be used.

In conclusion, our project will be helpful for many of the reasons already mentioned, including helping disabled people, such as dumb or deaf people, who can speak whatever they want the device to do, elderly people who can't move around much, and for people who can't always be close to the appliances (which is natural to happen), helpful in remote hilly areas without internet connections. In general, using this GSM-based Home Automation system will be a better alternative for anyone in everyday life.
