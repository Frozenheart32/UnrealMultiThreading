// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeFactory.h"

#include <random>

#include "Kismet/GameplayStatics.h"
#include "MyThreads/StartBuild_Runnable.h"

UCubeFactory::UCubeFactory()
{
	
}

AActor* UCubeFactory::Create(TSubclassOf<AMyCube> CubeType, FVector Position, FRotator Rotation)
{
	const FTransform CubeTransform{Rotation, Position, FVector{1}};
	const auto NewCube = GetWorld()->SpawnActorDeferred<AMyCube>(CubeType, CubeTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	RunnableClass_StartBuild = new FStartBuild_Runnable{this, NewCube};
	CurrentRunningThread_StartBuild = FRunnableThread::Create(RunnableClass_StartBuild, TEXT("StartCubeBuild Thread"), 0, TPri_Normal);
	
	CurrentRunningThread_StartBuild->WaitForCompletion();
	
	UGameplayStatics::FinishSpawningActor(NewCube, CubeTransform);

	RunnableClass_StartBuild = nullptr;
	CurrentRunningThread_StartBuild = nullptr;
	
	return NewCube;
}

void UCubeFactory::StopBuildThread()
{
	if(CurrentRunningThread_StartBuild)
		CurrentRunningThread_StartBuild->Kill();
	
	RunnableClass_StartBuild = nullptr;
	CurrentRunningThread_StartBuild = nullptr;
}

int32 UCubeFactory::GenerateCubeAge() const
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(MinAge, MaxAge);

	return dist6(rng);
}

UMaterialInterface* UCubeFactory::GenerateCubeMaterial() const
{
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MaterialTemplate, nullptr);
	
	const FLinearColor Color{GetRandomColorChanelValue(), GetRandomColorChanelValue(), GetRandomColorChanelValue(), 1.f};
	DynMaterial->SetVectorParameterValue(ColorParameterName, Color);
	return DynMaterial;
}

float UCubeFactory::GetRandomColorChanelValue() const
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 1);
	
	return dist(e2);
}


