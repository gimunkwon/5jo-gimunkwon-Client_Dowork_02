#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryAddItemWidget.generated.h"

class UImage;
class UButton;

UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventoryAddItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemID")
	FName ItemID;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_AddItem;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Button;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataTable")
	TObjectPtr<UDataTable> ItemDataTable;
	
protected:
	UFUNCTION()
	void OnButtonPressed();
	void InitializeButtonImage();
};
