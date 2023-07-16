// Fill out your copyright notice in the Description page of Project Settings.


#include "StartBuild_Runnable.h"

#include "HAL/ThreadManager.h"
#include "PartOne/MyCube.h"
#include "PartOne/CubeFactory.h"

FStartBuild_Runnable::FStartBuild_Runnable(UCubeFactory* CubeFactory, AMyCube* Cube)
{
	Factory = CubeFactory;
	MyCube = Cube;
}

FStartBuild_Runnable::~FStartBuild_Runnable()
{
	Factory = nullptr;
	MyCube = nullptr;
	RunnableClass_AgeGeneration = nullptr;
	RunnableClass_ColorGeneration = nullptr;
	WorkingThreads.Empty();
}

bool FStartBuild_Runnable::Init()
{
	return true;
}

uint32 FStartBuild_Runnable::Run()
{
	//create threads
	RunnableClass_AgeGeneration = new FAgeGeneration_Runnable{Factory, MyCube};
	RunnableClass_ColorGeneration = new FColorGeneration_Runnable{Factory, MyCube};

	WorkingThreads.Add(FRunnableThread::Create(RunnableClass_AgeGeneration, TEXT("CubeAgeGeneration Thread")));
	WorkingThreads.Add(FRunnableThread::Create(RunnableClass_ColorGeneration, TEXT("CubeColorGeneration Thread")));

	//wait
	for (const auto Thread : WorkingThreads)
	{
		Thread->WaitForCompletion();
	} 

	for (auto WorkingThread : WorkingThreads)
	{
		WorkingThread = nullptr;
	}

	WorkingThreads.Empty();
	
	return 1;
}

void FStartBuild_Runnable::Stop()
{
	const auto ThreadID = FPlatformTLS::GetCurrentThreadId();
	UE_LOG(LogTemp, Display, TEXT("FStartBuild_Runnable::Stop. Thread#%d, ThreadName is %s"),
		ThreadID, *FThreadManager::GetThreadName(ThreadID));
	
	for (auto WorkingThread : WorkingThreads)
	{
		if(WorkingThread)
		{
			WorkingThread->Kill(false);
			WorkingThread = nullptr;
		}
	}

	WorkingThreads.Empty();
}

void FStartBuild_Runnable::Exit()
{
	const auto ThreadID = FPlatformTLS::GetCurrentThreadId();
	UE_LOG(LogTemp, Display, TEXT("FStartBuild_Runnable::Exit. Thread#%d, ThreadName is %s"),
		ThreadID, *FThreadManager::GetThreadName(ThreadID));
}

