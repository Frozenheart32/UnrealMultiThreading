// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCube.generated.h"

UCLASS(Blueprintable)
class UNREALMULTITHREADING_API AMyCube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyCube();

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	int32 Age;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UMaterialInterface* CubeMaterial = nullptr;

public:
	
	void UpdateCubeAge(int32 NewAge);
	void UpdateCubeMaterial(UMaterialInterface* NewMaterial);
};
