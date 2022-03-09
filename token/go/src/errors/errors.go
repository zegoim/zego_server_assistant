package errors

import "fmt"

const (
	DefaultClientErrorCode = "SDK.ClientError"
	MissingParamErrorCode  = "SDK.MissingParam"
	InvalidParamErrorCode  = "SDK.InvalidParam"
	TimeoutErrorCode       = "SDK.TimeoutError"
	EncryptErrorCode       = "SDK.EncryptError"
	EncodeErrorCode        = "SDK.EncodetError"
	JsonUnmarshalErrorCode = "SDK.JsonUnmarshalError"
	JsonMarshalErrorCode   = "SDK.JsonMarshalError"
)

type ZegoSDKError struct {
	Code    string
	Message string
}

func (e *ZegoSDKError) Error() string {
	return fmt.Sprintf("[ZegoSDKError] Code=%s, Message=%s", e.Code, e.Message)
}

func NewZegoSDKError(code, message string) error {
	return &ZegoSDKError{
		Code:    code,
		Message: message,
	}
}

func (e *ZegoSDKError) GetCode() string {
	return e.Code
}

func (e *ZegoSDKError) GetMessage() string {
	return e.Message
}
