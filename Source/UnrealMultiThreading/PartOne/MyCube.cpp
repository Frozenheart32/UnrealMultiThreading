// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCube.h"


// Sets default values
AMyCube::AMyCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AMyCube::UpdateCubeAge(int32 NewAge)
{
	Age = NewAge;
}

void AMyCube::UpdateCubeMaterial(UMaterialInterface* NewMaterial)
{
	CubeMaterial = NewMaterial;
}

