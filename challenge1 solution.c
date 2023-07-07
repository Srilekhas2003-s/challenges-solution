Data Packet Corruption Detection

-> In a Wireless communciation device, multiple data packets are transferred over the air.
-> It is possible that data might get corrupted or lost before it reaches the destination.
-> Create a method to identify if a data packet is corrupted
  Assume below format for the data packet
#define MAX_PACKET_DATA_LENGTH (50)
typedef struct data_packet_t{
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
   }data_packet_t;
------------------------------------------------------------------------------------------------------------------------------------------

 C CODE


#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

// CRC calculation function using CRC-16 (CCITT polynomial)
uint16_t calculate_crc(const data_packet_t* packet) {
    uint16_t crc = 0xFFFF;  // Initialize with 0xFFFF

    crc ^= packet->id;
    crc ^= packet->data_length;

    for (int i = 0; i < packet->data_length; i++) {
        crc ^= packet->data[i] << 8;

        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;  // XOR with CRC-16 polynomial (0x1021)
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

// Function to check if a packet is corrupted
int is_packet_corrupted(const data_packet_t* packet) {
    uint16_t calculated_crc = calculate_crc(packet);

    // Compare calculated CRC with the packet's CRC
    return calculated_crc != packet->crc;
}

int main() {
    data_packet_t packet;

    // Set packet data
    packet.id = 1;
    packet.data_length = 10;
    for (int i = 0; i < packet.data_length; i++) {
        packet.data[i] = i;
    }
    packet.crc = calculate_crc(&packet);

    // Check if the packet is corrupted
    if (is_packet_corrupted(&packet)) {
        // Packet is corrupted
        // Handle the corruption error
    } else {
        // Packet is valid
        // Process the packet
    }

    return 0;
}
