// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBlueprint.h"
#include "FiniteStateMachine.h"

#if WITH_EDITOR
void UFSMBlueprint::GetReparentingRules(TSet<const UClass*>& AllowedChildrenOfClasses, TSet<const UClass*>& DisallowedChildrenOfClasses) const
{
	AllowedChildrenOfClasses.Add(UFiniteStateMachine::StaticClass());
}
#endif	//#if WITH_EDITOR