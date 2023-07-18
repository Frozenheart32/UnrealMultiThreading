// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	DataService = CreateDefaultSubobject<UDataService>(TEXT("DataService"));
}

UDataService* UMyGameInstance::GetDataService() const
{
	return DataService;
}
