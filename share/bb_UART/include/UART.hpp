#pragma once

#include <cstdint>
#include <queue>
#include <memory>
#include <mutex>
#include <numeric>

namespace uart
{
    enum uart_err_t
    {
        UART_SUCCEEDED          = 0,
        UART_ERROR_UNKNOWN      = -1,
        UART_INIT_FAILED        = -2,
        UART_TRANSMIT_FAILED    = -3,
        UART_RECEIVE_FAILED     = -4,
        UART_HASH_NOT_MATCH     = -5,
        UART_BUFFER_OVER        = -6
    };

    struct pdu
    {
        struct header
        {
            uint8_t seq_num;
            uint8_t payload_size;
            uint8_t checksum;
        };
        struct data
        {
            uint8_t type;
            uint8_t* data;
            uint8_t checksum;
        };
    };

    struct uart_conf
    {
        int TX              = -1;   // TX pin
        int RX              = -1;   // RX pin
        int BAUD            = 9600;
        int DATA_BIT_LEN    = 8;    // bits
        int STOP_BIT        = 2;
        int OFFSET          = 0;
        bool ENABLE_RESEND  = true; // 再送
        bool ENABLE_ECC     = false;
    };

    class UART
    {
        private:
        const uart_conf conf;
        uint8_t sequence_num;
        std::queue<uint8_t> transmit_queue;
        std::mutex lock;

        public:
        UART(uart_conf&);
        virtual uart_err_t initialize();
        virtual int thrower(const char*);
        // Generate Protocol Data Unit
        template <class T> uart_err_t create_pdu(const char&, const T&);
        template <class T> void calc_parity(char*, const T&, size_t&);
        virtual int receive();
        uart_err_t get_data();

    };

}

