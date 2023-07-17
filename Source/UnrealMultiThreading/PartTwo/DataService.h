// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataService.generated.h"

DECLARE_DELEGATE(FActionDelegate);

/**
 * 
 */

class AMyHUD;

UCLASS()
class UNREALMULTITHREADING_API UDataService : public UObject
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess))
	int ProducerCount = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess))
	float MinInterval = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings", meta=(AllowPrivateAccess))
	float MaxInterval = 1.f;
	
	TArray<FString> FirstNames;
	TArray<FString> LastNames;

	UPROPERTY()
	TWeakObjectPtr<AMyHUD> HUD;
	
	TQueue<FName> GeneratedNames;

	FActionDelegate NameGenerationDelegate;
	FActionDelegate TransferDelegate;
	
	bool IsInitialized = false;
	FCriticalSection Mutex;

	void GetRandomFirstName(FString& FirstName) const;
	void GetRandomLastName(FString& LastName) const;

public:

	UFUNCTION(BlueprintCallable)
	void Init(AMyHUD* MyHUD);
	UFUNCTION(BlueprintCallable)
	void StartGeneration();

	float GetRandomInterval() const;
	
	UFUNCTION()
	void GenerateNewName();

	UFUNCTION()
	void TransferNamesToHUD();
};
