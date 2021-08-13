package token03

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"encoding/base64"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"math/rand"
	"time"

	"github.com/zegoim/zego_server_assistant/token/go/src/errors"
)

const (
	PrivilegeKeyLogin   = 1 // 登录
	PrivilegeKeyPublish = 2 // 推流
	PrivilegeEnable     = 1 // 开启
	PrivilegeDisable    = 0 // 关闭
)

type TokenInfo struct {
	AppId      uint32      `json:"app_id"`
	RoomId     string      `json:"room_id"`
	UserId     string      `json:"user_id"`
	Privilege  map[int]int `json:"privilege"`
	CreateTime int64       `json:"create_time"`
	ExpireTime int64       `json:"expire_time"`
	Nonce      int64       `json:"nonce"`
}

func GenerateToken03(appId uint32, roomId, userId string, privilege map[int]int, secret string, effectiveTimeInSeconds int64) (string, error) {
	if appId == 0 {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "appId Invalid")
	}
	if roomId == "" {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "roomId Invalid")
	}
	if userId == "" {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "userId Invalid")
	}
	if len(secret) != 32 {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "secret Invalid")
	}
	if effectiveTimeInSeconds <= 0 {
		return "", errors.NewZegoSDKError(errors.InvalidParamErrorCode, "effectiveTimeInSeconds Invalid")
	}
	tokenInfo := &TokenInfo{
		AppId:      appId,
		RoomId:     roomId,
		UserId:     userId,
		Privilege:  privilege,
		CreateTime: time.Now().Unix(),
		Nonce:      makeNonce(),
	}
	tokenInfo.ExpireTime = tokenInfo.CreateTime + effectiveTimeInSeconds
	// 把token信息转成json
	plaintText, err := json.Marshal(tokenInfo)
	if err != nil {
		return "", errors.NewZegoSDKError(errors.JsonUnmarshalErrorCode, err.Error())
	}

	// 随机生成的 16 字节串，用作 AES 加密向量，放在密文前一起做Base64编码生成最终 token
	iv := makeRandomIv()

	// AES加密，使用模式: CBC/PKCS5Padding
	encryptBuf, err := aesEncrypt(plaintText, []byte(secret), iv)
	if err != nil {
		return "", errors.NewZegoSDKError(errors.EncryptErrorCode, fmt.Sprintf("AesEncrypt error:%s, plaintText:%s, iv:%s", err.Error(), plaintText, iv))
	}

	// len+data
	resultSize := len(encryptBuf) + 28
	result := bytes.NewBuffer(make([]byte, 0, resultSize))

	// 打包数据
	err = packInt64(result, tokenInfo.ExpireTime)
	if err != nil {
		return "", errors.NewZegoSDKError(errors.EncodeErrorCode, fmt.Sprintf("PackData1 error:%s, timeout:%d, result%s", err, tokenInfo.ExpireTime, result))
	}
	err = packString(result, string(iv))
	if err != nil {
		return "", errors.NewZegoSDKError(errors.EncodeErrorCode, fmt.Sprintf("PackData2 error:%s, iv:%d, result%s", err, iv, result))
	}
	err = packString(result, string(encryptBuf))
	if err != nil {
		return "", errors.NewZegoSDKError(errors.EncodeErrorCode, fmt.Sprintf("PackData3 error:%s, cryptedData:%d, result%s", err, encryptBuf, result))
	}

	thirdToken := "03" + base64.StdEncoding.EncodeToString(result.Bytes())
	return thirdToken, nil
}

func makeNonce() int64 {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	return int64(r.Uint64())
}

func makeRandomIv() []byte {
	str := "0123456789abcdefghijklmnopqrstuvwxyz"
	bytes := []byte(str)
	result := []byte{}
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	for i := 0; i < 16; i++ {
		result = append(result, bytes[r.Intn(len(bytes))])
	}
	return result
}

func aesEncrypt(origData, key, iv []byte) ([]byte, error) {
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}
	blockSize := block.BlockSize()
	origData = aesPKCS5Padding(origData, blockSize)
	if origData == nil {
		return nil, fmt.Errorf("origData padding nil")
	}

	blockMode := cipher.NewCBCEncrypter(block, iv)
	encrypted := make([]byte, len(origData))
	blockMode.CryptBlocks(encrypted, origData)
	return encrypted, nil
}

func aesPKCS5Padding(ciphertext []byte, blockSize int) []byte {
	padding := blockSize - len(ciphertext)%blockSize
	if padding < 0 {
		return nil
	}
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(ciphertext, padText...)
}

func packUint16(w io.Writer, n uint16) error {
	return binary.Write(w, binary.BigEndian, n)
}

func packInt64(w io.Writer, n int64) error {
	return binary.Write(w, binary.BigEndian, n)
}

func packString(w io.Writer, s string) error {
	err := packUint16(w, uint16(len(s)))
	if err != nil {
		return err
	}
	_, err = w.Write([]byte(s))
	return err
}
