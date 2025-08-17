#ifndef FUNCTIONHOLDER_H
#define FUNCTIONHOLDER_H

#include "IFunctionHolder.h"
#include <WString.h>
#include <string>
#include <functional>
#include <Arduino.h>
#include "enum_CommandRepo.h"

//#define DEBUG_FUNCTIONHOLDER //comment out or not 
#ifdef  DEBUG_FUNCTIONHOLDER
#define _FUNCTHOLDER_PP(a) Serial.print(a);
#define _FUNCTHOLDER_PL(a) Serial.println(a);
#else
#define _FUNCTHOLDER_PP(a)
#define _FUNCTHOLDER_PL(a)
#endif

template <typename T> class FunctionHolder:public IFunctionHolder
{
    private:   
    std::shared_ptr<T> Tptr;

    long stringTolint(String num);
    bool stringToBool(String bol);
    String boolToString(bool input){return input ? "true" : "false";};
    
    public:
    FunctionHolder(std::shared_ptr<T> shrptr);
    ~FunctionHolder() {};
    String run(std::vector<String> params)override;

    template <typename Z>
    struct function_traits;

    template <typename R, typename... Args>
    struct function_traits<std::function<R(Args...)>*>
    {
        static const size_t argnum = sizeof...(Args);
    };
    template <typename R, typename... Args>
    struct function_traits<std::function<R(Args...)>>
    {
        static const size_t argnum = sizeof...(Args);
    };

    template <typename Func>
    String apply_functions(Func func, const std::vector<String> &params)
    {   
        String response="";
        _FUNCTHOLDER_PL(String(__FUNCTION__)+" expected paramater num:"+
                        String(function_traits<decltype(func)>::argnum)+" real:"+
                        String(params.size()));
        if (params.size() == function_traits<decltype(func)>::argnum)
        {
            if constexpr (std::is_same_v<Func, ft_V_V>)
            {    
                 std::apply(func, std::make_tuple());
            }
            else if constexpr (std::is_same_v<Func, ft_V_I>)
            {
                std::apply(func, std::make_tuple(stringTolint(params[0])));
            }
            else if constexpr (std::is_same_v<Func, ft_V_UI>)
            {
                std::apply(func, std::make_tuple(static_cast<unsigned int>(stringTolint(params[0]))));
            }
            else if constexpr (std::is_same_v<Func, ft_V_UC>)
            {
                std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0]))));
            }
            else if constexpr (std::is_same_v<Func, ft_V_B>)
            {
                std::apply(func, std::make_tuple(stringToBool(params[0])));
            }
            else if constexpr (std::is_same_v<Func, ft_V_UC_B>)
            {
                std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])),
                                                 stringToBool(params[1])));
            }
            else if constexpr (std::is_same_v<Func, ft_V_UC_B_B>)
            {
                std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])),
                                                 stringToBool(params[1]),
                                                 stringToBool(params[2])));
            }
            else if constexpr (std::is_same_v<Func, ft_V_S_B>)
            {
                std::apply(func, std::make_tuple(params[0], stringToBool(params[1])));
            }
            else if constexpr (std::is_same_v<Func, ft_V_S_S>)
            {
                std::apply(func, std::make_tuple(params[0], params[1]));
            }
            else if constexpr (std::is_same_v<Func, ft_V_S_S_UC>)
            {
                std::apply(func, std::make_tuple(params[0], params[1], static_cast<unsigned char>(stringTolint(params[2]))));
            }
            else if constexpr (std::is_same_v<Func, ft_B_V>)
            {
                response=boolToString(static_cast<bool>(std::apply(func, std::make_tuple())));
            }
            else if constexpr (std::is_same_v<Func, ft_B_UC>)
            {
                response=boolToString(std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])))));
            }
            
            else if constexpr (std::is_same_v<Func, ft_B_S>)
            {
                response=boolToString(std::apply(func, std::make_tuple(params[0])));
            }
            else if constexpr (std::is_same_v<Func, ft_B_S_UC>)
            {
                response=boolToString(std::apply(func, std::make_tuple(params[0],
                                                                      static_cast<unsigned char>(stringTolint(params[1])))));
            }
            else if constexpr (std::is_same_v<Func, ft_B_UC_S>)
            {
                response=boolToString(std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])),
                                                                      params[1])));
            }
            else if constexpr (std::is_same_v<Func, ft_B_S_S>)
            {
                response=boolToString(std::apply(func, std::make_tuple(params[0], params[1])));
            }
            else if constexpr (std::is_same_v<Func, ft_B_S_UC_B_B>)
            {
                response=boolToString(std::apply(func, std::make_tuple(params[0],
                                                                      static_cast<unsigned char>(stringTolint(params[1])),
                                                                      stringToBool(params[2]),
                                                                      stringToBool(params[3]))));
            }
            else if constexpr (std::is_same_v<Func, ft_B_UC_B_B>)
            {
                response=boolToString(std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])),
                                                                      stringToBool(params[1]),
                                                                      stringToBool(params[2]))));
            }
            else if constexpr (std::is_same_v<Func, ft_B_S_B_B>)
            {
                response=boolToString(std::apply(func, std::make_tuple(params[0],
                                                                      stringToBool(params[1]),
                                                                      stringToBool(params[2]))));
            }
             else if constexpr (std::is_same_v<Func, ft_UI_V>)
            {
                response=String(std::apply(func,std::make_tuple()));
            }
            else if constexpr (std::is_same_v<Func, ft_I_S>)
            {
                response=String(std::apply(func,std::make_tuple(params[0])));
            }
        
            else if constexpr (std::is_same_v<Func, ft_I_V>)
            {
                response=String(std::apply(func,std::make_tuple()));
            }

            else if constexpr (std::is_same_v<Func, ft_I_UC>)
            {
                response=String(std::apply(func,std::make_tuple(static_cast <unsigned char>(params[0].toInt()))));
            }

            else if constexpr (std::is_same_v<Func, ft_UC_V>)
            {
                response=String(std::apply(func, std::make_tuple()));
            }
            else if constexpr (std::is_same_v<Func, ft_UC_S>)
            {
               response=String((unsigned int)std::apply(func, std::make_tuple(params[0]))); 
            }
            else if constexpr (std::is_same_v<Func, ft_UC_UC>)
            {
                response=String((unsigned int)std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])))));
            }
            else if constexpr (std::is_same_v<Func, ft_C_S>)
            {
               response=String((int)std::apply(func, std::make_tuple(params[0]))); 
            }
            else if constexpr (std::is_same_v<Func, ft_C_UC>)
            {
                response=String((int)std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0])))));
            }
            else if constexpr (std::is_same_v<Func, ft_F_S>)
            {
                response=String(std::to_string(std::apply(func, std::make_tuple(params[0]))).c_str());
            }
            else if constexpr (std::is_same_v<Func, ft_V_S>)
            {
                std::apply(func, std::make_tuple(params[0]));
            }
            else if constexpr (std::is_same_v<Func, ft_S_V>)
            {
                response=std::apply(func, std::make_tuple());
            }
            else if constexpr (std::is_same_v<Func, ft_S_UC>)
            {
                response=std::apply(func, std::make_tuple(static_cast<unsigned char>(stringTolint(params[0]))));
            }
            else if constexpr (std::is_same_v<Func, ft_S_UI_UI>)
            {
                response=std::apply(func, std::make_tuple(static_cast<uint>(stringTolint(params[0])),
                                                            static_cast<uint>(stringTolint(params[1]))));
            }
        }
        else
        {
            _FUNCTHOLDER_PL(String(__FUNCTION__) + ":The number of arguments does not match.")
        }
        return response;
    };
};
template <typename T>
inline long FunctionHolder<T>::stringTolint(String num)
{
    char** end=nullptr;
    return std::strtol(num.c_str(),end,10);
}

template <typename T>
inline bool FunctionHolder<T>::stringToBool(String bol)
{
    char** end=nullptr;
    if(bol=="true" || std::strtol(bol.c_str(),end,10)>0) return true;
    return false;
}

template <typename T>
FunctionHolder<T>::FunctionHolder(std::shared_ptr<T> shrptr)
{
    if(shrptr) Tptr=shrptr;
    else _FUNCTHOLDER_PL("FunctionHolder::FunctionHolder: shrptr is null");
}

template <typename T> String FunctionHolder<T>::run(std::vector<String> params)
{
	//std::shared_ptr<T> fpt = std::static_pointer_cast<T>(IFunctionHolder::voidptr);
	if(Tptr) return apply_functions(*Tptr, params);
    else _FUNCTHOLDER_PL("FunctionHolder::run: Tptr is null");
    return String();
}

#endif /* FUNCTIONHOLDER_H */
