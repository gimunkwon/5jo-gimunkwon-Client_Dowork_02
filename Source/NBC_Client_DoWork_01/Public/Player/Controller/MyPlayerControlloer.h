#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerControlloer.generated.h"

UCLASS()
class NBC_CLIENT_DOWORK_01_API AMyPlayerControlloer : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerControlloer();
	
	virtual void BeginPlay() override;
};
