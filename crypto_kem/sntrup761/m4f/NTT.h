#ifndef NTT_H
#define NTT_H

#include <stdint.h>

#include "NTT_params.h"

extern void __asm_Good_3x2(int32_t *des, const int32_t*, int32_t, int32_t, const int16_t *src);
extern void __asm_Good_3x2_small(int32_t *des, const int32_t*, int32_t, int32_t, const int8_t *src);
extern void __asm_ntt_32(int32_t *des, const int32_t*, int32_t, int32_t);
extern void __asm_base_mul(int32_t*, const int32_t*, int32_t, int32_t, int32_t*, int32_t*);
extern void __asm_i_3x2(int32_t *des, const int32_t*, int32_t, int32_t);
extern void __asm_intt(int32_t *des, const int32_t*, int32_t, int32_t);
extern void __asm_final_map(int16_t *des, const int32_t*, int32_t, int32_t, int32_t *src);

static const int32_t streamlined_CT_table_Q1[NTT_N - 1] = {
-311399, -311399, -311399, 3471433, -311399, 3471433, 2894487, -2592208, 3471433, 2894487, -2592208, 2462969, -1536046, -3050359, 3290424, -311399, -311399, 3471433, -311399, 3471433, 2894487, -2592208, 3471433, 2894487, -2592208, 2462969, -1536046, -3050359, 3290424, 2894487, 2462969, -1536046, -3196524, -2794208, 16826, 1356310, -2592208, -3050359, 3290424, -3421612, -922778, -1259013, -2252520, 2462969, -3196524, -2794208, 804399, -2052193, 3095387, 2009488, -1536046, 16826, 1356310, -1238959, -1340819, -2891570, 1431001, -3050359, -3421612, -922778, -3367043, -1642889, -1905608, 2340431, 3290424, -1259013, -2252520, 2867644, -2977751, -1280757, -3307920, -3196524, 804399, -2052193, 3454899, -1292838, -259914, 2786644, -2794208, 3095387, 2009488, -2832551, 3486211, 1210248, -137539, 16826, -1238959, -1340819, -751477, -1407403, 250674, -968737, 1356310, -2891570, 1431001, 2000205, 1318306, 2447325, 1605297, -3421612, -3367043, -1642889, -721754, -2223407, -414065, -679168, -922778, -1905608, 2340431, -1100903, -1454521, -2571496, -2397960, -1259013, 2867644, -2977751, -924236, 1454474, 2541407, 3381211, -2252520, -1280757, -3307920, 2826879, -2497269, 204037, -94891
};

static const int32_t mul_Rmod_table_Q1[NTT_N] = {
-311399, 3471433, 2894487, -2592208, 2462969, -1536046, -3050359, 3290424, -3196524, -2794208, 16826, 1356310, -3421612, -922778, -1259013, -2252520, 804399, -2052193, 3095387, 2009488, -1238959, -1340819, -2891570, 1431001, -3367043, -1642889, -1905608, 2340431, 2867644, -2977751, -1280757, -3307920, 3454899, -1292838, -259914, 2786644, -2832551, 3486211, 1210248, -137539, -751477, -1407403, 250674, -968737, 2000205, 1318306, 2447325, 1605297, -721754, -2223407, -414065, -679168, -1100903, -1454521, -2571496, -2397960, -924236, 1454474, 2541407, 3381211, 2826879, -2497269, 204037, -94891
};

static const int32_t streamlined_inv_CT_table_Q1[NTT_N - 1] = {
-311399, -311399, -311399, -3471433, -311399, 2592208, -3471433, -2894487, -3471433, 2592208, -2894487, -3290424, 1536046, 3050359, -2462969, -311399, -311399, -3471433, -311399, 2592208, -3471433, -2894487, 2252520, 3307920, 1280757, 94891, 2497269, -204037, -2826879, -3290424, 2252520, 1259013, 3307920, 2977751, 1280757, -2867644, -1356310, -1431001, 2891570, -1605297, -1318306, -2447325, -2000205, 2592208, -3290424, 3050359, 2252520, 922778, 1259013, 3421612, 922778, -2340431, 1905608, 2397960, 1454521, 2571496, 1100903, 1536046, -1356310, -16826, -1431001, 1340819, 2891570, 1238959, 2794208, -2009488, -3095387, 137539, -3486211, -1210248, 2832551, -3471433, 2592208, -2894487, -3290424, 1536046, 3050359, -2462969, 1259013, 2977751, -2867644, -3381211, -1454474, -2541407, 924236, 3050359, 922778, 3421612, -2340431, 1642889, 1905608, 3367043, -16826, 1340819, 1238959, 968737, 1407403, -250674, 751477, -2894487, 1536046, -2462969, -1356310, 2794208, -16826, 3196524, 3421612, 1642889, 3367043, 679168, 2223407, 414065, 721754, -2462969, 2794208, 3196524, -2009488, 2052193, -3095387, -804399, 3196524, 2052193, -804399, -2786644, 1292838, 259914, -3454899
};

static const int32_t _3_NTT_table_Q1[4] = {
omega3Q1, invomega3Q1
};

static const int32_t _3_NTT_Rmod_table_Q1[4] = {
omega3RmodQ1, invomega3RmodQ1
};

static const int32_t _3_iNTT_Rmod_table_Q1[4] = {
invomega3RmodQ1, omega3RmodQ1
};

static const int32_t final_const[4] = {
invNinv3R2modQ1, NTRU_Qbar, NTRU_Q
};

#define NTT_forward(out, in){ \
    __asm_Good_3x2(out, _3_NTT_Rmod_table_Q1, Q1prime, Q1, in); \
    __asm_ntt_32(out, streamlined_CT_table_Q1, Q1prime, Q1); \
}

#define NTT_forward_small(out, in){ \
    __asm_Good_3x2_small(out, _3_NTT_table_Q1, Q1prime, Q1, (int8_t*)in); \
    __asm_ntt_32(out, streamlined_CT_table_Q1, Q1prime, Q1); \
}

#define NTT_mul(out, in1, in2) __asm_base_mul(out, mul_Rmod_table_Q1, Q1prime, Q1, in1, in2)

#define NTT_inv(out, in){ \
    __asm_i_3x2(in, _3_iNTT_Rmod_table_Q1, Q1prime, Q1); \
    __asm_intt(in, streamlined_inv_CT_table_Q1, Q1prime, Q1); \
    __asm_final_map(out, final_const, Q1prime, Q1, in); \
}
#define NTT_inverse(in){ \
    __asm_i_3x2(in, _3_iNTT_Rmod_table_Q1, Q1prime, Q1); \
    __asm_intt(in, streamlined_inv_CT_table_Q1, Q1prime, Q1); \
}
#define Final_map(out,in) __asm_final_map(out, final_const, Q1prime, Q1, in); 

#endif


