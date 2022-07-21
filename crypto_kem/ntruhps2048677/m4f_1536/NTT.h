#ifndef NTT_H
#define NTT_H

#include <stdint.h>

#include "NTT_params.h"

extern void __asm_Good_3x2(int32_t *des, const int32_t*, int32_t, int32_t, const int16_t *src);
extern void __asm_Good_3x2_small(int32_t *des, const int32_t*, int32_t, int32_t, const int16_t *src);
extern void __asm_ntt_32(int32_t *des, const int32_t*, int32_t, int32_t);
extern void __asm_base_mul(int32_t*, const int32_t*, int32_t, int32_t, int32_t*, int32_t*);
extern void __asm_i_3x2(int32_t *des, const int32_t*, int32_t, int32_t);
extern void __asm_intt(int32_t *des, const int32_t*, int32_t, int32_t);
extern void __asm_final_map(uint16_t *des, const int32_t*, int32_t, int32_t, int32_t *src);

static const int32_t streamlined_CT_table_Q1[NTT_N - 1] = {
-795405, -795405, -795405, 1339451, -795405, 1339451, -292348, 1081606, 1339451, -292348, 1081606, -989458, -4302, -1362889, -801617, -795405, -795405, 1339451, -795405, 1339451, -292348, 1081606, 1339451, -292348, 1081606, -989458, -4302, -1362889, -801617, -292348, -989458, -4302, 268217, 696069, -1162914, 676937, 1081606, -1362889, -801617, -922090, 34378, -440440, 1349285, -989458, 268217, 696069, 1148369, 39557, -301085, 713673, -4302, -1162914, 676937, -1355046, -653528, -1211042, 946026, -1362889, -922090, 34378, -1323782, 973177, 880798, -1142884, -801617, -440440, 1349285, 532180, 997469, -964108, 794706, 268217, 1148369, 39557, -785627, 288260, 259700, 686239, 696069, -301085, 713673, 527025, 989240, -633452, 1359657, -1162914, -1355046, -653528, 761232, -604258, 498104, -1122204, 676937, -1211042, 946026, -757554, 968957, -87378, -213185, -922090, -1323782, 973177, -682267, 119712, -1337363, -1380076, 34378, 880798, -1142884, -1259825, -292254, -613490, 145040, -440440, 532180, 997469, -851198, -90240, 76287, 1282723, 1349285, -964108, 794706, 1216540, -139974, 124416, 927022
};

static const int32_t mul_Rmod_table_Q1[NTT_N] = {
-795405, 1339451, -292348, 1081606, -989458, -4302, -1362889, -801617, 268217, 696069, -1162914, 676937, -922090, 34378, -440440, 1349285, 1148369, 39557, -301085, 713673, -1355046, -653528, -1211042, 946026, -1323782, 973177, 880798, -1142884, 532180, 997469, -964108, 794706, -785627, 288260, 259700, 686239, 527025, 989240, -633452, 1359657, 761232, -604258, 498104, -1122204, -757554, 968957, -87378, -213185, -682267, 119712, -1337363, -1380076, -1259825, -292254, -613490, 145040, -851198, -90240, 76287, 1282723, 1216540, -139974, 124416, 927022
};

static const int32_t streamlined_inv_CT_table_Q1[NTT_N - 1] = {
-795405, -795405, -795405, -1339451, -795405, -1081606, -1339451, 292348, -1339451, -1081606, 292348, 801617, 4302, 1362889, 989458, -795405, -795405, -1339451, -795405, -1081606, -1339451, 292348, -1349285, -794706, 964108, -927022, 139974, -124416, -1216540, 801617, -1349285, 440440, -794706, -997469, 964108, -532180, -676937, -946026, 1211042, 213185, -968957, 87378, 757554, -1081606, 801617, 1362889, -1349285, -34378, 440440, 922090, -34378, 1142884, -880798, -145040, 292254, 613490, 1259825, 4302, -676937, 1162914, -946026, 653528, 1211042, 1355046, -696069, -713673, 301085, -1359657, -989240, 633452, -527025, -1339451, -1081606, 292348, 801617, 4302, 1362889, 989458, 440440, -997469, -532180, -1282723, 90240, -76287, 851198, 1362889, -34378, 922090, 1142884, -973177, -880798, 1323782, 1162914, 653528, 1355046, 1122204, 604258, -498104, -761232, 292348, 4302, 989458, -676937, -696069, 1162914, -268217, 922090, -973177, 1323782, 1380076, -119712, 1337363, 682267, 989458, -696069, -268217, -713673, -39557, 301085, -1148369, -268217, -39557, -1148369, -686239, -288260, -259700, 785627
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
invNinv3R2modQ1
};

#define NTT_forward(out, in){ \
    __asm_Good_3x2(out, _3_NTT_Rmod_table_Q1, Q1prime, Q1, in); \
    __asm_ntt_32(out, streamlined_CT_table_Q1, Q1prime, Q1); \
}

#define NTT_forward_small(out, in){ \
    __asm_Good_3x2_small(out, _3_NTT_table_Q1, Q1prime, Q1, in); \
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
#define Final_map(out, in) __asm_final_map((uint16_t*)out, final_const, Q1prime, Q1, in); 

#endif



