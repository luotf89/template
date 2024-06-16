
#include <type_traits>
namespace my_type_traits {

template<typename _T, _T __value>
struct integral_constant {
    using type = _T;
    constexpr static _T value = __value;
    constexpr operator _T() {
        return value;
    }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template<typename _T1, typename _T2>
struct is_same_type: public false_type {
};

template<typename _T>
struct is_same_type<_T, _T>: public true_type {
};

template<typename _T1, typename _T2>
constexpr bool is_same_type_v = is_same_type<_T1, _T2>::value;

template<typename _T>
struct remove_reference {
    using type = _T;
};

template<typename _T>
struct remove_reference<_T&&> {
    using type = typename remove_reference<_T>::type;
};

template<typename _T>
struct remove_reference<_T&> {
    using type = typename remove_reference<_T>::type;
};

template<typename _T>
using remove_reference_t = typename remove_reference<_T>::type;

template<typename _T>
struct remove_const{
    using type = _T;
};

template <typename _T>
struct remove_const<const _T> {
    using type = typename remove_const<_T>::type;
};

template<typename _T>
using remove_const_t = typename remove_const<_T>::type;

template<typename _T>
struct remove_volatile{
    using type = _T;
};

template <typename _T>
struct remove_volatile<volatile _T> {
    using type = typename remove_volatile<_T>::type;
};

template<typename _T>
using remove_volatile_t = typename remove_volatile<_T>::type;

template <typename _T>
struct remove_cv {
    using type = typename remove_const<typename remove_volatile<_T>::type>::type;
};

template<typename _T>
using remove_cv_t = typename remove_cv<_T>::type;

template <typename _T>
struct remove_cvr {
    using type = typename remove_cv<typename remove_reference<_T>::type>::type;
};

template<typename _T>
using remove_cvr_t = typename remove_cvr<_T>::type;

template<typename _T>
struct remove_point{
    using type = _T;
};

template <typename _T>
struct remove_point<_T*> {
    using type = typename remove_point<_T>::type;
};

template<typename _T>
using remove_point_t = typename remove_point<_T>::type;

template<typename _Base, typename _Derived>
struct is_base_of:public integral_constant<bool, __is_base_of(_Base, _Derived)> {};

template<typename _Base, typename _Derived>
bool constexpr is_base_of_v = is_base_of<_Base, _Derived>::value;

template<bool __cond, typename _T = void>
struct enable_if {};

template<typename _T>
struct enable_if<true, _T> {
    using type = _T;
};

template<bool __cond, typename _T>
using enable_if_t = typename enable_if<__cond, _T>::type;

template <typename _T>
struct negative {};

template<>
struct negative<true_type>:public false_type {};

template<>
struct negative<false_type>:public true_type {};

template<typename _T, typename ...Args>
struct conjunction {};

template<typename ...Args>
struct conjunction<false_type, Args...>: public false_type {};

template<typename ...Args>
struct conjunction<true_type, Args...>: public conjunction<Args...> {};

template<>
struct conjunction<true_type>:public true_type {};


template<typename _T, typename ...Args>
struct disjunction {};

template<typename ...Args>
struct disjunction<false_type, Args...>: public disjunction<Args...> {};

template<typename ...Args>
struct disjunction<true_type, Args...>: public true_type {};

template<>
struct disjunction<false_type>:public false_type {};


};