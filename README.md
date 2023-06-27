# Conflict Resolution Protocol for Network Congestion using Discrete Event Simulation

## Group Members:
- Fernando Alvarado
- Ivan Ponzio
- Armando Carral

## Description
This repository contains the implementation of a conflict resolution protocol for network congestion using discrete event simulation in Omnet++.

The project focuses on developing a congestion control algorithm based on TCP Reno to prevent data loss caused by buffer saturation in the network. The algorithm incorporates a congestion window variable and a dynamically adjusted threshold based on the network load. Bidirectional communication between nodes is established to control data flow and reduce transmission rates during congestion at the receiver.

The main objective of this project is to investigate the effectiveness of these protocols in improving network performance by reducing congestion and preventing data loss. Simulations are conducted to evaluate the performance of the implemented algorithm.

## Results
Data on network congestion, data loss, and flow performance was collected through simulations. The results demonstrate a significant improvement in congestion reduction and data loss prevention with the implemented conflict resolution protocol.

## References
Tanenbaum, A. S., & Wetherall, D. J. (2011). Computer Networks (5th ed.). Pearson Education.
