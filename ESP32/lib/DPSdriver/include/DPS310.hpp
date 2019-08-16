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
	bool tmp_ext_flag_;// used for TMP_EXT configuration. 0 - Internal sensor (in ASIC), 1 - External sensor (in pressure sensor MEMS element).
	unsigned int tmp_over_sampling_rate_;
	int tmp_scale_factor_;
	/*temperature measurement rate
		000 - 1 measurement pr. sec.
		001 - 2 measurements pr. sec.
		010 - 4 measurements pr. sec.
		011 - 8 measurements pr. sec.
		100 - 16 measurements pr. sec.
		101 - 32 measurements pr. sec.
		110 - 64 measurements pr. sec.
		111 - 128 measurements pr. sec..
	 */
	uint8_t tmp_rate_;
	uint8_t measure_tontrol_;
	uint8_t m_tempSensor_;
  //compensation coefficients
  	int32_t m_c0Half_;		//temperature coefficient value
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
		void setTmpExt(bool flag){tmp_ext_flag_ = flag;}
		/*temperature measurement rate
		000 - 1 measurement pr. sec.
		001 - 2 measurements pr. sec.
		010 - 4 measurements pr. sec.
		011 - 8 measurements pr. sec.
		100 - 16 measurements pr. sec.
		101 - 32 measurements pr. sec.
		110 - 64 measurements pr. sec.
		111 - 128 measurements pr. sec..
		*/
		void setTmpRate(bool rate){tmp_rate_ = rate;}
		void setTmpOversamplingRate(int over_sampling_rate){tmp_over_sampling_rate_ = over_sampling_rate;}
		void setMeasCtrl(uint8_t measure_tontrol){measure_tontrol_ =measure_tontrol;}
		void initiarize();
		esp_err_t temperature(float &T_comp);
	};
} // namespace dps
