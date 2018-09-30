#pragma once
#ifndef STRUCTS_H_
#define STRUCTS_H_

struct KeyStroke
{
public:
	int _key;
	int _scancode;
	int _action;
	int _mods;
};

struct ButtonClick
{
public:
	int _button;
	int _action;
	int _mods;
	glm::vec2 _position;
};

#endif // !STRUCTS_H_
