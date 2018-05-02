// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudACL.h"

#include "BCWrapperProxy.generated.h"

class BrainCloudWrapper;
class ABrainCloud;

UCLASS(BlueprintType)
class UBCWrapperProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
	GENERATED_BODY()

public:
	static ABrainCloud *DefaultBrainCloudInstance;

	UBCWrapperProxy(const FObjectInitializer& ObjectInitializer);
	
	/**
	* Create an actor that contains its own instance of the brainCloud Wrapper
	* This actor will destory itself on EndPlay
	*
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud")
		static ABrainCloud *CreateBrainCloudActor(const FString& wrapperName);

	/**
	* Set a default brainCloud instance to be used when none is provided.
	* When not set, the brainCloud Singleton will be used
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud")
		static void SetDefaultBrainCloudInstance(ABrainCloud *brainCloud);

	/**
	* Clear the default brainCloud instance
	* When not set, the brainCloud Singleton will be used
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud")
		static void ClearDefaultBrainCloudInstance();


	/*
    * Wrapper Authenticate the user using a userid and password (without any validation on the userid).
    * Similar to AuthenticateEmailPassword - except that that method has additional features to
    * allow for e-mail validation, password resets, etc.
    *
    * Service Name - Wrapper Authenticate
    * Service Operation - Authenticate
    *
    * Param - email  The e-mail address of the user
    * Param - password  The password of the user
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|WrapperAuthentication")
        static UBCWrapperProxy* AuthenticateUniversal(ABrainCloud *brainCloud, FString userId, FString password, bool forceCreate);

	/**
	* Returns a non null reference to brainCloud
	*
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
	static BrainCloudWrapper *GetBrainCloudInstance(ABrainCloud *brainCloud);


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
