#include "UART.hpp"

namespace uart
{
    UART::UART(uart_conf& conf_) : conf(conf_), sequence_num(0) {}
    
    template <class T>
    uart_err_t UART::transmit(const T &buf_)
    {
        if (transmit_queue.size() + (int)sizeof(T) > 1024) {
            return(UART_BUFFER_OVER);

        } else {
            std::unique_ptr<uint8_t> buf(new T(1));
            buf = (uint8_t*)&buf_;

            // キュー追加、dataサイズがペイロード最大サイズを超える場合は分割
            int j = 0;
            for (int i=0; i<(float)sizeof(T)/conf.MAX_PAYLOAD_SIZE; i++) {
                const uint8_t header = sequence_num & 0b00111111;
                transmit_queue.push(header);
                if (sequence_num == 63) {
                    sequence_num = 0;
                } else {
                    sequence_num++;
                }
                for (j; j<conf.MAX_PAYLOAD_SIZE*(i+1); j++){
                    if (j < (int)sizeof(T)){
                        transmit_queue.push(*buf[j]);
                    } else {
                        break;
                    }

                }

            }

        }

    }

    uart_err_t UART::get_data()
    {

    }

}
