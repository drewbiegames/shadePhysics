#pragma once

enum InputEnum {
	CLEAR = 0x00,

	FOREWARD = 1 << 0,
	BACKWARD = 1 << 1,
	STFRIGHT = 1 << 2,
	STFLEFT = 1 << 3,

};

inline InputEnum operator |(InputEnum a, InputEnum b){
	return static_cast<InputEnum>((int)a | (int)b);
}

inline InputEnum operator &(InputEnum a, InputEnum b){
	return static_cast<InputEnum>((int)a & (int)b);
}

inline InputEnum operator ~(InputEnum a){
	return static_cast<InputEnum>(~(int)a);
}