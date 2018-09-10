/*
 * utilities.h
 *
 *  Created on: Jul 12, 2018
 *      Author: Colton
 */

#ifndef RF24_UTILITIES_H_
#define RF24_UTILITIES_H_


#define discover_packet_size	32
#define provision_packet_size   10
#define node_info_packet_size   14
#define node_data_packet_size   18
#define gateway_ack_packet_size 6
#define minimalist_packet_size	30


enum packet_types
{
	discover_packet_type = 1,
	provision_packet_type = 2,
	node_info_packet_type = 3,
	node_data_packet_type = 4,
	gateway_ack_packet_type = 5,
	minimalist_packet_type = 6
};

struct minimalist_packet
{
	uint8_t packet_type;
	uint8_t VBUS_available;
	uint8_t bmp280_available;
	uint8_t si7020_available;
	uint8_t hardware_revision[2];
	uint32_t unique_id_0;
	uint32_t unique_id_1;
	uint32_t BMP280_pres;
	int32_t BMP280_temp;
	uint32_t Si7020_humid;
	int32_t Si7020_temp;
};

struct discover_packet
{
	uint8_t packet_type;
	char message[31];
};

struct provision_packet
{
	uint8_t packet_type;
	uint8_t node_id;
	uint32_t address;
	uint32_t mswait;
};

struct node_info_packet
{
	uint8_t packet_type;
	uint8_t VBUS_available;
	uint8_t bmp280_available;
	uint8_t si7020_available;
	uint8_t hardware_revision[2];
	uint32_t unique_id_0;
	uint32_t unique_id_1;
};

struct node_data_packet
{
	uint8_t packet_type;
	uint8_t node_id;
	uint32_t BMP280_pres;
	int32_t BMP280_temp;
	uint32_t Si7020_humid;
	int32_t Si7020_temp;
};

struct gateway_ack_packet
{
	uint8_t packet_type;
	uint8_t node_id;
	uint32_t msWait;
};

void prepareRF24(void);
void prepare_uart(void);
void prepareClocks(void);
void prepareRF24(void);
void prepareClocks(void);
void prepareGPIO(void);
void delayMicroseconds(uint32_t);
uint8_t min(uint8_t, uint8_t );
uint32_t millis(void);
void SysTick_Handler(void);
void delay(uint32_t );
void send_string(char * );
void print(const char* , ...);
void println(const char* , ...);
void print(unsigned long int );
void println(unsigned long int );
uint8_t uart_rx(void);
bool uart_available(void);
uint8_t hex_to_decimal(uint8_t);
void prepare_sleep(void);
void prepare_wakeup(void);
bool transmit_packet(void*, uint8_t);
bool receive_packet(void*, uint8_t);
void reconfigure_radio(provision_packet* );
#endif /* RF24_UTILITIES_H_ */
