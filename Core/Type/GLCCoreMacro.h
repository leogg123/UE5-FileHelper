#pragma once


#define REGISTER_SINGLE_SAVE_OBJECT(str) \
	FString Get##str() \
	{ \
		if (UGLCSaveObject* InObject___ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject___->LoadConfig(); \
			return InObject___->str; \
		} \
		return FString();\
	}\
	void Set##str(const FString& InStr) \
	{ \
		if (UGLCSaveObject* InObject_____ = GetMutableDefault<UGLCSaveObject>()) \
		{ \
			InObject_____->LoadConfig();\
			InObject_____->str = InStr; \
			InObject_____->SaveConfig(); \
		} \
	}