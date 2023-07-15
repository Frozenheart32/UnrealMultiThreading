// Fill out your copyright notice in the Description page of Project Settings.


#include "AgeGeneration_Runnable.h"

#include "HAL/ThreadManager.h"
#include "PartOne/CubeFactory.h"
#include "PartOne/MyCube.h"


FAgeGeneration_Runnable::FAgeGeneration_Runnable(UCubeFactory* CubeFactory, AMyCube* MyCube)
{
	Factory = CubeFactory;
	Cube = MyCube;
}

FAgeGeneration_Runnable::~FAgeGeneration_Runnable()
{
	Factory = nullptr;
	Cube = nullptr;
}

bool FAgeGeneration_Runnable::Init()
{
	return true;
}

uint32 FAgeGeneration_Runnable::Run()
{
	const auto Age = Factory->GenerateCubeAge();
	Cube->UpdateCubeAge(Age);

	return 1;
}

void FAgeGeneration_Runnable::Stop()
{
	const auto ThreadID = FPlatformTLS::GetCurrentThreadId();
	UE_LOG(LogTemp, Display, TEXT("FAgeGeneration_Runnable::Stop. Thread#%d, ThreadName is %s"),
		ThreadID, *FThreadManager::GetThreadName(ThreadID));
}

void FAgeGeneration_Runnable::Exit()
{
	const auto ThreadID = FPlatformTLS::GetCurrentThreadId();
	UE_LOG(LogTemp, Display, TEXT("FAgeGeneration_Runnable::Exit. Thread#%d, ThreadName is %s"),
		ThreadID, *FThreadManager::GetThreadName(ThreadID));
}
