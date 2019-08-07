#pragma once

#include "DPS.hpp"

namespace dps
{
	class DPS310 : public DPS
	{
	private:
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
	int c0_; //temperature coefficient value
	int c1_; //temperature coefficient value
	public:
		DPS310(dps_bus_t *bus);
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
		esp_err_t initiarize();
		esp_err_t temperature(float &T_comp);
	};
} // namespace dps