// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "PartOne/MyCube.h"

/**
 * 
 */
class UCubeFactory;
class AMyCube;

class UNREALMULTITHREADING_API FColorGeneration_Runnable : public FRunnable
{
 
public:
	
    FColorGeneration_Runnable(UCubeFactory* CubeFactory, AMyCube* MyCube);
	virtual ~FColorGeneration_Runnable() override;

private:

	UCubeFactory* Factory = nullptr;
	AMyCube* Cube = nullptr;

public:

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};
