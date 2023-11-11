// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "FSMBlueprint.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FSM_API UFSMBlueprint : public UBlueprint
{
	GENERATED_BODY()
public:
#pragma region UBlueprint Interface
#if WITH_EDITOR
	virtual void GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const override;



#endif	//#if WITH_EDITOR
#pragma endregion

public:
	UEdGraph* GetRootFSMGraph() const { return RootFSMGraph; }
	void SetRootFSMGraph(UEdGraph* InRootFSMGraph) { RootFSMGraph = InRootFSMGraph; }

private:
	UPROPERTY()
	UEdGraph* RootFSMGraph;
};
