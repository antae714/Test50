// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetCompilerModule.h"
#include "KismetCompiler.h"

/**
 * 
 */
class FSMEDITOR_API FFSMBlueprintCompiler : public IBlueprintCompiler
{
#pragma region IBlueprintCompiler Interface	
	virtual bool CanCompile(const UBlueprint* Blueprint);
	virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results);
	bool GetBlueprintTypesForClass(UClass* ParentClass, UClass*& OutBlueprintClass, UClass*& OutBlueprintGeneratedClass) const override;
#pragma endregion
};


class FSMEDITOR_API FFSMKismetCompilerContext : public FKismetCompilerContext
{
	typedef FKismetCompilerContext Super;
public:
	FFSMKismetCompilerContext(class UFSMBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompileOptions);


public:
	virtual void SpawnNewClass(const FString& NewClassName) override;
	//virtual UEdGraphSchema_K2* CreateSchema() override;
	virtual bool IsNodePure(const UEdGraphNode* Node) const;
	virtual bool ShouldForceKeepNode(const UEdGraphNode* Node) const override;

	virtual void MergeUbergraphPagesIn(UEdGraph* Ubergraph);
	virtual void CreateFunctionList();
	virtual void CompileFunction(FKismetFunctionContext& Context);



	template<typename T>
	T* GetBlueprint() const
	{
		return Cast<T>(Blueprint);
	}
};