// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorGeneration_Runnable.h"

#include "HAL/ThreadManager.h"
#include "PartOne/CubeFactory.h"

FColorGeneration_Runnable::FColorGeneration_Runnable(UCubeFactory* CubeFactory, AMyCube* MyCube)
{
	Factory = CubeFactory;
	Cube = MyCube;
}

FColorGeneration_Runnable::~FColorGeneration_Runnable()
{
	Factory = nullptr;
	Cube = nullptr;
}

bool FColorGeneration_Runnable::Init()
{
	return true;
}

uint32 FColorGeneration_Runnable::Run()
{
	const auto CreatedMaterial = Factory->GenerateCubeMaterial();
	Cube->UpdateCubeMaterial(CreatedMaterial);
	
	return 1;
}

void FColorGeneration_Runnable::Stop()
{
	const auto ThreadID = FPlatformTLS::GetCurrentThreadId();
	UE_LOG(LogTemp, Display, TEXT("FColorGeneration_Runnable::Stop. Thread#%d, ThreadName is %s"),
		ThreadID, *FThreadManager::GetThreadName(ThreadID));
}

void FColorGeneration_Runnable::Exit()
{
	const auto ThreadID = FPlatformTLS::GetCurrentThreadId();
	UE_LOG(LogTemp, Display, TEXT("FColorGeneration_Runnable::Exit. Thread#%d, ThreadName is %s"),
		ThreadID, *FThreadManager::GetThreadName(ThreadID));
}
