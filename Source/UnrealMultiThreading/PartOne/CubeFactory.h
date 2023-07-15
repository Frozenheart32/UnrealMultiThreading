// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCube.h"
#include "UObject/Object.h"
#include "CubeFactory.generated.h"

/**
 * 
 */

class FStartBuild_Runnable;

UCLASS(BlueprintType)
class UNREALMULTITHREADING_API UCubeFactory : public UObject
{
	GENERATED_BODY()

public:

	UCubeFactory();

private:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Cube factory settings", meta=(AllowPrivateAccess, ExposeOnSpawn))
	UMaterialInterface* MaterialTemplate = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Cube factory settings", meta=(AllowPrivateAccess, ExposeOnSpawn))
	FName ColorParameterName;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Cube factory settings", meta=(AllowPrivateAccess, ExposeOnSpawn))
	int32 MinAge;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Cube factory settings", meta=(AllowPrivateAccess, ExposeOnSpawn))
	int32 MaxAge;


	FStartBuild_Runnable* RunnableClass_StartBuild = nullptr;
	FRunnableThread* CurrentRunningThread_StartBuild = nullptr;
	

public:

	UFUNCTION(BlueprintCallable)
	AActor* Create(TSubclassOf<AMyCube> CubeType, FVector Position, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	void StopBuildThread();
	
	int32 GenerateCubeAge() const;
	UMaterialInterface* GenerateCubeMaterial() const;

private:

	float GetRandomColorChanelValue() const;
};
