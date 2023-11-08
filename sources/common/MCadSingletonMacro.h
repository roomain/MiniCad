#pragma once

#define NOT_COPIABLE(classname)\
public:\
classname(const classname&) = delete;\
classname(classname&&)noexcept = delete;\
classname& operator = (const classname&) = delete;\
classname& operator = (classname&&)noexcept = delete;