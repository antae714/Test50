// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/BlueprintFactory.h"
#include "FSMBlueprintFactory.generated.h"

//#include "ModuleDescriptor.h"
//FModuleDescriptor

/**
 * 
 */
UCLASS(Blueprintable)
class FINITESTATEMACHINEEDITOR_API UFSMBlueprintFactory : public UBlueprintFactory
{
	GENERATED_UCLASS_BODY()

#pragma region UBlueprintFactory Interface	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual bool ShouldShowInNewMenu() const override { return true; }
	virtual bool ConfigureProperties() override { return true; }
#pragma endregion
};
