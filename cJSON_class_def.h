#ifndef __CJSON_CLASS_DEF_H__
#define __CJSON_CLASS_DEF_H__


#include "cJSON.h"
#include <vector>
#include <string>
#include <stdarg.h>
#include <string.h>
#include <exception>

/* json解析异常 */
struct MyJsonParseError : public std::exception
{
	const char* what() const throw()
	{
		return "Json parse error.";
	}
};

/* json添加string类型 异常 */
struct MyJsonAddStringError : public std::exception
{
	const char* what() const throw()
	{
		return "Json add string error.";
	}
};

/* 参数错误 */
struct MyJsonParameterError : public std::exception
{
	const char* what() const throw()
	{
		return "MyJsonParameterError error.";
	}
};

/* json添加double类型 异常 */
struct MyJsonAddNumError : public std::exception
{
	const char* what() const throw()
	{
		return "Json add number error.";
	}
};

/* json添加bool类型 异常 */
struct MyJsonAddBoolError : public std::exception
{
	const char* what() const throw()
	{
		return "Json add bool error.";
	}
};

/* json添加对象类型 异常 */
struct MyJsonAddObjError : public std::exception
{
	const char* what() const throw()
	{
		return "Json add object error.";
	}
};

/* json添加对象类型 异常 */
struct MyJsonAddArrayError : public std::exception
{
    const char* what() const throw()
    {
        return "Json add MyJsonAddArrayError error.";
    }
};

/* json转化为字符串  异常 */
struct MyJsonToStringError : public std::exception
{
	const char* what() const throw()
	{
		return "Json to string error.";
	}
};

/* MyJson类构造失败  异常 */
struct MyJsonConstructorError : public std::exception
{
	const char* what() const throw()
	{
		return "MyJson Constructor failed";
	}
};

/* MyJson类拷贝构造失败  异常 */
struct MyJsonCopyConstructorError : public std::exception
{
	const char* what() const throw()
	{
		return "MyJson copy Constructor failed";
	}
};


/* josn转换成string  异常 */
struct MyJsonJsonToStringError : public std::exception
{
	const char* what() const throw()
	{
		return "MyJson json to string failed";
	}
};

/* josn转换成string  异常 */
struct MyJsonJsonToNumberError : public std::exception
{
	const char* what() const throw()
	{
		return "MyJson json to int error";
	}
};

/* josn转换成int  异常 */
struct MyJsonJsonToVectorError : public std::exception
{
    const char* what() const throw()
    {
        return "MyJson json to vector error";
    }
};

namespace MyCJson
{

#define JSON_PARSE_ERROR		1			

#define GET_JOSN_ITEM_CASE_SENSITIVE(JSON_OBJ, NAME) cJSON_GetObjectItemCaseSensitive(JSON_OBJ, #NAME)




	class MyCJson
	{
	public:

		MyCJson() 
		{
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_CreateObject();
			if (!m_jsonObject)
			{
				throw MyJsonConstructorError();
			}

		}
		/* 从json字符串构造 */
		MyCJson(const char* const json)
		{
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_Parse(json);
			if (NULL == m_jsonObject)
			{
				/* 抛出解析错误异常 */
				throw MyJsonParseError();
			}
		}
		MyCJson(const std::string json)
		{
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_Parse(json.c_str());
			if (NULL == m_jsonObject)
			{
				/* 抛出解析错误异常 */
				throw MyJsonParseError();
			}
		}

		/* 重构拷贝构造函数，深度拷贝 */
		MyCJson(const MyCJson& tmpObj)
		{
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_DeepCopyFromObject(tmpObj.get_json_ptr());
			if (NULL == m_jsonObject)
			{
				/* 抛出解析错误异常 */
				throw MyJsonCopyConstructorError();
			}
		}

		/* 重构拷贝构造函数，深度拷贝 */
		MyCJson(MyCJson& tmpObj)
		{
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_DeepCopyFromObject(tmpObj.get_json_ptr());
			if (NULL == m_jsonObject)
			{
				/* 抛出解析错误异常 */
				throw MyJsonCopyConstructorError();
			}
		}

		/* 模板构造，从自定义结构体构造MyJson对象 */
		template<typename T>
		MyCJson(T& t)
		{
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_CreateObject();
			if (!m_jsonObject)
			{
				throw MyJsonConstructorError();
			}


			t.to_json(*this, t);
		}

		/* 重载复制运算符 */
		MyCJson& operator=(const MyCJson& tmpObj)
		{
			/* 将原来的释放掉 */
			cJSON_Delete(m_jsonObject);

			/* 深度拷贝新的新的 */
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_DeepCopyFromObject(tmpObj.get_json_ptr());
			if (NULL == m_jsonObject)
			{
				/* 抛出解析错误异常 */
				throw MyJsonCopyConstructorError();
			}
		}
		MyCJson& operator=(MyCJson& tmpObj)
		{
			/* 将原来的释放掉 */
			cJSON_Delete(m_jsonObject);

			/* 深度拷贝新的新的 */
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_DeepCopyFromObject(tmpObj.get_json_ptr());
			if (NULL == m_jsonObject)
			{
				/* 抛出解析错误异常 */
				throw MyJsonCopyConstructorError();
			}
		}

		/* 自定义结构体转换为MyJson对象 */
		template <typename T>
		MyCJson& operator=(const T& tmpObjS)
		{
			/* 将原来的释放掉 */
			cJSON_Delete(m_jsonObject);

			/* 创建一个新的CJson */
			m_jsonObject_notDelete = NULL;
			m_jsonObject = cJSON_CreateObject();
			if (!m_jsonObject)
			{
				throw MyJsonConstructorError();
			}
			tmpObjS.to_json(*this, tmpObjS);
		}

		/* 只在中间对象初始化时使用此构造函数 */
		MyCJson(cJSON* obj) :m_jsonObject_notDelete(obj), m_jsonObject(NULL)
		{
			if (!m_jsonObject_notDelete)
			{
				throw MyJsonConstructorError();
			}
		}
        MyCJson(cJSON* obj, bool bIsNotDelete)
        {
            if (!obj)
            {
                throw MyJsonConstructorError();
            }
            if (bIsNotDelete)
            {
                m_jsonObject_notDelete = obj;
                m_jsonObject = NULL;
            }
            else 
            {
                m_jsonObject_notDelete = NULL;
                m_jsonObject = obj;
            }
        }
		~MyCJson()
		{
			/* 不释放m_jsonObject_notDelete，会在最外面的对象析构时释放 */
			cJSON_Delete(m_jsonObject);			
		}

		/* 添加string到json */
		void add_to_json(const char* key, const char* value)
		{
			if (m_jsonObject_notDelete)
			{
				if (cJSON_AddStringToObject(m_jsonObject_notDelete, key, value) == NULL)
				{
					throw MyJsonAddStringError();
				}
			}
			else
			{
				if (cJSON_AddStringToObject(m_jsonObject, key, value) == NULL)
				{
					throw MyJsonAddStringError();
				}
			}
		}

		void add_to_json(const char* key, const std::string& value)
		{
			if (m_jsonObject_notDelete)
			{
				if (cJSON_AddStringToObject(m_jsonObject_notDelete, key, value.c_str()) == NULL)
				{
					throw MyJsonAddStringError();
				}
			}
			else
			{
				if (cJSON_AddStringToObject(m_jsonObject, key, value.c_str()) == NULL)
				{
					throw MyJsonAddStringError();
				}
			}
			
		}

		/* 添加Double到json */
		void add_to_json(const char* key, const double value)
		{
			if (m_jsonObject_notDelete)
			{
				if (cJSON_AddNumberToObject(m_jsonObject_notDelete, key, value) == NULL)
				{
					throw MyJsonAddNumError();
				}
			}
			else
			{
				if (cJSON_AddNumberToObject(m_jsonObject, key, value) == NULL)
				{
					throw MyJsonAddNumError();
				}
			}
		}

		/* 添加Double到json */
		void add_to_json(const char* key, const int value)
		{
			if (m_jsonObject_notDelete)
			{
				if (cJSON_AddNumberToObject(m_jsonObject_notDelete, key, (double)value) == NULL)
				{
					throw MyJsonAddNumError();
				}
			}
			else
			{
				if (cJSON_AddNumberToObject(m_jsonObject, key, (double)value) == NULL)
				{
					throw MyJsonAddNumError();
				}
			}
		}
        
        /* 添加const unsigned int到json */
        void add_to_json(const char* key, const unsigned int value)
        {
            if (m_jsonObject_notDelete)
            {
                if (cJSON_AddNumberToObject(m_jsonObject_notDelete, key, (double)value) == NULL)
                {
                    throw MyJsonAddNumError();
                }
            }
            else
            {
                if (cJSON_AddNumberToObject(m_jsonObject, key, (double)value) == NULL)
                {
                    throw MyJsonAddNumError();
                }
            }
        }
        
        ///* 添加unsigned int到json */
        //void add_to_json(const char* key, unsigned int value)
        //{
        //	if (m_jsonObject_notDelete)
        //	{
        //		if (cJSON_AddNumberToObject(m_jsonObject_notDelete, key, (double)value) == NULL)
        //		{
        //			throw MyJsonAddNumError();
        //		}
        //	}
        //	else
        //	{
        //		if (cJSON_AddNumberToObject(m_jsonObject, key, (double)value) == NULL)
        //		{
        //			throw MyJsonAddNumError();
        //		}
        //	}
        //}
        
        
		/* 添加bool到json */
		void add_to_json(const char* key, const bool value)
		{
			if (m_jsonObject_notDelete)
			{
				if (value)
				{
					if (cJSON_AddTrueToObject(m_jsonObject_notDelete, key) == NULL)
					{
						throw MyJsonAddBoolError();
					}
				}
				else
				{
					if (cJSON_AddFalseToObject(m_jsonObject_notDelete, key) == NULL)
					{
						throw MyJsonAddBoolError();
					}
				}
			}
			else
			{
				if (value)
				{
					if (cJSON_AddTrueToObject(m_jsonObject, key) == NULL)
					{
						throw MyJsonAddBoolError();
					}
				}
				else
				{
					if (cJSON_AddFalseToObject(m_jsonObject, key) == NULL)
					{
						throw MyJsonAddBoolError();
					}
				}
			}
		}

		/* 添加自定义结构体到json */
		template<typename T>
		void add_to_json(const char* key, const T& value)
		{
			cJSON* obj = NULL;
			if (m_jsonObject_notDelete)
			{
				obj = cJSON_AddObjectToObject(m_jsonObject_notDelete, key);
			}
			else
			{
				obj = cJSON_AddObjectToObject(m_jsonObject, key);
			}
			if (NULL == obj)
			{
				throw MyJsonAddObjError();
			}
			/* 添加的如果是自定义的结构体T类型变量，则调用结构体里的to_json函数，
				to_json(cJSON* obj, const T& value) */
            /* 使用 MyCJson(cJSON* obj) 构造函数创建子对象，子对象内部cJSON指针内存由父对象释放 */
			MyCJson J(obj);
			value.to_json(J, value);

		}

        /* 向array中添加元素，只有自定义结构体可以定义array列表，基础类型不能定义 */
        template<typename T>
        void add_to_array(const T& value)
        {
            cJSON* obj = cJSON_CreateObject();
            if (NULL == obj)
            {
                throw MyJsonAddObjError();
            }
            MyCJson J(obj);
            value.to_json(J, value);
            if (m_jsonObject_notDelete)
            {
                cJSON_AddItemToArray(m_jsonObject_notDelete, obj);
            }
            else
            {
                cJSON_AddItemToArray(m_jsonObject, obj);
            }
        }
        
        /* 添加vector列表到json */
        template <typename T>
        void add_to_json(const char* key, std::vector<T> value)
        {
            cJSON* obj = NULL;
            if (m_jsonObject_notDelete)
            {
                obj = cJSON_AddArrayToObject(m_jsonObject_notDelete, key);
            }
            else
            {
                obj = cJSON_AddArrayToObject(m_jsonObject, key);
            }
            if (NULL == obj)
            {
                throw MyJsonAddArrayError();
            }
            MyCJson J(obj);
            for (int i = 0; i < value.size(); i++)
            {
                J.add_to_array(value[i]);
            }
        }
        
        
		/* json赋值到char* */
		void get_to(char* value, const char* key)
		{
			if ((!key) || (!value))
			{
				throw MyJsonParameterError();
			}
			const cJSON* j = NULL;
			if (m_jsonObject)
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
            }
            else
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject_notDelete, key);
            }
			if (cJSON_IsString(j) && (j->valuestring != NULL))
			{
				strncpy(value, j->valuestring, strlen(j->valuestring));
			}
			else
			{
				throw MyJsonJsonToStringError();
			}
		}

		/* json赋值到string */
		void get_to(std::string& value, const char* key)
		{
			if ((!key))
			{
				throw MyJsonParameterError();
			}
			const cJSON* j = NULL;
			if (m_jsonObject)
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
            }
            else
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject_notDelete, key);
            }
			if (cJSON_IsString(j) && (j->valuestring != NULL))
			{
				value = j->valuestring;
			}
			else
			{
				throw MyJsonJsonToStringError();
			}
		}

		/* json赋值到number */
		void get_to(double& value, const char* key)
		{
			if ((!key))
			{
				throw MyJsonParameterError();
			}
			const cJSON* j = NULL;
			if (m_jsonObject)
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
            }
            else
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject_notDelete, key);
            }
			if (cJSON_IsNumber(j))
			{
				value = j->valuedouble;
			}
			else
			{
				throw MyJsonJsonToNumberError();
			}
		}
		
		/* json赋值到number */
		void get_to(int& value, const char* key)
		{
			if ((!key))
			{
				throw MyJsonParameterError();
			}
			const cJSON* j = NULL;
			if (m_jsonObject)
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
            }
            else
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject_notDelete, key);
            }
			if (cJSON_IsNumber(j))
			{
				value = j->valueint;
			}
			else
			{
				throw MyJsonJsonToNumberError();
			}
		}

        /* json赋值到number */
        void get_to(unsigned int& value, const char* key)
        {
            if ((!key))
            {
                throw MyJsonParameterError();
            }
            const cJSON* j = NULL;
            if (m_jsonObject)
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
            }
            else
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject_notDelete, key);
            }
            if (cJSON_IsNumber(j))
            {
                value = j->valueint;
            }
            else
            {
                throw MyJsonJsonToNumberError();
            }
        }
            
		/* json赋值到vector */
        template <typename T>
        void get_to(std::vector<T>& value, const char* key)
        {
            if ((!key))
            {
                throw MyJsonParameterError();
            }
            const cJSON* j = NULL;
            if (m_jsonObject)
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
            }
            else
            {
                j = cJSON_GetObjectItemCaseSensitive(m_jsonObject_notDelete, key);
            }
            if (cJSON_IsArray(j))
            {
                /* 如果类型是array, 遍历 */
                cJSON* item = NULL;
                cJSON_ArrayForEach(item, j)
                {
                    T temp;
                    cJSON* tj = cJSON_DeepCopyFromObject(item);
                    MyCJson mj(tj, false);
                    temp.from_json(mj, temp);
                    value.emplace_back(temp);
                }
            }
            else
            {
                throw MyJsonJsonToVectorError();
            }
        }


		template<typename T>
		void get_to(T& value, const char* key = NULL) const
		{
			MyCJson mj;
			const cJSON* j = NULL;
			if (!key)
			{
				value.from_json(*this, value);
			}
			else
			{
				j = cJSON_GetObjectItemCaseSensitive(m_jsonObject, key);
				mj.set_json(j);
				value.from_json(mj, value);
			}
			
			
		}





        void set_json(const cJSON* j) 
        {
            cJSON_Delete(m_jsonObject);
            m_jsonObject = cJSON_DeepCopyFromObject(j);
        }

        void parse(const std::string json_string)
        {
            cJSON* j = cJSON_Parse(json_string.c_str());
            if (!j)
            {
                throw MyJsonParseError();
            }
            else
            {
                cJSON_Delete(m_jsonObject);
                cJSON_Delete(m_jsonObject_notDelete);
                m_jsonObject = j;
                m_jsonObject_notDelete = NULL;
            }
        }






		/* json转化为字符串 */
		std::string dump()
		{
			char* string = NULL;
			string = cJSON_Print(m_jsonObject);
			if (string == NULL)
			{
				throw MyJsonToStringError();
			}
			std::string str = std::string(string);

            free(string);
            return str;
		}

		const cJSON* get_json_ptr() const
		{
			return this->m_jsonObject;
		}


	private:
		cJSON* m_jsonObject;
		cJSON* m_jsonObject_notDelete;    /* 中间object由外部delete */
	};


}

//=========================================================================================
#define MY_JSON_HELPER(Type, ...)  \
    inline void to_json(MyCJson::MyCJson& myJson_j, const Type& myJson_t) const { MY_JSON_EXPAND(MY_JSON_PASTE(MY_JSON_TO, __VA_ARGS__)) } \
    inline void from_json( MyCJson::MyCJson myJson_j,  Type& myJson_t) { MY_JSON_EXPAND(MY_JSON_PASTE(MY_JSON_FROM, __VA_ARGS__)) }

#define MY_JSON_EXPAND( x ) x
#define MY_JSON_GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, NAME,...) NAME
#define MY_JSON_PASTE(...) MY_JSON_EXPAND(MY_JSON_GET_MACRO(__VA_ARGS__, \
        MY_JSON_PASTE64, MY_JSON_PASTE63, MY_JSON_PASTE62, MY_JSON_PASTE61, MY_JSON_PASTE60, MY_JSON_PASTE59, MY_JSON_PASTE58, MY_JSON_PASTE57, \
        MY_JSON_PASTE56, MY_JSON_PASTE55, MY_JSON_PASTE54, MY_JSON_PASTE53, MY_JSON_PASTE52, MY_JSON_PASTE51, MY_JSON_PASTE50, MY_JSON_PASTE49, \
        MY_JSON_PASTE48, MY_JSON_PASTE47, MY_JSON_PASTE46, MY_JSON_PASTE45, MY_JSON_PASTE44, MY_JSON_PASTE43, MY_JSON_PASTE42, MY_JSON_PASTE41, \
        MY_JSON_PASTE40, MY_JSON_PASTE39, MY_JSON_PASTE38, MY_JSON_PASTE37, MY_JSON_PASTE36, MY_JSON_PASTE35, MY_JSON_PASTE34, MY_JSON_PASTE33, \
        MY_JSON_PASTE32, MY_JSON_PASTE31, MY_JSON_PASTE30, MY_JSON_PASTE29, MY_JSON_PASTE28, MY_JSON_PASTE27, MY_JSON_PASTE26, MY_JSON_PASTE25, \
        MY_JSON_PASTE24, MY_JSON_PASTE23, MY_JSON_PASTE22, MY_JSON_PASTE21, MY_JSON_PASTE20, MY_JSON_PASTE19, MY_JSON_PASTE18, MY_JSON_PASTE17, \
        MY_JSON_PASTE16, MY_JSON_PASTE15, MY_JSON_PASTE14, MY_JSON_PASTE13, MY_JSON_PASTE12, MY_JSON_PASTE11, MY_JSON_PASTE10, MY_JSON_PASTE9, \
        MY_JSON_PASTE8, MY_JSON_PASTE7, MY_JSON_PASTE6, MY_JSON_PASTE5, MY_JSON_PASTE4, MY_JSON_PASTE3, MY_JSON_PASTE2, MY_JSON_PASTE1)(__VA_ARGS__))
#define MY_JSON_PASTE2(func, v1) func(v1)
#define MY_JSON_PASTE3(func, v1, v2) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE2(func, v2)
#define MY_JSON_PASTE4(func, v1, v2, v3) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE3(func, v2, v3)
#define MY_JSON_PASTE5(func, v1, v2, v3, v4) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE4(func, v2, v3, v4)
#define MY_JSON_PASTE6(func, v1, v2, v3, v4, v5) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE5(func, v2, v3, v4, v5)
#define MY_JSON_PASTE7(func, v1, v2, v3, v4, v5, v6) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE6(func, v2, v3, v4, v5, v6)
#define MY_JSON_PASTE8(func, v1, v2, v3, v4, v5, v6, v7) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE7(func, v2, v3, v4, v5, v6, v7)
#define MY_JSON_PASTE9(func, v1, v2, v3, v4, v5, v6, v7, v8) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE8(func, v2, v3, v4, v5, v6, v7, v8)
#define MY_JSON_PASTE10(func, v1, v2, v3, v4, v5, v6, v7, v8, v9) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE9(func, v2, v3, v4, v5, v6, v7, v8, v9)
#define MY_JSON_PASTE11(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE10(func, v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define MY_JSON_PASTE12(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE11(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)
#define MY_JSON_PASTE13(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE12(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12)
#define MY_JSON_PASTE14(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE13(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13)
#define MY_JSON_PASTE15(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE14(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14)
#define MY_JSON_PASTE16(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE15(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15)
#define MY_JSON_PASTE17(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE16(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16)
#define MY_JSON_PASTE18(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE17(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17)
#define MY_JSON_PASTE19(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE18(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18)
#define MY_JSON_PASTE20(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE19(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19)
#define MY_JSON_PASTE21(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE20(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20)
#define MY_JSON_PASTE22(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE21(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21)
#define MY_JSON_PASTE23(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE22(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22)
#define MY_JSON_PASTE24(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE23(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23)
#define MY_JSON_PASTE25(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE24(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24)
#define MY_JSON_PASTE26(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE25(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25)
#define MY_JSON_PASTE27(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE26(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26)
#define MY_JSON_PASTE28(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE27(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27)
#define MY_JSON_PASTE29(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE28(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28)
#define MY_JSON_PASTE30(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE29(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29)
#define MY_JSON_PASTE31(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE30(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30)
#define MY_JSON_PASTE32(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE31(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31)
#define MY_JSON_PASTE33(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE32(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32)
#define MY_JSON_PASTE34(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE33(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33)
#define MY_JSON_PASTE35(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE34(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34)
#define MY_JSON_PASTE36(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE35(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35)
#define MY_JSON_PASTE37(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE36(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36)
#define MY_JSON_PASTE38(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE37(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37)
#define MY_JSON_PASTE39(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE38(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38)
#define MY_JSON_PASTE40(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE39(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39)
#define MY_JSON_PASTE41(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE40(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40)
#define MY_JSON_PASTE42(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE41(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41)
#define MY_JSON_PASTE43(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE42(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42)
#define MY_JSON_PASTE44(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE43(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43)
#define MY_JSON_PASTE45(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE44(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44)
#define MY_JSON_PASTE46(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE45(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45)
#define MY_JSON_PASTE47(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE46(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46)
#define MY_JSON_PASTE48(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE47(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47)
#define MY_JSON_PASTE49(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE48(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48)
#define MY_JSON_PASTE50(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE49(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49)
#define MY_JSON_PASTE51(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE50(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50)
#define MY_JSON_PASTE52(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE51(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51)
#define MY_JSON_PASTE53(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE52(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52)
#define MY_JSON_PASTE54(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE53(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53)
#define MY_JSON_PASTE55(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE54(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54)
#define MY_JSON_PASTE56(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE55(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55)
#define MY_JSON_PASTE57(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE56(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56)
#define MY_JSON_PASTE58(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE57(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57)
#define MY_JSON_PASTE59(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE58(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58)
#define MY_JSON_PASTE60(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE59(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59)
#define MY_JSON_PASTE61(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE60(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60)
#define MY_JSON_PASTE62(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE61(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61)
#define MY_JSON_PASTE63(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE62(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62)
#define MY_JSON_PASTE64(func, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63) MY_JSON_PASTE2(func, v1) MY_JSON_PASTE63(func, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v40, v41, v42, v43, v44, v45, v46, v47, v48, v49, v50, v51, v52, v53, v54, v55, v56, v57, v58, v59, v60, v61, v62, v63)

#define MY_JSON_TO(v1)  myJson_j.add_to_json(#v1, myJson_t.v1);
#define MY_JSON_FROM(v1) myJson_j.get_to(myJson_t.v1, #v1);





//=========================================================================================
typedef struct Status
{
	int err_code;
	std::string err_msg;

	MY_JSON_HELPER(Status, err_code, err_msg);
}STATUS;

typedef struct Mail
{
	STATUS status;
	std::string mail;
	STATUS status1;

	MY_JSON_HELPER(Mail, status, mail, status1);
}MAIL;

typedef struct Mails
{
    std::vector<MAIL> mail_list;
    MY_JSON_HELPER(Mails, mail_list);
}MAILS;


#endif // !__CJSON_CLASS_DEF_H__

