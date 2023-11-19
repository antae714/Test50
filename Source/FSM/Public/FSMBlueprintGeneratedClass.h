// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMBlueprintGeneratedClass.generated.h"

/**
 * 
 */
UCLASS()
class FSM_API UFSMBlueprintGeneratedClass : public UBlueprintGeneratedClass
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<struct FFSMStateClass> States;
	UPROPERTY()
	TArray<struct FFSMTransitionClass> Transitions;
	UPROPERTY()
	FGuid EnteryStateGUID;
};
