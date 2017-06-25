// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/GameStateBase.h"

// @third party code - BEGIN
#include "AllowWindowsPlatformTypes.h"
#include "oscpkt.hh"
#include "zmq.h"
#include "czmq.h"
#include "zmq.hpp"
#include "zmsg.hpp"
#include "HideWindowsPlatformTypes.h"
// @third party code - END

#include "GameStateBaseZMQ.generated.h"
/**
 * 
 */
UCLASS()
class UEZEROMQPLUGIN_API AGameStateBaseZMQ : public AGameStateBase
{
	GENERATED_BODY()

public:
	AGameStateBaseZMQ();
	virtual ~AGameStateBaseZMQ();

private:
	
};
