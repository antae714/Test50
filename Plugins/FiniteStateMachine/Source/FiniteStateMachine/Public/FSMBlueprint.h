// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "FSMBlueprint.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FINITESTATEMACHINE_API UFSMBlueprint : public UBlueprint
{
	GENERATED_BODY()
public:
#pragma region UBlueprint Interface
#if WITH_EDITOR
	virtual void GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const override;

#endif	//#if WITH_EDITOR
#pragma endregion

public:
	/** 루트 상태그래프를 반환합니다. */
	UEdGraph* GetRootFSMGraph() const { return RootFSMGraph; }
	/** 루트 상태그래프를 세팅합니다. */
	void SetRootFSMGraph(UEdGraph* InRootFSMGraph) { RootFSMGraph = InRootFSMGraph; }

private:
	UPROPERTY()
	UEdGraph* RootFSMGraph;
};
