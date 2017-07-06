// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// @third party code - BEGIN
#include "AllowWindowsPlatformTypes.h"
#include "oscpkt.hh"
#include "zmq.h"
#include "czmq.h"
#include "HideWindowsPlatformTypes.h"
// @third party code - END

#include "Core.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "ZMQComponent.generated.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(LogZMQ, Log, All);


UENUM(BlueprintType)
enum class EZMQPatternEnum : uint8
{
	UE_ZMQ_PUSH		UMETA(DisplayName = "PUSH"),
	UE_ZMQ_PULL		UMETA(DisplayName = "PULL"),
	UE_ZMQ_PUB		UMETA(DisplayName = "PUB"),
	UE_ZMQ_SUB		UMETA(DisplayName = "SUB"),
	UE_ZMQ_CLIENT	UMETA(DisplayName = "CLIENT"),
	UE_ZMQ_SERVER	UMETA(DisplayName = "SERVER")
};


USTRUCT(BlueprintType, Blueprintable)
struct FZSocket
{
	GENERATED_USTRUCT_BODY()

	zsock_t *ZSocket;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEZEROMQPLUGIN_API UZMQComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZMQComponent();
	virtual ~UZMQComponent();

	void _ShutdownZSockets()
	{
		if (m_ZSockets.size() > 0) {
			for (auto iter = m_ZSockets.begin(); iter != m_ZSockets.end(); ++iter) {
				zsock_destroy(&(*iter).ZSocket);
			}
			m_ZSockets.clear();
		}
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BluePrintCallable, Category = ZMQ)
	bool IsZMQIinitialized();

	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	bool CreateContextZMQ();
	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	int DestroyContextZMQ();
	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	int SetContextZMQ();
	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	int TermContextZMQ();
	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	bool ShutDownContextZMQ();


	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool GetSockOpt_IMMEDIATE_ZMQ(const FZSocket _target);
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool SetSockOpt_IMMEDIATE_ZMQ(const FZSocket _target, const bool _immediate);

	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	bool CreateSocketZMQ(const FString ip, EZMQPatternEnum pattern);

	UFUNCTION(BluePrintCallable, Category = ZMQ)
		FZSocket CreateZSocketSubscribe(const FString ip, const int port, FString filter);
	
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		virtual int ReceiveZMQ(const FZSocket _target);

protected:

	bool m_IsInitialized;

	std::vector<FZSocket> m_ZSockets;

	/*zsock_t *m_ZMQSubscriber;
	zsock_t *m_ZMQPublisher;

	zsock_t *m_ZMQPush;
	zsock_t *m_ZMQPull;*/
};
