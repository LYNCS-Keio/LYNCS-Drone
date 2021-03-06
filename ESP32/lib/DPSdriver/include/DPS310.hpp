#pragma once

#include "DPS.hpp"

namespace dps310
{
	using namespace dps;
	class DPS310 : public DPS
	{
	private:
	uint8_t tmp_over_sampling_rate_;
	uint8_t prs_over_sampling_rate_;
	uint8_t m_tempSensor_;
	/**
	 * \name Calibration coefficients
	 * Coefficients used when calculating compensated Temperature/Pressure
	 * \{
	 */
  	float m_c0Half_;		//temperature coefficient value
  	int32_t m_c1_;			//temperature coefficient value
	int32_t m_c00_;			//pressure coefficient value
	int32_t m_c10_;			//pressure coefficient value
	int32_t m_c01_;			//pressure coefficient value
	int32_t m_c11_;			//pressure coefficient value
	int32_t m_c20_;			//pressure coefficient value
	int32_t m_c21_;			//pressure coefficient value
	int32_t m_c30_;			//pressure coefficient value
	//! \}
	float m_lastTempScal_;	//it will be used for pressure compensation
	float calcTemp(int32_t raw);
	float calcPressure(int32_t raw);
	//implement virtual functions
	dps_err_t flushFIFO() override;
	dps_err_t readcoeffs() override;
	dps_err_t configTemp(uint8_t tempMr, uint8_t tempOsr) override;
	dps_err_t configPressure(uint8_t prsMr, uint8_t prsOsr) override;

	public:
	DPS310(dps_bus_t *bus);
	~DPS310(){};
	void setTmpOversamplingRate(uint8_t over_sampling_rate){tmp_over_sampling_rate_ = over_sampling_rate;}
	void setPrsOversamplingRate(uint8_t over_sampling_rate){prs_over_sampling_rate_ = over_sampling_rate;}
	dps_err_t initiarize();
	};
} // namespace dps
