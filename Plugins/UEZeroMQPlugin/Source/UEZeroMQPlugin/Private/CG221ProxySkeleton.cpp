// Fill out your copyright notice in the Description page of Project Settings.

#include "CG221ProxySkeleton.h"


UCG221ProxySkeleton::UCG221ProxySkeleton() :
	UZMQComponent()
{
	CreateSkeletonData();
}

FString UCG221ProxySkeleton::GetSkeletonName()
{
	return ANSI_TO_TCHAR(m_SkeletonName.c_str());
}

void UCG221ProxySkeleton::SetSkeletonId(const int skeletonid)
{
	m_SkeletonId = skeletonid;
}

int UCG221ProxySkeleton::GetSkeletonId()
{
	return m_SkeletonId;
}

FVector UCG221ProxySkeleton::GetPosition()
{
	return m_Position;
}

int UCG221ProxySkeleton::ReceiveZMQ(const FZSocket _target)
{
	int result = Super::ReceiveZMQ(_target);

	if (m_IsInitialized) {
		char *address = zstr_recv_nowait(_target.ZSocket);

		if ((address != NULL) && (strcmp(address, "skeleton") == 0)) {

			//UE_LOG(LogTemp, Warning, TEXT("[%s]"), ANSI_TO_TCHAR(address));

			zmsg_t *zmessage = zmsg_new();
			zmessage = zmsg_recv_nowait(_target.ZSocket);
			if ((zmessage != NULL) && (zmsg_content_size(zmessage) > 0)) {
				zframe_t *fr = zmsg_pop(zmessage);

				oscpkt::PacketReader pr(zframe_data(fr), zframe_size(fr));
				oscpkt::Message *msg;

				std::string nameStr;
				//bool tempBool;
				int calibrated = 0;
				float pos[3];
				float rot[4];
				float refv[3];
				int tempInt;
				FCG221BonePtr bone;

				//Frame 0 = /joint/Head i f f f f f f f f f f f f
				//fscan(buf, "%s %i %f %f %f %f %f %f %f %f")
				while ((pr.isOk()) && (msg = pr.popMessage()) != 0) {
					if (msg->match("/Skeleton").popStr(nameStr).popInt32(tempInt).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton Number=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						m_SkeletonName = nameStr;
						m_SkeletonId = tempInt;
						m_Position.X = pos[0];
						m_Position.Y = pos[1];
						m_Position.Z = pos[2];
						
					} else
					if (msg->match("/joint/Head").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton calibrated=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						bone = GetBone(ECG221SkeletonEnum::JOINT_Head);
						if (bone != NULL) {
							UpdateBoneData(bone, calibrated, refv, pos, rot);
						}

					} else
					if (msg->match("/joint/Neck").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton calibrated=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						bone = GetBone(ECG221SkeletonEnum::JOINT_Neck);
						if (bone != NULL) {
							UpdateBoneData(bone, calibrated, refv, pos, rot);
						}
					} else
					if (msg->match("/joint/SpineShoulder").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton calibrated=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						bone = GetBone(ECG221SkeletonEnum::JOINT_SpineShoulder);
						if (bone != NULL) {
							UpdateBoneData(bone, calibrated, refv, pos, rot);
						}
					} else
					if (msg->match("/joint/SpineBase").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton calibrated=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						bone = GetBone(ECG221SkeletonEnum::JOINT_SpineBase);
						if (bone != NULL) {
							UpdateBoneData(bone, calibrated, refv, pos, rot);
						}
					} else
					if (msg->match("/joint/ShoulderLeft").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton calibrated=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						bone = GetBone(ECG221SkeletonEnum::JOINT_ShoulderLeft);
						if (bone != NULL) {
							UpdateBoneData(bone, calibrated, refv, pos, rot);
						}
					} else
					if (msg->match("/joint/ShoulderRight").popStr(nameStr).popInt32(calibrated).
						popFloat(pos[0]).popFloat(pos[1]).popFloat(pos[2]).
						popFloat(rot[0]).popFloat(rot[1]).popFloat(rot[2]).popFloat(rot[3]).
						popFloat(refv[0]).popFloat(refv[1]).popFloat(refv[2]).
						isOkNoMoreArgs()) {
						UE_LOG(LogTemp, Warning, TEXT("[%s] Skeleton calibrated=%i"), ANSI_TO_TCHAR(nameStr.c_str()), tempInt);
						bone = GetBone(ECG221SkeletonEnum::JOINT_ShoulderRight);
						if (bone != NULL) {
							UpdateBoneData(bone, calibrated, refv, pos, rot);
						}
					}

				}
			}
			zstr_free(&address);
		}

	}

	return result;
}

void UCG221ProxySkeleton::UpdateBoneData(FCG221BonePtr bone, int8 calibrated, float * refv, float * pos, float * rot)
{
	bone->Calibrated = calibrated;
	bone->RefVector.X = refv[0]; bone->RefVector.Y = refv[1]; bone->RefVector.Z = refv[2];
	bone->Pos.X = pos[0]; bone->Pos.Y = pos[1]; bone->Pos.Z = pos[2];
	bone->Rot.X = rot[0]; bone->Rot.Y = rot[1]; bone->Rot.Z = rot[2]; bone->Rot.W = rot[3];

	UE_LOG(LogTemp, Warning, TEXT("Skeleton calibrated=%i Pos=(%f, %f, %f)"), bone->Calibrated, bone->Pos.X, bone->Pos.Y, bone->Pos.Z);
	
}

FCG221BonePtr UCG221ProxySkeleton::CreateNewBone(ECG221SkeletonEnum _b, ECG221SkeletonEnum _parent)
{
	
	FCG221BonePtr bone = new FCG221Bone();

	bone->Calibrated = false;
	bone->Pos = FVector::ZeroVector;
	bone->Rot = FQuat::Identity;
	bone->Index = _b;
	bone->ParentIndex = _parent;

	m_Bones[_b] = bone;

	return bone;
}

//
//void UCG221ProxySkeleton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}
//
//void UCG221ProxySkeleton::BeginPlay()
//{
//	Super::BeginPlay();
//}
//
//void UCG221ProxySkeleton::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	Super::EndPlay(EndPlayReason);
//}

void UCG221ProxySkeleton::CreateSkeletonData()
{
	FCG221BonePtr bone;
	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_SpineShoulder, ECG221SkeletonEnum::JOINT_SpineBase);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_Neck, ECG221SkeletonEnum::JOINT_SpineShoulder);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_Head, ECG221SkeletonEnum::JOINT_Neck);	
		
	// Right Arm

	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_ShoulderRight, ECG221SkeletonEnum::JOINT_Neck);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_ElbowRight, ECG221SkeletonEnum::JOINT_ShoulderRight);
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_WristRight, ECG221SkeletonEnum::JOINT_ElbowRight);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_HandRight, ECG221SkeletonEnum::JOINT_WristRight);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_ThumbRight, ECG221SkeletonEnum::JOINT_HandRight);
	
	// Left Arm

	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_ShoulderLeft, ECG221SkeletonEnum::JOINT_Neck);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_ElbowLeft, ECG221SkeletonEnum::JOINT_ShoulderLeft);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_WristLeft, ECG221SkeletonEnum::JOINT_ElbowLeft);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_HandLeft, ECG221SkeletonEnum::JOINT_WristLeft);
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_ThumbLeft, ECG221SkeletonEnum::JOINT_HandLeft);

	// Right Leg

	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_HipRight, ECG221SkeletonEnum::JOINT_SpineBase);
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_KneeRight, ECG221SkeletonEnum::JOINT_HipRight);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_AnkleRight, ECG221SkeletonEnum::JOINT_KneeRight);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_FootRight, ECG221SkeletonEnum::JOINT_AnkleRight);

	// Left Leg

	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_HipLeft, ECG221SkeletonEnum::JOINT_SpineBase);	
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_KneeLeft, ECG221SkeletonEnum::JOINT_HipLeft);
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_AnkleLeft, ECG221SkeletonEnum::JOINT_KneeLeft);
	bone = CreateNewBone(ECG221SkeletonEnum::JOINT_FootLeft, ECG221SkeletonEnum::JOINT_AnkleLeft);
	
}
