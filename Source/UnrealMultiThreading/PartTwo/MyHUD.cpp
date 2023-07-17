// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "MyGameInstance.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	const auto GI = GetGameInstance();
	if(const auto MyGI = Cast<UMyGameInstance>(GI))
	{
		const auto DataService = MyGI->GetDataService();
		if(DataService)
		{
			DataService->Init(this);
			MyDataService = DataService;
		}
	}
}

void AMyHUD::StartButtonPressed()
{
	if(MyDataService.IsValid())
		MyDataService->StartGeneration();
}
