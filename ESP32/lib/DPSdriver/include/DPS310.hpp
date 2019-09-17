#pragma once

#include "DPS.hpp"

namespace dps310
{
	using namespace dps;
	class DPS310 : public DPS
	{
	private:
	esp_err_t flushFIFO();
	esp_err_t readcoeffs();
	uint8_t tmp_over_sampling_rate_;
	uint8_t prs_over_sampling_rate_;
	uint8_t m_tempSensor_;
  //compensation coefficients
  	float m_c0Half_;		//temperature coefficient value
  	int32_t m_c1_;			//temperature coefficient value
	int32_t m_c00_;			//pressure coefficient value
	int32_t m_c10_;			//pressure coefficient value
	int32_t m_c01_;			//pressure coefficient value
	int32_t m_c11_;			//pressure coefficient value
	int32_t m_c20_;			//pressure coefficient value
	int32_t m_c21_;			//pressure coefficient value
	int32_t m_c30_;			//pressure coefficient value
	float m_lastTempScal_;	//it will be used for pressure compensation
	float calcTemp(int32_t raw);
	float calcPressure(int32_t raw);
	protected:
	public:
		DPS310(dps_bus_t *bus, int cs_pin_num);
		~DPS310(){};
		void setTmpOversamplingRate(uint8_t over_sampling_rate){tmp_over_sampling_rate_ = over_sampling_rate;}
		void setPrsOversamplingRate(uint8_t over_sampling_rate){prs_over_sampling_rate_ = over_sampling_rate;}
	};
} // namespace dps
