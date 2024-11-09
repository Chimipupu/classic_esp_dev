/**
 * @file （ファイル名） : lib_math.h
 * @brief （概要） : 数学ライブラリ
 * @author （作成者） : ちみ/Chimi（https://github.com/Chimipupu）
 * @date （作成日） : 2021/01/13
 * @details （詳細な説明） : 
*/

#ifndef __LIB_MATH_H__
#define __LIB_MATH_H__

#include "./common.h"

#define _USE_MATH_DEFINES /* mathライブラリのπ,e等のマクロ有効 */
#include <math.h>

#define CALC_DIGIT  10   /* 有効数字 */

void lib_math_accuracy( void );

// #define MATH_PI    3.14159265358979323846264338327950288 /* π（円周率） */
/* 角度からラジアンへの変換 */
// #define MATH_DEG_TO_RAD(degree)     (double)((double)degree *  (180. / (double)MATH_PI))
/* ラジアンから角度への変換 */
// #define MATH_RAD_TO_DEG(radian)     (double)((double)radian * (double)(MATH_PI / 180.))

typedef struct _duvmod_t{
    double quot;    /* 除算演算結果 */
    double rem;     /* 剰余算演算結果 */
}divmod_t;

/**
 * @fn inline double math_pi( void )
 * @brief 円周率の計算
 * @param[in] None
 * @param[out] 円周率(double)
 * @return None
 * @details 
*/
inline double math_pi( void )
{
    double pi;

    pi = atan(1.) * 4.;

    return pi;
}

/**
 * @fn inline divmod_t divmod(double val_a,double val_b)
 * @brief 除算＋剰余算
 * @param[in] None
 * @param[out] 引数の除算及び剰余算の結果
 * @return None
 * @details 
*/
inline divmod_t divmod(double val_a,double val_b)
{
    divmod_t val_divmod;

    val_divmod.quot = val_a / val_b;
    val_divmod.rem = (double)((uint32_t)val_a % (uint32_t)val_b);

    return val_divmod;
}

/**
 * @fn inline double math_deg2rad(double deg)
 * @brief ラジアンから角度に変換
 * @param[in] None
 * @param[out] ラジアンから角度への変換結果
 * @return None
 * @details 
*/
inline double math_rad2deg(double rad)
{
    double deg;

    deg = rad * (math_pi() / 180.);

    return deg;
}

/**
 * @fn inline double math_deg2rad(double deg)
 * @brief 角度からラジアンに変換
 * @param[in] None
 * @param[out] 角度からラジアンへの変換結果
 * @return None
 * @details 
*/
inline double math_deg2rad(double deg)
{
    double rad;

    rad = deg * (180. / math_pi());

    return rad;
}

/**
 * @fn inline double math_sin(double val_a,double val_b)
 * @brief サイン
 * @param[in] None
 * @param[out] コサインの計算結果
 * @return None
 * @details 
*/
inline double math_sin(double val_a,double val_b)
{
    double tmp_sin, tmp_sin_deg, tmp_sin_rad;

    tmp_sin_deg = sin(val_a / val_b);
    tmp_sin_rad = sin(math_deg2rad(val_a) / math_deg2rad(val_b));
    tmp_sin = (tmp_sin_deg + tmp_sin_rad) / 2.;

    return tmp_sin;
}

/**
 * @fn inline double math_cos(double val_a,double val_b)
 * @brief コサイン
 * @param[in] None
 * @param[out] コサインの計算結果
 * @return None
 * @details 
*/
inline double math_cos(double val_a,double val_b)
{
    double tmp_cos, tmp_cos_deg, tmp_cos_rad;

    tmp_cos_deg = cos(val_a / val_b);
    tmp_cos_rad = cos(math_deg2rad(val_a) / math_deg2rad(val_b));
    tmp_cos = (tmp_cos_deg + tmp_cos_rad) / 2.;

    return tmp_cos;
}

/**
 * @fn inline double math_tan(double val_a,double val_b)
 * @brief タンジェント
 * @param[in] None
 * @param[out] タンジェントの計算結果
 * @return None
 * @details 
*/
inline double math_tan(double val_a,double val_b)
{
    double tmp_tan, tmp_tan_deg, tmp_tan_rad;

    tmp_tan_deg = tan(val_a / val_b);
    tmp_tan_rad = tan(math_deg2rad(val_a) / math_deg2rad(val_b));
    tmp_tan = (tmp_tan_deg + tmp_tan_rad) / 2.;

    return tmp_tan;
}

#endif /* __LIB_MATH_H__ */