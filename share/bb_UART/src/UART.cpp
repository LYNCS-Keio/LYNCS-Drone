#include "UART.hpp"

namespace uart
{
    UART::UART(uart_conf& conf_) : conf(conf_), sequence_num(0) {}
    
    template <class T>
    uart_err_t UART::create_pdu(const char &type, const T &data_)
    {
        size_t size = sizeof(T)
        std::unique_ptr<pdu> buf(new pdu);

        (*buf).data.type = type;

        if (conf.ENABLE_ECC == false){
            (*buf).data.data = (char*)&data_;
        } else {
            calc_parity((*buf).data.data, data_, size);
        }
        
        (*buf).data.checksum = std::accumulate((*buf).data.data, 
            (*buf).data.data+(uint8_t)size, 0) / (uint8_t)size;

        (*buf).header.payload_size = (char)size;
        
        lock.lock();
        (*buf).header.seq_num = sequence_num;
        if (sequence_num == 255) {
            sequence_num = 0;
        } else {
            sequence_num++;
        }
        lock.unlock();

        (*buf).header.checksum = ((*buf).header.seq_num + (*buf).header.payload_size) / 2;
           
    }

    template<class T>
    void UART::calc_parity(char* buf, const T &data_, size_t &size)
    {

    }

    uart_err_t UART::get_data()
    {

    }

}
