#ifndef NTT_H
#define NTT_H

#include <stdint.h>

#include "NTT_params.h"

extern void __asm_Good_3x2(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q, int16_t *src);
extern void __asm_Good_3x2_small(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q, int16_t *src);
extern void __asm_3x2block_ntt(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q);
extern void __asm_ntt(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q);
extern void __asm_base_mul(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q, int32_t *src1, int32_t *src2);
extern void __asm_intt(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q);
extern void __asm_3x2block_intt(int32_t *des, const int32_t *table, int32_t Qprime, int32_t Q);
extern void __asm_i_Good(int32_t *des, int32_t *src);
extern void __asm_final_map(uint16_t *des, const int32_t last_const, int32_t Qprime, int32_t Q, int32_t *src);

static const int32_t _9_NTT_table[16] = {
1, omega93Q1, omega96Q1,
omega9Q1, omega94Q1, omega97Q1,
omega92Q1, omega95Q1, omega98Q1,
};

static const int32_t _3x2_NTT_table_Q1[32] = {
omega93Q1,       omega96Q1,
       1,                1,               1,
       1,         omega9Q1,       omega92Q1,
       1,        omega92Q1,       omega94Q1,
 omega4Q1,        omega4Q1,        omega4Q1,
 omega4Q1,  omega4omega9Q1, omega4omega92Q1,
 omega4Q1, omega4omega92Q1, omega4omega94Q1
};

static const int32_t streamlined_CT_table_Q1[NTT_N - 1] = {
-3284735, -3284735, -2858835, -3284735, -3284735, -2858835, -3284735, -2858835, 455852, -2555650, -3284735, -2858835, 455852, -2555650, 3076373, 1526730, -1909996, 3193720, -2858835, 455852, -2555650, 3076373, 1526730, -1909996, 3193720, 2544653, 2994940, 3189686, -3337682, 2309343, -2831613, -1094042, -2679653, 455852, 3076373, 1526730, 2544653, 2994940, 3189686, -3337682, 2036787, 817442, -405489, -955155, 364810, 2203116, 1022683, -3137233, -2555650, -1909996, 3193720, 2309343, -2831613, -1094042, -2679653, -1664883, -1208293, 619472, -2829832, 2447880, -1245602, 527689, 1618639
};

static const int32_t mul_Rmod_table_Q1[((NTT_N >> 1) * 9)] = {
3284735, -2407648, -877087, 173666, -372833, 199167, 547923, -780727, 232804, 2858835, 2560983, 1306711, -1332432, -2031560, -3362537, -619951, -2813720, -3292858, -455852, -1600018, 2055870, -1520034, -1958965, -3247530, -426966, -1705567, 2132533, 2555650, -797761, -1757889, 161423, 2758524, -2919947, 3204811, 1844024, 1677694, -3076373, -3164222, -485934, -1478080, -257730, 1735810, -2182502, 160356, 2022146, -1526730, -2829164, -2370635, 2933183, -382107, -2551076, 2252273, -878466, -1373807, 1909996, -2040502, 130506, 2944007, 638808, 3143714, 1136221, -823865, -312356, -3193720, 1239795, 1953925, -1859663, 156441, 1703222, -1752788, 3295917, -1543129, -2544653, -2991776, -1190100, 2132582, -2139399, 6817, 898819, -2256639, 1357820, -2994940, -1123117, -2608472, -1206631, 2046599, -839968, -3317427, 718677, 2598750, -3189686, 1243684, 1946002, -1390666, -2971454, -2364409, -740470, 2074137, -1333667, 3337682, -924257, -2413425, -222107, 1204884, -982777, 2932939, 2242238, 1551352, -2309343, 3187904, -878561, -1214622, 2230653, -1016031, -3087585, -783895, -2855049, 2831613, -3321376, 489763, -2746458, 1444206, 1302252, -2118682, 952229, 1166453, 1094042, 1631658, -2725700, -2387111, -642186, 3029297, -3119286, -1139611, -2467632, 2679653, -2247294, -432359, 1293495, -1325888, 32393, -2621294, 877878, 1743416, -2036787, -2582203, -2107539, -2769440, 3329623, -560183, -2035951, -2421321, -2269257, -817442, 489214, 328228, -3089634, -2481676, -1155219, -1157266, -3209997, -2359266, 405489, 2396, -407885, 48529, 1309051, -1357580, -3107125, -1679816, -1939588, 955155, 1729540, -2684695, -2218172, -2745396, -1762961, -97826, -2959004, 3056830, -364810, -1652315, 2017125, -263162, 2267495, -2004333, 2773701, 821455, 3131373, -2203116, -266377, 2469493, -1585605, 1884677, -299072, -2279243, -1318566, -3128720, -1022683, -1014270, 2036953, -2671296, 1489987, 1181309, 3241458, 1767634, 1717437, 3137233, -3243511, 106278, 2814333, 2461387, 1450809, -2754498, 3340693, -586195, 1664883, 2300370, 2761276, 354225, 790039, -1144264, 24677, 3123596, -3148273, 1208293, -2885396, 1677103, 1356296, 2954994, 2415239, -1984818, 1094621, 890197, -619472, -1707733, 2327205, -3277795, 653502, 2624293, -357285, 584332, -227047, 2829832, -2167544, -662288, 1690354, -634814, -1055540, -241180, -1323029, 1564209, -2447880, -3180282, -1098367, -17856, 2163822, -2145966, -8308, -955126, 963434, 1245602, 1220839, -2466441, 1046671, -1160315, 113644, 2121913, -1987941, -133972, -527689, -2534684, 3062373, -479082, -245092, 724174, 1178454, -1048276, -130178, -1618639, -481612, 2100251, -2388037, 2204941, 183096, 2579148, 698926, -3278074
};

static const int32_t streamlined_inv_CT_table_Q1[NTT_N - 1] = {
-3284735, -3284735, 2858835, -3284735, 2858835, 2555650, -455852, -3284735, -3284735, 2858835, -3284735, 2858835, 2555650, -455852, 2858835, 2555650, -455852, -3193720, 1909996, -1526730, -3076373, 2555650, -3193720, 1909996, 2679653, 1094042, 2831613, -2309343, -455852, -1526730, -3076373, 3337682, -3189686, -2994940, -2544653, -3193720, 2679653, 1094042, -1618639, -527689, 1245602, -2447880, 1909996, 2831613, -2309343, 2829832, -619472, 1208293, 1664883, -1526730, 3337682, -3189686, 3137233, -1022683, -2203116, -364810, -3076373, -2994940, -2544653, 955155, 405489, -817442, -2036787
};

static const int32_t _3x2block_intt_table_Q1[27] = {
-3284735, -3284735, 2858835, -3284735, 2858835, 2555650, -455852,
invomega93RmodQ1, invomega96RmodQ1,
 invomega9RmodQ1, invomega92RmodQ1, invomega94RmodQ1, invomega98RmodQ1,
invomega95RmodQ1,  invomega9RmodQ1,
invomega4RmodQ1,
invomega4omega9RmodQ1, invomega4omega92RmodQ1, invomega4omega94RmodQ1, invomega4omega98RmodQ1,
invomega4omega95RmodQ1, invomega4omega9RmodQ1
};

static const int32_t _3x2_NTT_Rmod_table_Q1[32] = {
omega93RmodQ1, omega96RmodQ1,
 omega9RmodQ1, omega92RmodQ1,  omega94RmodQ1, omega98RmodQ1,
omega95RmodQ1,  omega9RmodQ1,
omega4RmodQ1,
omega4omega9RmodQ1, omega4omega92RmodQ1, omega4omega94RmodQ1, omega4omega98RmodQ1,
omega4omega95RmodQ1, omega4omega9RmodQ1
};

#define NTT_forward(out, in){ \
    __asm_Good_3x2(out, _3x2_NTT_Rmod_table_Q1, Q1prime, Q1, in); \
    __asm_3x2block_ntt(out, _3x2_NTT_Rmod_table_Q1, Q1prime, Q1); \
    __asm_ntt(out, streamlined_CT_table_Q1, Q1prime, Q1); \
}

#define NTT_forward_small(out, in){ \
    __asm_Good_3x2_small(out, _3x2_NTT_table_Q1, Q1prime, Q1, in); \
    __asm_3x2block_ntt(out, _3x2_NTT_Rmod_table_Q1, Q1prime, Q1); \
    __asm_ntt(out, streamlined_CT_table_Q1, Q1prime, Q1); \
}

#define NTT_mul(out, in1, in2) __asm_base_mul(out, mul_Rmod_table_Q1, Q1prime, Q1, in1, in2)


#define NTT_inv(out, buff, in){ \
    __asm_intt(in, streamlined_inv_CT_table_Q1, Q1prime, Q1); \
    __asm_3x2block_intt(in, _3x2block_intt_table_Q1, Q1prime, Q1); \
    __asm_i_Good(buff, in); \
    __asm_final_map(out, invNinv9R2modQ1, Q1prime, Q1, buff); \
}

#define NTT_inverse(buff, in){ \
    __asm_intt(in, streamlined_inv_CT_table_Q1, Q1prime, Q1); \
    __asm_3x2block_intt(in, _3x2block_intt_table_Q1, Q1prime, Q1); \
    __asm_i_Good(buff, in); \
}
#define Final_map(out, buff) __asm_final_map((uint16_t*)out, invNinv9R2modQ1, Q1prime, Q1, buff); 


#endif


