// Fill out your copyright notice in the Description page of Project Settings.

#include "ZMQComponent.h"

//General Log
DEFINE_LOG_CATEGORY(LogZMQ);


// Sets default values for this component's properties
UZMQComponent::UZMQComponent()	
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	UE_LOG(LogInit, Log, TEXT("ZMQComponent()"));

	
}


UZMQComponent::~UZMQComponent()
{	

}

// Called when the game starts
void UZMQComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UZMQComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	_ShutdownZSockets();	
}

// Called every frame
void UZMQComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
}

bool UZMQComponent::IsZMQIinitialized()
{
	return  m_IsInitialized;
}

//
//bool UZMQComponent::CreateContextZMQ()
//{
//	bool result = true;
//
//	if (m_ZMQContext == nullptr) {
//		m_ZMQContext = zmq_ctx_new();
//		UE_LOG(LogInit, Log, TEXT("UZMQComponent::CreateZMQContext() create ZMQ context"));
//	}
//	else {
//		UE_LOG(LogInit, Error, TEXT("UZMQComponent::CreateZMQContext() create ZMQ context FAILED"));
//		result = false;
//	}
//
//	return result;
//}
//
//int UZMQComponent::DestroyContextZMQ()
//{
//	int result = 0;
//
//	return result;
//}
//
//int UZMQComponent::SetContextZMQ()
//{
//	int result = 0;
//
//	return result;
//}
//
//int UZMQComponent::TermContextZMQ()
//{
//	int result = 0;
//
//	return result;
//}
//
//bool UZMQComponent::ShutDownContextZMQ()
//{
//	bool result = true;
//	if (m_ZMQContext != nullptr) {
//		zmq_ctx_shutdown(m_ZMQContext);
//		UE_LOG(LogInit, Warning, TEXT("UZMQComponent::ShutDownZMQContext() shutdown ZMQ context"));
//	}
//	return result;
//}

bool UZMQComponent::GetSockOpt_IMMEDIATE_ZMQ(const FZSocket _target)
{
	bool result = false;

	if (zsock_immediate(_target.ZSocket) > 0) {
		result = true;
	}

	return result;
}

bool UZMQComponent::SetSockOpt_IMMEDIATE_ZMQ(const FZSocket _target, const bool _immediate)
{
	bool result = true;

	zsock_set_immediate(_target.ZSocket, _immediate);
	//zmq_setsockopt(m_ZMQSocket, ZMQ_IMMEDIATE, &value, 1);

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

FZSocket UZMQComponent::CreateZSocketSubscribe(const FString ip, const int port, FString filter)
{
	FZSocket result;
	
	std::string filterStr(TCHAR_TO_UTF8(*filter));	

	FString host("tcp://");
	host.Append(ip).Append(":").Append(FString::FromInt(port));
	std::string hostStr(TCHAR_TO_UTF8(*host));

	result.ZSocket = zsock_new_sub(hostStr.c_str(), filterStr.c_str());
	
	if (result.ZSocket != NULL) {
		m_IsInitialized = true;
		m_ZSockets.push_back(result);
		UE_LOG(LogTemp, Warning, TEXT("ZMQ create Subscriber"));
	} else {
		m_IsInitialized = false;
		UE_LOG(LogTemp, Warning, TEXT("ZMQ fail to create subscriber"));
	}

	return result;
}

int UZMQComponent::ReceiveZMQ(const FZSocket _target)
{
	int result = 0;

	//UE_LOG(LogTemp, Warning, TEXT("UZMQComponent::ReceiveZMQ(const FZSocket _target)"));
	return result;
}
