// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataService.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMULTITHREADING_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UDataService* DataService = nullptr;

public:
	
	UMyGameInstance();

	UFUNCTION(BlueprintCallable)
	UDataService* GetDataService() const;
};
