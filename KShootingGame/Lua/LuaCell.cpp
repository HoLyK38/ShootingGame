﻿#include "LuaCell.h"
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cctype>
#include <malloc.h>
#include <cstdlib>
#pragma warning(disable:4996)
#include <assert.h>


LuaCell::LuaCell()
{
	m_LuaState = luaL_newstate();
	luaL_openlibs(m_LuaState);
}

LuaCell::~LuaCell()
{
	lua_close(m_LuaState);
}

bool LuaCell::callLua_Function(const char* functionName)
{
	lua_getglobal(m_LuaState, functionName);
	if (lua_isfunction(m_LuaState, -1))
	{
		if (lua_pcall(m_LuaState, 0, 0, 0) != 0)
		{
			return false;
		}
		else
		{
			return true;
		}		
	}
	return false;
}
//format： callLua_Function("GetTime", "fis>ii", 1.0f, 2, "3", *int, *int);
bool LuaCell::callLua_Function( const char* functionName, const char* signString, ... )
{
	va_list v1;
	int narg, nres;
	va_start(v1, signString);
	lua_getglobal(m_LuaState, functionName);

	for (narg = 0; *signString; narg++)
	{
		luaL_checkstack(m_LuaState, 1, "too many arguments");
		switch (*signString++)
		{
		case 'f':
			lua_pushnumber(m_LuaState, (double)va_arg(v1, float));
			break;
		case 'i':
			lua_pushinteger(m_LuaState, va_arg(v1, int));
			break;
		case 's':
			lua_pushstring(m_LuaState, va_arg(v1, char*));
			break;
		case '>':
			goto emdargs;
		default:
#if _DEBUG
			assert(0 && "callLua_Function args error!");
#endif
			break;
		}
	}
emdargs:
	nres = (int)strlen(signString);
	if (lua_pcall(m_LuaState, narg, nres, 0) != 0)
	{
		return false;
	}

	nres = -nres;
	while (*signString)
	{
		switch (*signString++)
		{
		case 'f':
			*va_arg(v1, double *) = lua_tonumber(m_LuaState, nres);
			break;
		case 'i':
			*va_arg(v1, int *) = (int)lua_tointeger(m_LuaState, nres);
			break;
		case 's':
			*va_arg(v1, const char **) = lua_tostring(m_LuaState, nres);
			break;
		default:
			printf("callLua_Function result args error!\n");
		}
		nres++;
	}

	va_end(v1);
	return true;
}
//if success return true
bool LuaCell::InputLuaFile(const char* path)
{
	if (luaL_loadfile(m_LuaState, path) || lua_pcall(m_LuaState, 0, 0, 0)) return false;
	return true;
}
#if defined(WIN32) || defined(WIN64)
bool LuaCell::InputLuaFile( const wchar_t* path )
{
	std::wstring wstr(path);
	char* ansi = (char*)malloc(wstr.length()+1);
	wcstombs(ansi, wstr.c_str(), INT_MAX);
	if (luaL_loadfile(m_LuaState, ansi) || lua_pcall(m_LuaState, 0, 0, 0)) 
	{
		free(ansi);
		return false;
	}
	free(ansi);
	return true;
}
#endif
//從 table1\table2\table3\varableName 這樣的路徑中得到資料的函數

bool LuaCell::setLua_NewTable(const char* table)
{
	lua_getglobal(m_LuaState, table);
	if (lua_istable(m_LuaState,-1))
	{
		lua_pop(m_LuaState, 1);
		return false;
	}
	else
	{
		lua_newtable(m_LuaState);
		lua_setglobal(m_LuaState, table);
		return true;
	}	
}

bool LuaCell::isDigitString( const char *str )
{
	for (const char *pos=str; *pos != '\0';pos++)
	{
		if (!isdigit(*pos)) 
			return false;
	}
	return true;
}

void* LuaCell::getLua_Value_UsePath( const char* pathString, int type )
{
	void *result = buffer;
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = pathString;;pos++)
	{
		if (*pos == '\\' || *pos == '/') //get Layer string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1)
				lua_getglobal(m_LuaState, path);
			else
			{
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
			}
			target = path;
		}
		else if (*pos == '\0') //get varable string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1) // if varable in global
				lua_getglobal(m_LuaState, path);
			else
			{
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
			}			
			switch (type)
			{
			case BackType(INTEGER):
				*((int*)result) = (int)lua_tointeger(m_LuaState, -1);
				break;
			case BackType(LONGFLOAT):
				*((double*)result) = lua_tonumber(m_LuaState, -1);
				break;
			case BackType(STRING):
				result = const_cast<char*>(lua_tostring(m_LuaState, -1));
				break;
			}
			break;
		}
		else
		{
			*target = *pos;
			++target;
		}
	}	
	lua_pop(m_LuaState, pathLayer);
	return result;
}

void LuaCell::setLua_Value_UsePath( const char* pathString, int type, void* data )
{
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = pathString;;pos++)
	{
		if (*pos == '\\' || *pos == '/') //get Layer string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1)
				lua_getglobal(m_LuaState, path);
			else
			{
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
			}
			target = path;
		}
		else if (*pos == '\0') //get varable string
		{
			++pathLayer;
			*target = '\0'; //c string end
			switch (type)
			{
			case BackType(INTEGER):
				lua_pushinteger(m_LuaState, *static_cast<int*>(data));				
				break;
			case BackType(LONGFLOAT):
				lua_pushnumber(m_LuaState, *static_cast<double*>(data));
				break;
			case BackType(STRING):
				lua_pushstring(m_LuaState, static_cast<char*>(data));
				break;
			}
			if (pathLayer == 1) // if varable in global
				lua_setglobal(m_LuaState, path);
			else
			{
				if (isDigitString(path))	//is integer index?
					lua_rawseti(m_LuaState, -2, atoi(path));
				else
					lua_setfield(m_LuaState, -2, path);
			}			
			break;
		}
		else
		{
			*target = *pos;
			++target;
		}
	}	
	lua_pop(m_LuaState, pathLayer-1);
}

template <> 
int LuaCell::getLua<int>()
{
	return (int)lua_tointeger(m_LuaState, -1);
}
template <> 
double LuaCell::getLua<double>()
{
	return lua_tonumber(m_LuaState, -1);
}
template <> 
const char* LuaCell::getLua<const char*>()
{
	return lua_tostring(m_LuaState, -1);
}

template <class T> 
T LuaCell::getLua(const char* pathString, ...)
{
	// 可變長度的字串
	char *buffer = (char*)malloc(1024);
	va_list args;
	va_start (args, pathString);
	vsprintf (buffer,pathString, args);
	//開始尋找變數
	T result;
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = buffer;;pos++)
	{
		if (*pos == '\\' || *pos == '/') //get Layer string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1)
				lua_getglobal(m_LuaState, path);			
			else
			{
				if (lua_isnil(m_LuaState, -1))
				{
					lua_pop(m_LuaState, pathLayer);
					assert(0&&"getLua");
					return false;	
				}
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
			}
			target = path;
		}
		else if (*pos == '\0') //get varable string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1) // if varable in global
				lua_getglobal(m_LuaState, path);
			else
			{
				if (lua_isnil(m_LuaState, -1))
				{
					lua_pop(m_LuaState, pathLayer);
					assert(0&&"getLua");
					return false;	
				}
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
			}
			result = getLua<T>();
			break;
		}
		else
		{
			*target = *pos;
			++target;
		}
	}	
	lua_pop(m_LuaState, pathLayer);
	free(buffer);
	va_end (args);
	return result;
}
template <>
void LuaCell::setLua<int>(int data)
{
	lua_pushinteger(m_LuaState, data);
}
template <>
void LuaCell::setLua<double>(double data)
{
	lua_pushnumber(m_LuaState, data);
}
template <>
void LuaCell::setLua<const char*>(const char* data)
{
	lua_pushstring(m_LuaState, data);
}
template <class T>
void LuaCell::setLua(T data, const char* pathString, ...)
{
	// 可變長度的字串
	char *buffer = (char*)malloc(1024);
	va_list args;
	va_start (args, pathString);
	vsprintf (buffer,pathString, args);
	//開始尋找變數
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = buffer;;pos++)
	{
		if (*pos == '\\' || *pos == '/') //get Layer string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1)
				lua_getglobal(m_LuaState, path);
			else
			{
				if (lua_isnil(m_LuaState, -1))
				{
					lua_pop(m_LuaState, pathLayer);
					assert(0&&"setLua");
					return ;	
				}
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
			}
			target = path;
		}
		else if (*pos == '\0') //get varable string
		{
			++pathLayer;
			*target = '\0'; //c string end
			setLua<T>(data);
			if (pathLayer == 1) // if varable in global
				lua_setglobal(m_LuaState, path);
			else
			{
				if (lua_isnil(m_LuaState, -1))
				{
					lua_pop(m_LuaState, pathLayer);
					assert(0&&"setLua");
					return ;	
				}
				if (isDigitString(path))	//is integer index?
					lua_rawseti(m_LuaState, -2, atoi(path));
				else
					lua_setfield(m_LuaState, -2, path);
			}			
			break;
		}
		else
		{
			*target = *pos;
			++target;
		}
	}	
	lua_pop(m_LuaState, pathLayer-1);
	free(buffer);
	va_end (args);
}

bool LuaCell::CheckNotNil( const char* pathString, ... )
{
	// 可變長度的字串
	char *buffer = (char*)malloc(1024);
	va_list args;
	va_start (args, pathString);
	vsprintf (buffer,pathString, args);
	char path[250] = {0};
	const char *pos;
	char *target = path;
	int pathLayer = 0;
	for (pos = buffer;;pos++)
	{
		if (*pos == '\\' || *pos == '/' || *pos == '\0') //get Layer string
		{
			++pathLayer;
			*target = '\0'; //c string end
			if (pathLayer == 1)
			{
				lua_getglobal(m_LuaState, path);
				if (lua_isnil(m_LuaState,-1)) 
				{
					lua_pop(m_LuaState, pathLayer);
					free(buffer);
					return false;
				}
			}
			else
			{
				if (!lua_istable(m_LuaState,-1)) 
				{
					lua_pop(m_LuaState, pathLayer);
					free(buffer);
					return false;
				}
				if (isDigitString(path))	//is integer index?
					lua_pushinteger(m_LuaState, atoi(path));
				else
					lua_pushstring(m_LuaState, path);
				lua_gettable(m_LuaState, -2);
				if (lua_isnil(m_LuaState, -1))
				{
					lua_pop(m_LuaState, pathLayer);
					free(buffer);
					return false;	
				}
			}
			target = path;
			if (*pos == '\0')
				break;
		}
		else
		{
			*target = *pos;
			++target;
		}
	}
	lua_pop(m_LuaState, pathLayer);
	free(buffer);
	return true;
}

void LuaCell::RegisterFunction( std::string libname, const luaL_reg* reg )
{
	luaL_register(m_LuaState, libname.c_str(), reg);
}

void LuaCell::luaYield()
{
	lua_yield(m_LuaState, 0);
}

void LuaCell::luaResume()
{
	int status = lua_status(m_LuaState);
	if (status == LUA_YIELD)
	{
		int ret = lua_resume( m_LuaState, 0 );
		if( ret != 0 )
		{
			printf("lua_resume:%d\n", ret);
		}
	}
}
