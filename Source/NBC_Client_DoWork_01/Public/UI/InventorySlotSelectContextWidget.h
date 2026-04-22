#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotSelectContextWidget.generated.h"

class UMenuAnchor;
class UButton;

UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventorySlotSelectContextWidget : public UUserWidget
{
	GENERATED_BODY()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButton);
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnUseButtonClicked();
	UFUNCTION()
	void OnCloseButtonClicked();
	UFUNCTION()
	void OnDeleteButtonClicked();
	
	UPROPERTY()
	FOnCloseButton OnCloseButton;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_UseItem;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_DeleteItem;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Close;
};
