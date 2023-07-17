// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
class UDataService;

UCLASS()
class UNREALMULTITHREADING_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TWeakObjectPtr<UDataService> MyDataService;
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void AddNewNameToHUD(const FName& NewName);

	UFUNCTION(BlueprintCallable)
	void StartButtonPressed();
};
