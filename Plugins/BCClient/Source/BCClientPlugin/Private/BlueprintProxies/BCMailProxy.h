// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCMailProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCMailProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCMailProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* Sends a simple text email to the specified player
	*
	* Service Name - mail
	* Service Operation - SEND_BASIC_EMAIL
	*
	* Param - profileId The user to send the email to
	* Param - subject The email subject
	* Param - body The email body
	*/
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Mail")
        static UBCMailProxy* SendBasicEmail(ABrainCloud *brainCloud, const FString& profileId, const FString& subject, const FString& body);

	/**
	* Sends an advanced email to the specified player
	*
	* Service Name - mail
	* Service Operation - SEND_ADVANCED_EMAIL
	*
	*Param - profileId The user to send the email to
	*Param - jsonServiceParams Parameters to send to the email service. See the documentation for
	*	a full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Mail")
		static UBCMailProxy* SendAdvancedEmail(ABrainCloud *brainCloud, const FString& profileId, const FString& jsonServiceParams);

	/**
	* Sends an advanced email to the specified email address
	*
	* Service Name - mail
	* Service Operation - SEND_ADVANCED_EMAIL_BY_ADDRESS
	*
	*Param - emailAddress The address to send the email to
	*Param - jsonServiceParams Parameters to send to the email service. See the documentation for
	*	a full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Mail")
		static UBCMailProxy* SendAdvancedEmailByAddress(ABrainCloud *brainCloud, const FString& emailAddress, const FString& jsonServiceParams);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
