package util

import (
	"encoding/binary"
	"io"
)

func PackData(w io.Writer, data interface{}) error {
	return binary.Write(w, binary.BigEndian, data)
}

func UnPackData(r io.Reader, data interface{}) error {
	return binary.Read(r, binary.BigEndian, data)
}

func PackUint16(w io.Writer, n uint16) error {
	return binary.Write(w, binary.BigEndian, n)
}

func PackUint32(w io.Writer, n uint32) error {
	return binary.Write(w, binary.BigEndian, n)
}
func PackInt32(w io.Writer, n int32) error {
	return binary.Write(w, binary.BigEndian, n)
}

func PackUint64(w io.Writer, n uint64) error {
	return binary.Write(w, binary.BigEndian, n)
}
func PackInt64(w io.Writer, n int64) error {
	return binary.Write(w, binary.BigEndian, n)
}

func PackString(w io.Writer, s string) error {
	err := PackUint16(w, uint16(len(s)))
	if err != nil {
		return err
	}
	_, err = w.Write([]byte(s))
	return err
}
