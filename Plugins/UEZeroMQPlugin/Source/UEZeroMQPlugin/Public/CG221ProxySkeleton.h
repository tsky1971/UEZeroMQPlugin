// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZMQComponent.h"

#include "CoreMinimal.h"
#include "Animation/Skeleton.h"

#include <map>
#include <vector>

#include "CG221ProxySkeleton.generated.h"

UENUM(BlueprintType)
enum class ENUISkeletonEnum : uint8 // from _NUI_SKELETON_POSITION_INDEX https://msdn.microsoft.com/en-us/library/nuisensor.nui_skeleton_position_index.aspx
{	
	SKELETON_HIP_CENTER = 0,
	SKELETON_SPINE,
	SKELETON_SHOULDER_CENTER,
	SKELETON_HEAD,
	SKELETON_SHOULDER_LEFT,
	SKELETON_ELBOW_LEFT,
	SKELETON_WRIST_LEFT,
	SKELETON_HAND_LEFT,
	SKELETON_SHOULDER_RIGHT,
	SKELETON_ELBOW_RIGHT,
	SKELETON_WRIST_RIGHT,
	SKELETON_HAND_RIGHT,
	SKELETON_HIP_LEFT,
	SKELETON_KNEE_LEFT,
	SKELETON_ANKLE_LEFT,
	SKELETON_FOOT_LEFT,
	SKELETON_HIP_RIGHT,
	SKELETON_KNEE_RIGHT,
	SKELETON_ANKLE_RIGHT,
	SKELETON_FOOT_RIGHT,
	SKELETON_COUNT,
	SKELETON_UNKNOWN = 255,
};

//https://msdn.microsoft.com/en-us/library/windowspreview.kinect.jointtype.aspx?cs-save-lang=1&cs-lang=cpp#code-snippet-1

enum ECG221SkeletonEnum
{
	JOINT_Head = 3,
	JOINT_Neck = 2,
	JOINT_SpineShoulder = 29,
	JOINT_SpineBase = 0,
	JOINT_ShoulderLeft = 4,
	JOINT_ShoulderRight = 8,
	JOINT_ElbowLeft = 5,
	JOINT_WristLeft = 6,
	JOINT_HandLeft = 7,
	JOINT_ThumbLeft = 22,
	JOINT_HandRight = 11,
	JOINT_ThumbRight = 24,
	JOINT_HandTipLeft = 21,
	JOINT_HandTipRight = 23,
	JOINT_WristRight = 10,
	JOINT_ElbowRight = 9,
	JOINT_HipLeft = 12,
	JOINT_HipRight = 16,
	JOINT_KneeLeft = 13,
	JOINT_KneeRight = 17,
	JOINT_AnkleLeft = 14,
	JOINT_AnkleRight = 18,
	JOINT_FootLeft = 15,
	JOINT_FootRight = 19,
	JOINT_MAX = 25
};

struct FCG221Bone
{
	int8 Calibrated;	
	ECG221SkeletonEnum Index;	
	ECG221SkeletonEnum ParentIndex;
	FVector RefVector;
	FVector Pos;
	FQuat Rot;
};

typedef FCG221Bone* FCG221BonePtr;
typedef std::map<ECG221SkeletonEnum, FCG221BonePtr> tBoneContainer;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEZEROMQPLUGIN_API UCG221ProxySkeleton : public UZMQComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UCG221ProxySkeleton();

	UFUNCTION(BluePrintCallable, Category = ZMQ)
		virtual FString GetSkeletonName();

	UFUNCTION(BluePrintCallable, Category = ZMQ)		
		virtual void SetSkeletonId(const int skeletonid);
	
	UFUNCTION(BluePrintCallable, Category = ZMQ)
		virtual int GetSkeletonId();

	UFUNCTION(BluePrintCallable, Category = ZMQ)
		virtual FVector GetPosition();

	UFUNCTION(BluePrintCallable, Category = ZMQ)
		virtual int ReceiveZMQ(const FZSocket _target) override;

	void UpdateBoneData(FCG221BonePtr bone, int8 calibrated, float * refv, float * pos, float * rot);

	FCG221BonePtr CreateNewBone(ECG221SkeletonEnum _b, ECG221SkeletonEnum _parent);
	

	inline FCG221BonePtr GetBone(ECG221SkeletonEnum _b)
	{
		return m_Bones[_b];
	}


protected:
	//virtual void BeginPlay() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void CreateSkeletonData();




protected:
	std::string m_SkeletonName;
	int32 m_SkeletonId;
	FVector m_Position;
	tBoneContainer m_Bones;

};
