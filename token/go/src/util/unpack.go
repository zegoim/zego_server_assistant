package util

import (
	"encoding/binary"
	"io"
)

func UnPackUint16(r io.Reader) (uint16, error) {
	var n uint16
	err := binary.Read(r, binary.BigEndian, &n)
	return n, err
}
func UnPackint64(r io.Reader) (int64, error) {
	var n int64
	err := binary.Read(r, binary.BigEndian, &n)
	return n, err
}

func UnPackUint32(r io.Reader) (uint32, error) {
	var n uint32
	err := binary.Read(r, binary.BigEndian, &n)
	return n, err
}

func UnPackInt32(r io.Reader) (int32, error) {
	var n int32
	err := binary.Read(r, binary.BigEndian, &n)
	return n, err
}

func UnPackByte16(r io.Reader) ([16]byte, error) {
	var n [16]byte
	err := binary.Read(r, binary.BigEndian, &n)
	return n, err
}

func UnPackString(r io.Reader) (string, error) {
	n, err := UnPackUint16(r)
	if err != nil {
		return "", err
	}

	buf := make([]byte, n)
	r.Read(buf)
	s := string(buf[:])
	return s, err
}
