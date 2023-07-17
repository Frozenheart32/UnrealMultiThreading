// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartTwo/DataService.h"

/**
 * 
 */

class UNREALMULTITHREADING_API FGraphTask_Consumer
{

private:
	
	FActionDelegate TransferDelegate;
	
public:
	FGraphTask_Consumer(FActionDelegate InTransferDelegate) : TransferDelegate(InTransferDelegate)
	{
		
	}

	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FGraphTask_Consumer, STATGROUP_TaskGraphTasks)
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::GameThread;
	}

	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		if(TransferDelegate.IsBound())
		{
			UE_LOG(LogTemp, Display, TEXT("Consumer DoWork"));
			TransferDelegate.Execute();
		}
	}
};
