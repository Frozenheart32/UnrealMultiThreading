// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgeGeneration_Runnable.h"
#include "ColorGeneration_Runnable.h"

/**
 * 
 */

class AMyCube;
class UCubeFactory;

class UNREALMULTITHREADING_API FStartBuild_Runnable : public FRunnable
{
	
public:
	
	FStartBuild_Runnable(UCubeFactory* CubeFactory, AMyCube* Cube);
	virtual ~FStartBuild_Runnable() override;

private:
	
	UCubeFactory* Factory = nullptr;
	AMyCube* MyCube = nullptr;

	FAgeGeneration_Runnable* RunnableClass_AgeGeneration = nullptr;
	FColorGeneration_Runnable* RunnableClass_ColorGeneration = nullptr;

	TArray<FRunnableThread*> WorkingThreads;
	

public:

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};
