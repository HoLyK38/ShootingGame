/*! @brief 這個類別是用來與lua做簡單的溝通的類別
使用了void*與template做了同樣的功能
對lua做的包裝，用法大致如下
double a = cell.getLua<double>("table2\\table23\\table2\\1");
cell.setLua<int>("table2\\table23\\table2\\1",100);
const char* b = cell.getLua<const char*>("table2\\table23\\table2\\1");
*/
#pragma once
#include "lua.hpp"
#include <string>
#if defined (WIN32) || defined (WIN64)
#include "windows.h"
#endif
#ifdef WIN64
#	if _DEBUG
#		pragma comment(lib, "Lua/lua5.1dx64.lib")
#	else
#		pragma comment(lib, "Lua/lua5.1x64.lib")
#	endif // _DEBUG
#else 
#	if _DEBUG
#		pragma comment(lib, "Lua/lua5.1d.lib")
#	else
#		pragma comment(lib, "Lua/lua5.1.lib")
#	endif // _DEBUG
#endif

#include <cstdarg>

class LuaCell
{
public:
	enum BackType {INTEGER,LONGFLOAT,STRING};
	/// 初始化函數，會製造一個lua狀態機
	LuaCell();
	~LuaCell();
	/// 呼叫lua無參數的function
	bool callLua_Function(const char* functionName);
	/// 呼叫lua無參數的function
	bool callLua_Function(const char* functionName, const char* signString, ...);
	/// 讀入一個lua檔，得到這個檔的函數與變數
	bool InputLuaFile(const char* path);
#if defined(WIN32) || defined(WIN64)
	bool InputLuaFile(const wchar_t* path);
#endif
	/// 讀取lua中的變數，不可使用超過1024字元的可變字串
	template <class T> T getLua(const char* pathString, ...);
	/// 設定lua中的變數，不可使用超過1024字元的可變字串
	template <class T> void setLua(T data, const char* pathString, ...);
	bool setLua_NewTable(const char* table);
	bool CheckNotNil(const char* pathString, ...);
	void RegisterFunction(std::string libname, const luaL_reg* reg);
	void luaYield();
	void luaResume();
private:
	void 		setLua_Value_UsePath(const char* pathString, int type, void* data);
	void*		getLua_Value_UsePath(const char* pathString, int type );
	void*		getLua_Value(const char* pathString, int type, va_list vlist);
	template <class T> T getLua() {return NULL;}
	template <> int		getLua<int>();
	template <> double	getLua<double>();
	template <> const char*	getLua<const char*>();
	template <class T> void setLua(T data) {}
	template <> void setLua<int>(int data);
	template <> void setLua<double>(double data);
	template <> void setLua<const char*>(const char* data);
	bool isDigitString(const char *str);
	lua_State* m_LuaState;
	char buffer[10];
};
//要預先宣告偏特化才不會連結錯誤
template int LuaCell::getLua<int>(const char* pathString, ...);
template double LuaCell::getLua<double>(const char* pathString, ...);
template const char* LuaCell::getLua<const char*>(const char* pathString, ...);
template void LuaCell::setLua(int data, const char* pathString, ...);
template void LuaCell::setLua(double data, const char* pathString, ...);
template void LuaCell::setLua(const char* data, const char* pathString, ...);


