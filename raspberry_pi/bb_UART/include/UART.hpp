#pragma once

#include <cstdint>
#include <queue>
#include <memory>

// 
// packet
// 
// name             : bit 
// header   ACK     : 11xxxxxx (x: sequence_num)
//          data    : 00xxxxxx (x: sequence_num)
//                   
// payload_size     : xxxxxxxx
// 
// hash             : xxxxyyyy (x: header's hash, y: payload's hash)
// 
// payload          : xxxxxxxx
//                  : xxxxxxxx
//                    ~~~~~~~~
//                  : xxxxxxxx 
// 

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

    struct uart_conf
    {
        int TX              = -1;   // TX pin
        int RX              = -1;   // RX pin
        int BAUD            = 9600;
        int DATA_BIT_LEN    = 8;    // bits
        int MAX_PAYLOAD_SIZE= 32;   // ペイロードサイズ(1-255bytes)
        int STOP_BIT        = 2;
        int OFFSET          = 0;
        bool ENABLE_RESEND  = true; // 再送
    };

    class UART
    {
        private:
        const uart_conf conf;
        uint8_t sequence_num;
        std::queue<uint8_t> transmit_queue;

        public:
        UART(uart_conf&);
        virtual uart_err_t initialize();
        // パケット送信
        virtual int thrower(const uint8_t*);
        // パケット作成→キュー追加
        template <class T> uart_err_t transmit(const T&);
        virtual int receive();
        uart_err_t get_data();

    };

}

