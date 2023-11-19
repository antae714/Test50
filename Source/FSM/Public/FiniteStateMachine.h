// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FiniteStateMachine.generated.h"




USTRUCT(BlueprintType)
struct FSM_API FFiniteStateMachineHandler
{
	GENERATED_BODY()
public:
	void Init(UObject* outer);
protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UFiniteStateMachine> FSMClass;
	UPROPERTY(VisibleInstanceOnly, transient, NonTransactional, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFiniteStateMachine> FSMInstance;
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FSM_API UFiniteStateMachine : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UFiniteStateMachine();

	friend struct FFSMState;
	friend struct FFSMTransition;
public:
#pragma region FTickableGameObject Interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }

#pragma endregion
	UFUNCTION(BlueprintImplementableEvent, Category = "Finite State Machine")
	void TickEvent(float DeltaTime);
	void Init();

	void UpdateState();
	void TransitionState();

public:
	UPROPERTY(EditAnywhere, Category = Settings)
	int32 MaxTransitionsPerFrame;


protected:
	TArray<struct FFSMState> States;
	TArray<struct FFSMTransition> Transitions;

	FFSMState* CurrrentState;
};


