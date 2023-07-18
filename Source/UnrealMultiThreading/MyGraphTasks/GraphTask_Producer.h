// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartTwo/DataService.h"

/**
 * 
 */



class UNREALMULTITHREADING_API FGraphTask_Producer
{

private:
	
	FActionDelegate NameGenerationDelegate;
	float SleepInterval;

public:
	
	FGraphTask_Producer(FActionDelegate InNameGenerationDelegate, float InSleepInterval)
		: NameGenerationDelegate(InNameGenerationDelegate), SleepInterval(InSleepInterval)
	{
		
	}

	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FGraphTask_Producer, STATGROUP_TaskGraphTasks)
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyBackgroundThreadNormalTask;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		FPlatformProcess::Sleep(SleepInterval);
		
		if(NameGenerationDelegate.IsBound())
		{
			UE_LOG(LogTemp, Display, TEXT("Producer DoWork"));
			NameGenerationDelegate.Execute();
		}
	}
};
