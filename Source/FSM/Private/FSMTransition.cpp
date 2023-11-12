// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMTransition.h"

void FFSMTransition::SettingFunction(UFunction* func)
{
	TransitionCondition = func;
}
