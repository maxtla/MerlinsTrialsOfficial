#ifndef ENUMERATORS_H
#define ENUMERATORS_H

//Add project enumerators to this file

enum HOLDING {YES, NO};
enum PUZZLE_PHASE { FIRST, SECOND };
enum Dimension { NORMAL, OTHER };
enum sunType { RED, BLUE, YELLOW };



enum SHADERTYPE {
	VertexPosCol,
	VertexPosNorm,
	VertexPosNormTex,
	VertexPosNormCol,
	VertexPosNormColTex
};

enum NORMALMAP_SHADER_TYPE
{
	NO_COLOR,
	WITH_COLOR
};

enum BLENDSTATES
{
	OPAQUE_STATE,
	ALPHPA_BLEND_STATE,
	ADDITIVE_STATE,
	NON_PREMULTIPLIED_STATE
};

enum DEPTHSTENCILSTATES
{
	DEPTH_NONE_STATE,
	DEPTH_DEFAULT_STATE,
	DEPTH_READ_STATE
};

enum RASTERIZERSTATES
{
	CULL_NONE_STATE,
	CULL_CLOCKWISE_STATE,
	CULL_COUNTERCLOCKWISE_STATE,
	WIREFRAME_STATE
};

enum SAMPLERSTATES
{
	POINT_WRAP_STATE,
	POINT_CLAMP_STATE,
	LINEAR_WRAP_STATE,
	LINEAR_CLAMP_STATE,
	ANISOTROPIC_WRAP_STATE,
	ANISOTROPIC_CLAMP_STATE
};

enum KEY
{
	Unknown = -1,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	Num0 = 0x30,
	Num1 = 0x31,
	Num2 = 0x32,
	Num3 = 0x33,
	Num4 = 0x34,
	Num5 = 0x35,
	Num6 = 0x36,
	Num7 = 0x37,
	Num8 = 0x38,
	Num9 = 0x39,
	EscapeKey = 0x1B,
	LShift = 0x10,
	LControl = 0x11,
	LAlt = 0x12,
	Space = 0x20,
	Return = 0x0D,
	BackSpace = 0x08,
	Tab = 0x09,
	Left = 0x25,
	Right = 0x26,
	Up = 0x27,
	Down = 0x28,
	Numpad0 = 0x60,
	Numpad1 = 0x61,
	Numpad2 = 0x62,
	Numpad3 = 0x63,
	Numpad4 = 0x64,
	Numpad5 = 0x65,
	Numpad6 = 0x66,
	Numpad7 = 0x67,
	Numpad8 = 0x68,
	Numpad9 = 0x69,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
};

#endif // !ENUMERATORS_H
