#include "DareDashboard.h"
#include <iostream>
#include "../RobotMap.h"

DareDashboard::DareDashboard() : Subsystem("DaredevilDashboard") {
	frames["driverstation"] = new DriverstationFrame("driverstation")
	frames["match"] = new MatchFrame("match");
	SocketClient::SetConnection("127.0.0.1",5055);
	//connection->Connect();
}

void DareDashboard::InitDefaultCommand() {

}


void DareDashboard::Update() {
	/*
	 * TODO Data Change Broadcasting
	 *
	 * We're going to use a "frame" system. All frames extend on top of a base frame class.
	 * For every object that exists in the dashboard logger, there will be a frame.
	 * You initialize all its values AFTER constructing it, and all objects will coincidentally
	 *   be flagged as "dirty".
	 * Then, frame#update() will be called on all frames, passing in the connection.
	 * The frame will then broadcast any dirty values to the server, not updating unchanged ones.
	 *
	 * This reduces our packet spam by quite a bit and will take unneccasary load off of the nodejs server
	 *
	 */

	// Talon Frames
	for( auto const& kvs : frames){
		kvs.second->Update();
		if(IsConnected()){
			kvs.second->Broadcast();
		}else{
			kvs.second->MarkAllDirty();
		}
	}


}

bool DareDashboard::IsConnected(){
	return SocketClient::IsConnected();
}

void DareDashboard::RegisterTalonSRX(std::string path, WPI_TalonSRX* talon){
	frames[path] = new TalonSRXFrame(path, talon);
}

void DareDashboard::RegisterLimitSwitch(std::string path, frc::DigitalInput* limitSwitch){
	frames[path] = new LimitSwitchFrame(path, limitSwitch);
}

//void RegisterUltrasonics(std::string path, UltrasonicSubsystem ultrasonicSubsystem);

//Reminder to associate path with talon
void DareDashboard::RegisterEncoder(std::string path, frc::Encoder* encoder, int aChannel, int bChannel){
	frames[path] = new EncoderFrame(path, encoder, aChannel, bChannel);

}

void DareDashboard::RegisterDoubleSolenoid(std::string path, frc::DoubleSolenoid* doubleSolenoid, int forwardChannel, int reverseChannel){
	frames[path] = new DoubleSolenoidFrame(path,doubleSolenoid,forwardChannel,reverseChannel);
}
