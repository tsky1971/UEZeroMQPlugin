// Fill out your copyright notice in the Description page of Project Settings.

#include "ZMQComponent.h"

#include "zhelpers.h"

//General Log
DEFINE_LOG_CATEGORY(LogZMQ);


// Sets default values for this component's properties
UZMQComponent::UZMQComponent() :
	m_ZMQContext(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	UE_LOG(LogInit, Log, TEXT("ZMQComponent()"));
}


// Called when the game starts
void UZMQComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


void UZMQComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
}

// Called every frame
void UZMQComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
}

bool UZMQComponent::IsZMQIinitialized()
{
	if (m_ZMQContext != nullptr && m_IsInitialized) {
		return true;
	}

	return false;
}

bool UZMQComponent::CreateContextZMQ()
{
	bool result = true;

	if (m_ZMQContext == nullptr) {
		m_ZMQContext = zmq_ctx_new();
		UE_LOG(LogInit, Log, TEXT("UZMQComponent::CreateZMQContext() create ZMQ context"));
	}
	else {
		UE_LOG(LogInit, Error, TEXT("UZMQComponent::CreateZMQContext() create ZMQ context FAILED"));
		result = false;
	}

	return result;
}

int UZMQComponent::DestroyContextZMQ()
{
	int result = 0;

	return result;
}

int UZMQComponent::SetContextZMQ()
{
	int result = 0;

	return result;
}

int UZMQComponent::TermContextZMQ()
{
	int result = 0;

	return result;
}

bool UZMQComponent::ShutDownContextZMQ()
{
	bool result = true;
	if (m_ZMQContext != nullptr) {
		zmq_ctx_shutdown(m_ZMQContext);
		UE_LOG(LogInit, Warning, TEXT("UZMQComponent::ShutDownZMQContext() shutdown ZMQ context"));
	}
	return result;
}

bool UZMQComponent::GetSockOpt_IMMEDIATE_ZMQ()
{
	bool result = true;

	//zmq_getsockopt(m_ZMQSocket, ZMQ_IMMEDIATE, &result, sizeof(result));

	return result;
}

bool UZMQComponent::SetSockOpt_IMMEDIATE_ZMQ(const bool value)
{
	bool result = true;

	zmq_setsockopt(m_ZMQSocket, ZMQ_IMMEDIATE, &value, 1);

	return result;
}

//bool UZMQComponent::CreateSocketZMQ(const FString ip, EZMQPatternEnum pattern)
//{
//	bool result = true;
//	if (m_ZMQContext != nullptr) {
//		switch (pattern)
//		{
//		case EZMQPatternEnum::UE_ZMQ_SUB:
//			m_ZMQSocket = zmq_socket(m_ZMQContext, ZMQ_SUB);
//			
//			break;
//		default:
//			break;
//		}
//
//		if (m_ZMQSocket) {
//			UE_LOG(LogTemp, Warning, TEXT("ZMQ is created"));
//
//			int result = zmq_connect(m_ZMQSocket, TCHAR_TO_UTF8(*ip));
//			if (result) {
//				zmq_setsockopt(m_ZMQSocket, ZMQ_SUBSCRIBE, "B", 1);
//				m_IsInitialized = true;
//				UE_LOG(LogTemp, Warning, TEXT("ZMQ Context is connected"));
//			}
//			else {
//				m_IsInitialized = false;
//				UE_LOG(LogTemp, Warning, TEXT("ZMQ Context is NOT connected"));
//			}
//		}
//
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("ZMQ Context is NULL"));
//	}
//	return result;
//}

bool UZMQComponent::CreateSUBSocketZMQ(const FString ip, const int port, FString filter)
{
	bool result = true;
	if (m_ZMQContext != nullptr) {
		m_ZMQSocket = zmq_socket(m_ZMQContext, ZMQ_SUB);
		if (m_ZMQSocket != nullptr) {

			std::string cstr(TCHAR_TO_UTF8(*filter));
			zmq_setsockopt(m_ZMQSocket, ZMQ_SUBSCRIBE, cstr.c_str(), cstr.size());
			//zmq_setsockopt(m_ZMQSocket, ZMQ_SUBSCRIBE, "B", 1);

			FString host("tcp://");
			host.Append(ip).Append(":").Append(FString::FromInt(port));

			zmq_connect(m_ZMQSocket, TCHAR_TO_UTF8(*host));
			//zmq_connect(m_ZMQSocket, "tcp://localhost:5563");			
			//zmq_connect(m_ZMQSocket, "tcp://127.0.0.1:5563");
			
			m_SocketPattern = EZMQPatternEnum::UE_ZMQ_SUB;
			m_IsInitialized = true;
		}
		else {
			m_IsInitialized = false;
			UE_LOG(LogTemp, Error, TEXT("ZMQ CreateSUBSocketZMQ FAILED"));
		}
	}
	else {
		m_IsInitialized = false;
		UE_LOG(LogTemp, Warning, TEXT("ZMQ Context is NULL"));
	}
	return result;
}

int UZMQComponent::ReceiveZMQ()
{
	int result = 0;
	int rc;

	zmq_msg_t message;

	if (m_IsInitialized) {
		rc = zmq_msg_init(&message);
		assert(rc == 0);
		
		int size = zmq_msg_recv(&message, m_ZMQSocket, ZMQ_NOBLOCK);
		assert(size >= 0);
		
		char *data = (char *) zmq_msg_data(&message);
		assert(data != 0);

		zmq_msg_close(&message);

		if ((size > 0) && (data != NULL) && (strcmp(data, "skeleton") == 0)) {

			rc = zmq_msg_init(&message);
			assert(rc == 0);

			size = zmq_msg_recv(&message, m_ZMQSocket, ZMQ_NOBLOCK);
			assert(size >= 0);
			
			data = (char *) zmq_msg_data(&message);
			assert(data != 0);			
			if (size > 0) {
				oscpkt::PacketReader pr(data, size);
				oscpkt::Message *msg;

				std::string nameStr;
				//bool tempBool;
				int calibrated = 0;
				float pos[3]; 
				float rot[4];
				float refv[3];
				//int tempInt;
				
				//Frame 0 = /joint/Head i f f f f f f f f f f f f
				//fscan(buf, "%s %i %f %f %f %f %f %f %f %f")
				while ((pr.isOk()) && (msg = pr.popMessage()) != 0) {
					if (msg->match("/joint/Head").popStr(nameStr).popInt32(calibrated).
							popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
							popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
							popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
							isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("Head found"));
					}
					if (msg->match("/joint/Neck").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("Neck found"));
					}
					if (msg->match("/joint/SpineShoulder").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("SpineShoulder found"));
					}
					if (msg->match("/joint/SpineBase").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("SpineBase found"));
					}
					if (msg->match("/joint/ShoulderLeft").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("ShoulderLeft found"));
					}
					if (msg->match("/joint/ShoulderRight").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("ShoulderRight found"));
					}

					
				}

				UE_LOG(LogTemp, Warning, TEXT("[%s]"), ANSI_TO_TCHAR(data));
				//UE_LOG(LogTemp, Warning, TEXT("[%s] %s"), ANSI_TO_TCHAR(address), ANSI_TO_TCHAR(contents));

			}
			rc = zmq_msg_close(&message);
		}
			
	}

	return result;
}
