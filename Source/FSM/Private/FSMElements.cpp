// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMElements.h"


void FFSMElements::Init(FString _Name, FGuid _CompiledNodeGuid)
{
	Name = _Name;
	CompiledNodeGuid = _CompiledNodeGuid;
}

bool FFSMElements::operator==(FGuid _NodeGuid)
{
	return CompiledNodeGuid == _NodeGuid;
}
