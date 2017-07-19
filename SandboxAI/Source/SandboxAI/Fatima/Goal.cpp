// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "Goal.h"


FGoal::FGoal(float* Variable, float SuccessValue, FString Description) :Description(Description), SuccessValue(SuccessValue), Variable(Variable) {
	if (Variable) {
		StartValue = *Variable;
	}
}
