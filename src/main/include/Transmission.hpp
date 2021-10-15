#pragma once

#include <initializer_list>
#include <string>

#include <frc/Encoder.h>

enum Direction {
	Forward,
	Reverse
};

template <typename Motor_Controller>
class Transmission {
public:

	Transmission(std::initializer_list<std::pair<int, Direction>> motor_info, std::pair<int,int> encPort) : 
			leader( (motor_info.begin())->first ),
			enc( encPort.first, encPort.second ) {
		// Initialize leader motor and create a const variable to store the leader motor's info
		auto const leader_info = *(motor_info.begin());
		leader.SetInverted(leader_info.second);

		// Store follower motors in vector
		followers.reserve(motor_info.size()-1);
		for(auto m_inf = motor_info.begin()+1; m_inf != motor_info.end(); m_inf++)
			followers +=  (new Motor_Controller( m_inf->first) );

		// Invert followers depending on direction and set to follow mode
		for(std::size_t i = 0; i < motor_info.size()-1; i++){
			followers[i]->SetInverted((motor_info.begin()+i+1)->second);
			followers[i]->Set(ControlMode::Follower, leader_info.first);
		}
	}

	// Manual destruction required due to allocation of pointers
	~Transmission(){
		for(Motor_Controller* follower : followers)
			follower->~Motor_Controller();
	}

	Motor_Controller* operator->(){
		return &leader;
	}

	int getEncoderPosition() {
		return enc.Get();
	}

	int getEncoderRate() {
		return enc.GetRate();
	}

private:
	Motor_Controller leader;
	std::basic_string<Motor_Controller*> followers;
	frc::Encoder enc;
};
/*
template<>
class Transmission<rev::CANSparkMax>{
public:

	Transmission(std::initializer_list<std::pair<int, Direction>> motor_info, std::pair<int,int> encPort) : 
			leader( (motor_info.begin())->first, rev::CANSparkMaxLowLevel::MotorType::kBrushless ),
			enc( leader.GetEncoder() ) {

		// Restore Factory Defaults for leader
		leader.RestoreFactoryDefaults();
		leader.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

		// Initialize leader motor and create a const variable to store the leader motor's info
		auto const leader_info = *(motor_info.begin());
		leader.SetInverted(leader_info.second);

		// Store follower motors in vector
		followers.reserve(motor_info.size()-1);
		for(auto m_inf = motor_info.begin()+1; m_inf != motor_info.end(); m_inf++)
			followers +=  (new rev::CANSparkMax( m_inf->first, rev::CANSparkMaxLowLevel::MotorType::kBrushless) );

		// Invert followers depending on direction and set to follow mode
		for(int i = 0; i < motor_info.size()-1; i++){
			followers[i]->RestoreFactoryDefaults();
			followers[i]->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
			followers[i]->Follow(leader, (motor_info.begin()+i+1)->second);
		}
	}

	// Manual destruction required due to allocation of pointers
	~Transmission(){
		for(rev::CANSparkMax* follower : followers)
			follower->~CANSparkMax();
	}

	Transmission* operator->(){
		return this;
	}

	void Set(ControlMode cm, double rate){
		leader.Set(rate);
	}

	int getEncoderPosition() {
		return enc.GetPosition();
	}

	int getEncoderRate() {
		return enc.GetVelocity();
	}

private:
	rev::CANSparkMax leader;
	std::basic_string<rev::CANSparkMax*> followers;
	rev::CANEncoder enc;
}; */