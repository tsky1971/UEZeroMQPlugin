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
struct FZMQBone
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	bool JointTracked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	int32 JointState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	int32 BoneIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	int32 Joint0Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	FVector Joint0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	int32 Joint1Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ZMQSkeleton)
	FVector Joint1;
};

USTRUCT(BlueprintType, Blueprintable)
struct FZMQSkeleton
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ZMQSkeleton)
	int32 SkeletonId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ZMQSkeleton)
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ZMQSkeleton)
	TArray<FZMQBone> Bones;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEZEROMQPLUGIN_API UZMQComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZMQComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BluePrintCallable, Category = ZMQ)
	bool IsZMQIinitialized();

	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool CreateContextZMQ();
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		int DestroyContextZMQ();
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		int SetContextZMQ();
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		int TermContextZMQ();
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool ShutDownContextZMQ();


	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool GetSockOpt_IMMEDIATE_ZMQ();
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool SetSockOpt_IMMEDIATE_ZMQ(const bool value);

	//UFUNCTION(BluePrintCallable, Category = ZMQ)
	//	bool CreateSocketZMQ(const FString ip, EZMQPatternEnum pattern);

	UFUNCTION(BluePrintCallable, Category = ZMQ)
		bool CreateSUBSocketZMQ(const FString ip, const int port, FString filter);
	
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		int ReceiveZMQ();

private:

	EZMQPatternEnum m_SocketPattern;

	void *m_ZMQContext;
	void *m_ZMQSocket;
	bool m_IsInitialized;

};
