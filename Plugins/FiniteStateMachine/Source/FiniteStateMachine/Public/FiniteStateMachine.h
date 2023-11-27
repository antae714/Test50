// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FiniteStateMachine.generated.h"

/**
*  CDO의 사용을 피하고 고유한 상태머신을 가질수있게 도와줍니다.
*/
USTRUCT(BlueprintType, Blueprintable)
struct FINITESTATEMACHINE_API FFiniteStateMachineHandler
{
	GENERATED_BODY()

public:	
	/**
	* 초기화해주면 작동합니다.
	* @param outer Outer가될 오브젝트로 부모가됩니다.
	*/
	void Init(UObject* outer);

protected:
	/** 사용할 상태머신 블루프린트입니다. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UFiniteStateMachine> FSMClass;

	/** 고유한 상태머신 객체입니다. */
	UPROPERTY(VisibleInstanceOnly, transient, NonTransactional, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFiniteStateMachine> FSMInstance;
};


/**
 * 상태머신 객체입니다.
 */
UCLASS(BlueprintType, Blueprintable)
class FINITESTATEMACHINE_API UFiniteStateMachine : public UObject, public FTickableGameObject
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
	//(BlueprintImplementableEvent, Category = "Finite State Machine")
	//void BeginEvent(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent, Category = "Finite State Machine")
	void TickEvent(float DeltaTime);
	void Init();

	//virtual void BeginDestroy();
	
	/** 현재상태의 업데이트합수를 호출합니다. */
	void UpdateState();
	/** 현재상태의 트랜지션 조건을 검사후 가능하면 전이합니다. */
	void TransitionState();


public:
	/** 한프레임에 전이가능 횟수 입니다.*/
	UPROPERTY(EditAnywhere, Category = Settings)
	int32 MaxTransitionsPerFrame;

protected:
	TArray<struct FFSMState> States;
	TArray<struct FFSMTransition> Transitions;

	FFSMState* CurrrentState;
};


