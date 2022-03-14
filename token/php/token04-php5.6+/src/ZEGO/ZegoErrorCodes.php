<?php
namespace ZEGO;

class ZegoErrorCodes{
    const success                       = 0;  // 获取鉴权 token 成功
    const appIDInvalid                  = 1;  // 调用方法时传入 appID 参数错误
    const userIDInvalid                 = 3;  // 调用方法时传入 userID 参数错误
    const secretInvalid                 = 5;  // 调用方法时传入 secret 参数错误
    const effectiveTimeInSecondsInvalid = 6;  // 调用方法时传入 effectiveTimeInSeconds 参数错误
}