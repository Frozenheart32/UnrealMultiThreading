// Fill out your copyright notice in the Description page of Project Settings.


#include "DataService.h"

#include <random>

#include "MyHUD.h"
#include "MyGraphTasks/GraphTask_Consumer.h"
#include "MyGraphTasks/GraphTask_Producer.h"

void UDataService::Init(AMyHUD* MyHUD)
{
	if(IsInitialized) return;
	
	if(MyHUD)
	{
		HUD = MyHUD;
	}

	NameGenerationDelegate.BindUFunction(this, "GenerateNewName");
	TransferDelegate.BindUFunction(this, "TransferNamesToHUD");

	FirstNames.Add("Alex");
	FirstNames.Add("Dima");
	FirstNames.Add("Lisa");

	LastNames.Add("Bolduin");
	LastNames.Add("Warlock");
	LastNames.Add("Sheppard");

	
	IsInitialized = true;
}

void UDataService::StartGeneration()
{
	FGraphEventArray ProducerTasks;
	for (int i = 0; i < ProducerCount; i++)
	{
		auto ProducerTask = TGraphTask<FGraphTask_Producer>::CreateTask(nullptr, ENamedThreads::GameThread)
			.ConstructAndDispatchWhenReady(NameGenerationDelegate, GetRandomInterval());
		ProducerTasks.Add(ProducerTask);
	}
	
	
	TGraphTask<FGraphTask_Consumer>::CreateTask(&ProducerTasks, ENamedThreads::AnyThread)
		.ConstructAndDispatchWhenReady(TransferDelegate);
}

float UDataService::GetRandomInterval() const
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(MinInterval, MaxInterval);
	
	return dist(e2);
}

void UDataService::GenerateNewName()
{
	FScopeLock ScopeLock{&Mutex};
	
	FString FirstName;
	GetRandomFirstName(FirstName);
	FString LastName;
	GetRandomLastName(LastName);

	FirstName.Append(" ");
	FirstName.Append(LastName);
	GeneratedNames.Enqueue(FName{FirstName});
}

void UDataService::TransferNamesToHUD()
{
	FScopeLock ScopeLock{&Mutex};

	while (!GeneratedNames.IsEmpty())
	{
		FName NewName;
		GeneratedNames.Dequeue(NewName);
		HUD->AddNewNameToHUD(NewName);
	}
}

void UDataService::GetRandomFirstName(FString& FirstName) const
{
	int Size = FirstNames.Num();
	if(Size == 0) return;
	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, Size - 1);

	FirstName = FirstNames[dist6(rng)];
}

void UDataService::GetRandomLastName(FString& LastName) const
{
	int Size = LastNames.Num();
	if(Size == 0) return;
	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, Size - 1);

	LastName = LastNames[dist6(rng)];
}
