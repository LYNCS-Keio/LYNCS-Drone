#pragma once
namespace lyncs
{
class PIDController
{
  private:
	double kProportionGain_;
	double kIntegralGain_;
	double kDifferentialGain_;
	double integral_;
	double prev_error_;
	double manipulative_variable_;
	PIDController();

  public:
	PIDController(const double kProportionGain, const double kIntegralGain, const double kDifferentialGain);
	~PIDController();
	void InputPID(double data, double goal, double dt);
	const double GetPID() const;
	[[deprecated("Propotion gain must not be changed.")]] void SetPropotionGain(double propotion_gain) {
		kProportionGain_ = propotion_gain;
	}
	[[deprecated("Integral gain must not be changed.")]] void SetIntegralGain(double integral_gain)
	{
		kIntegralGain_ = integral_gain;
	}
	[[deprecated("Differential gain must not be changed.")]] void SetDifferentialGain(double differential_gain) {
		kDifferentialGain_ = differential_gain;
	}
};

} // namespace lyncs
